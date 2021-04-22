#include "trithemiuscipher.h"

#include "commonAlghorithms.h"
#include "dictionaries/cyrillicdictionary.h"

TrithemiusCipher::TrithemiusCipher(QObject *parent) : EncryptionAlgorithm(parent)
{
    dict_ = std::unique_ptr<CyrillicDictionary>(new CyrillicDictionary());
}

TrithemiusCipher::TrithemiusCipher(const QString &key, QObject *parent) : EncryptionAlgorithm(parent), key_(key)
{
    dict_ = std::unique_ptr<CyrillicDictionary>(new CyrillicDictionary());
    matrix_ = dict_->makeSquareDictionaryMatrix(key_);
}

QString TrithemiusCipher::encrypt(const QString &textForEncrypt)
{
    error_ = "";
    QString res;

    for(const QChar &ch : textForEncrypt)
    {
        auto foundPos = MyAlgo::findPosition(matrix_, ch);
        if(foundPos)
        {
            if((*foundPos).first == matrix_.size() - 1)
            {
                res.push_back(matrix_.at(0).at((*foundPos).second));
            }
            else
            {
                res.push_back(matrix_.at((*foundPos).first + 1).at((*foundPos).second));
            }
        }
        else
        {
            error_ = tr("Шифр не смог найти в матрице символ %1").arg(ch);
            break;
        }
    }

    return res;
}

QString TrithemiusCipher::decrypt(const QString &encryptedText)
{
    error_ = "";
    QString res;

    for(const QChar &ch : encryptedText)
    {
        auto foundPos = MyAlgo::findPosition(matrix_, ch);
        if(foundPos)
        {
            if((*foundPos).first == 0)
            {
                res.push_back(matrix_.at(matrix_.size() - 1).at((*foundPos).second));
            }
            else
            {
                res.push_back(matrix_.at((*foundPos).first - 1).at((*foundPos).second));
            }
        }
        else
        {
            error_ = tr("Шифр не смог найти в матрице символ %1").arg(ch);
            break;
        }
    }

    return res;
}

QString TrithemiusCipher::defaultKey() const
{
    return "трисемус";
}

bool TrithemiusCipher::setKey(const QString &key)
{
    key_ = key;
    matrix_ = dict_->makeSquareDictionaryMatrix(key_);

    return true;
}
