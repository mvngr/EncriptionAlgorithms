#include "playfaircipher.h"
#include "dictionaries/cyrillicdictionary.h"
#include "commonAlghorithms.h"

#include <QDebug>

PlayfairCipher::PlayfairCipher(QObject *parent) : EncryptionAlgorithm(parent)
{
    dict_ = std::unique_ptr<CyrillicDictionary>(new CyrillicDictionary());
}

PlayfairCipher::PlayfairCipher(const QString &key, QObject *parent) : EncryptionAlgorithm(parent), key_(key)
{
    dict_ = std::unique_ptr<CyrillicDictionary>(new CyrillicDictionary());
}

QString PlayfairCipher::encrypt(const QString &textForEncrypt)
{
    error_ = "";

    auto copyText = textForEncrypt;
    if(textForEncrypt.size() % 2 == 1)
        copyText += ' ';

    auto matrix = dict_->makeSquareDictionaryMatrix(key_);

    QString encryptedText;
    for(int i = 0; i < copyText.size(); i+=2)
    {
        //Если два символа биграммы совпадают, добавляем после первого символа «Х», зашифровываем новую пару символов и продолжаем.
        if(copyText.at(i) == copyText.at(i + 1))
        {
            copyText.insert(i + 2, L'.');
            i--; //для того, чтобы пройтись по текущему символу и х
            continue;
        }

        auto positionPtr = MyAlgo::findPosition(matrix, copyText.at(i));
        auto position2Ptr = MyAlgo::findPosition(matrix, copyText.at(i+1));
        if(positionPtr && position2Ptr)
        {
            //Если символы биграммы исходного текста встречаются в одной строке, то эти символы замещаются на символы,
            //расположенные в ближайших столбцах справа от соответствующих символов.
            //Если символ является последним в строке, то он заменяется на первый символ этой же строки.
            if(positionPtr->second == position2Ptr->second)
            {
                QChar c;
                if(positionPtr->second + 1 < matrix.size())
                    c = matrix.at(positionPtr->first).at(positionPtr->second + 1);
                else
                    c = matrix.at(positionPtr->first).at(0);
                encryptedText += c;
                if(position2Ptr->second + 1 < matrix.size())
                    c = matrix.at(position2Ptr->first).at(position2Ptr->second + 1);
                else
                    c = matrix.at(position2Ptr->first).at(0);
                encryptedText += c;
            }
            else
            {
                //Если символы биграммы исходного текста встречаются в одном столбце, то они преобразуются в символы того же столбца,
                //находящимися непосредственно под ними. Если символ является нижним в столбце, то он заменяется на первый символ этого же столбца.

                if(positionPtr->first == position2Ptr->first)
                {
                    QChar c;
                    if(positionPtr->first + 1 < matrix.size())
                        c = matrix.at(positionPtr->first + 1).at(positionPtr->second);
                    else
                        c = matrix.at(0).at(positionPtr->second);
                    encryptedText += c;
                    if(position2Ptr->first + 1 < matrix.size())
                        c = matrix.at(position2Ptr->first + 1).at(position2Ptr->second);
                    else
                        c = matrix.at(0).at(position2Ptr->second);
                    encryptedText += c;
                }
                else
                {
                    //Если символы биграммы исходного текста находятся в разных столбцах и разных строках, то они заменяются на символы,
                    //находящиеся в тех же строках, но соответствующие другим углам прямоугольника.
                    encryptedText += matrix.at(positionPtr->first).at(position2Ptr->second);
                    encryptedText += matrix.at(position2Ptr->first).at(positionPtr->second);
                }
            }
        }
        else
        {
            error_ = tr("Не удалось найти один из символов \"%1\" \"%2\" в словаре").arg(copyText.at(i), copyText.at(i+1));
        }
    }
    return encryptedText;
}

QString PlayfairCipher::decrypt(const QString &encryptedText)
{
    auto copyText = encryptedText;
    if(encryptedText.size() % 2 == 1)
        copyText += ' ';

    error_ = "";

    auto matrix = dict_->makeSquareDictionaryMatrix(key_);

    QString decryptedText;
    for(int i = 0; i < copyText.size(); i+=2)
    {
        //Если два символа биграммы совпадают, добавляем после первого символа «Х», зашифровываем новую пару символов и продолжаем.

        auto positionPtr = MyAlgo::findPosition(matrix, copyText.at(i));
        auto position2Ptr = MyAlgo::findPosition(matrix, copyText.at(i+1));
        if(positionPtr && position2Ptr)
        {
            //Если символы биграммы исходного текста встречаются в одной строке, то эти символы замещаются на символы,
            //расположенные в ближайших столбцах справа от соответствующих символов.
            //Если символ является последним в строке, то он заменяется на первый символ этой же строки.
            if(positionPtr->second == position2Ptr->second)
            {
                QChar c;
                if(positionPtr->second - 1 > 0)
                    c = matrix.at(positionPtr->first).at(positionPtr->second - 1);
                else
                    c = matrix.at(positionPtr->first).at(matrix.size() - 1);
                decryptedText += c;
                if(position2Ptr->second - 1 > 0)
                    c = matrix.at(position2Ptr->first).at(position2Ptr->second - 1);
                else
                    c = matrix.at(position2Ptr->first).at(matrix.size() - 1);
                decryptedText += c;
            }
            else
            {
                //Если символы биграммы исходного текста встречаются в одном столбце, то они преобразуются в символы того же столбца,
                //находящимися непосредственно под ними. Если символ является нижним в столбце, то он заменяется на первый символ этого же столбца.

                if(positionPtr->first == position2Ptr->first)
                {
                    QChar c;
                    if(positionPtr->first - 1 > 0)
                        c = matrix.at(positionPtr->first - 1).at(positionPtr->second);
                    else
                        c = matrix.at(matrix.size() - 1).at(positionPtr->second);
                    decryptedText += c;
                    if(position2Ptr->first - 1 > 0)
                        c = matrix.at(position2Ptr->first - 1).at(position2Ptr->second);
                    else
                        c = matrix.at(matrix.size() - 1).at(position2Ptr->second);
                    decryptedText += c;
                }
                else
                {
                    //Если символы биграммы исходного текста находятся в разных столбцах и разных строках, то они заменяются на символы,
                    //находящиеся в тех же строках, но соответствующие другим углам прямоугольника.
                    decryptedText += matrix.at(positionPtr->first).at(position2Ptr->second);
                    decryptedText += matrix.at(position2Ptr->first).at(positionPtr->second);
                }
            }
            if(decryptedText.at(decryptedText.size() - 1) == L'.')
            {
                decryptedText[decryptedText.size() - 1] = decryptedText.at(decryptedText.size() - 2);
            }
        }
        else
        {
            error_ = tr("Не удалось найти один из символов \"%1\" \"%2\" в словаре").arg(copyText.at(i), copyText.at(i+1));
        }
    }
    return decryptedText;
}

QString PlayfairCipher::defaultKey() const
{
    return "плейфер";
}

bool PlayfairCipher::setKey(const QString &key)
{
    key_ = key;

    return true;
}
