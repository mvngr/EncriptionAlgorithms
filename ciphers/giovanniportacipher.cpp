#include "giovanniportacipher.h"

#include "dictionaries/cyrillicdictionary.h"
#include "commonAlghorithms.h"

GiovanniPortaCipher::GiovanniPortaCipher(QObject *parent) : EncryptionAlgorithm(parent)
{
    dict_ = std::unique_ptr<CyrillicDictionary>(new CyrillicDictionary());
    matrix_ = dict_->mergeWithDictionary(*dict_, Numbers);
}

QString GiovanniPortaCipher::encrypt(const QString &textForEncrypt)
{
    error_ = "";
    QString res;

    QString copyText = textForEncrypt;
    if(textForEncrypt.size() % 2 == 1)
        copyText += ' ';

    for(int i = 0; i < copyText.size(); i+=2)
    {
        auto charPos = MyAlgo::findPosition(dict_->dictionary(), copyText.at(i));
        auto charPos2 = MyAlgo::findPosition(dict_->dictionary(), copyText.at(i + 1));

        if(charPos && charPos2)
        {
            res += matrix_.at(*charPos).at(*charPos2);
        }
        else
        {
            error_ = tr("Не удалось найти один из символов \"%1\" \"%2\" в словаре").arg(copyText.at(i), copyText.at(i+1));
        }
    }

    return res;
}

QString GiovanniPortaCipher::decrypt(const QString &encryptedText)
{
    error_ = "";
    QString res;

    QString copyText = encryptedText;

    for(int i = 0; i < copyText.size(); i++)
    {
        //находим элемент в двумерной матрице
        auto charPos = MyAlgo::findPosition(matrix_, copyText.at(i));

        //теперь смотрим строку и столбец

        if(charPos)
        {
            res += dict_->dictionary()[charPos->first];
            res += dict_->dictionary()[charPos->second];
        }
        else
        {
            error_ = tr("Не удалось найти символ в матрице \"%1\"").arg(copyText.at(i));
        }
    }

    return res;
}

QString GiovanniPortaCipher::defaultKey() const
{
    return "";
}

bool GiovanniPortaCipher::setKey(const QString &key)
{
    Q_UNUSED(key);
    return true;
}
