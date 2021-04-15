#include "vigenerecipher.h"

#include "commonAlghorithms.h"
#include "dictionaries/cyrillicdictionary.h"

VigenereCipher::VigenereCipher(QObject *parent) : EncryptionAlgorithm(parent)
{
    dict_ = std::unique_ptr<CyrillicDictionary>(new CyrillicDictionary());
    matrix_ = dict_->mergeWithDictionary(*dict_);
}

VigenereCipher::VigenereCipher(const QString key, QObject *parent) : EncryptionAlgorithm(parent)
{
    dict_ = std::unique_ptr<CyrillicDictionary>(new CyrillicDictionary());
    matrix_ = dict_->mergeWithDictionary(*dict_);
}

QString VigenereCipher::encrypt(const QString &textForEncrypt)
{
    error_ = "";

    QString res;
    QString specialKey = repeatKeyToSize(textForEncrypt.size());

    for(int i = 0; i < specialKey.size(); i++)
    {
        auto rowNumber = MyAlgo::findPosition(dict_->dictionary(), specialKey.at(i));
        if(rowNumber)
        {
            auto colNumber = MyAlgo::findPosition(dict_->dictionary(), textForEncrypt.at(i));
            if(colNumber)
            {
                res.push_back(matrix_.at(*rowNumber).at(*colNumber));
            }
            else
            {
                error_ = tr("Шифр не смог найти сивол %1 в словаре!").arg(textForEncrypt.at(i));
                break;
            }
        }
        else
        {
            error_ = tr("Шифр не смог найти сивол %1 в словаре!").arg(specialKey.at(i));
            break;
        }
    }

    return res;
}

QString VigenereCipher::decrypt(const QString &encryptedText)
{
    error_ = "";

    QString res;
    QString specialKey = repeatKeyToSize(encryptedText.size());

    for(int i = 0; i < specialKey.size(); i++)
    {
        auto rowNumber = MyAlgo::findPosition(dict_->dictionary(), specialKey.at(i));
        if(rowNumber)
        {
            auto indexNumber = MyAlgo::findPosition(matrix_.at(*rowNumber), encryptedText.at(i));
            if(indexNumber)
            {
                res.push_back(dict_->dictionary().at(*indexNumber));
            }
            else
            {
                error_ = tr("Шифр не смог найти сивол %1 в словаре!").arg(encryptedText.at(i));
                break;
            }
        }
        else
        {
            error_ = tr("Шифр не смог найти сивол %1 в словаре!").arg(specialKey.at(i));
            break;
        }
    }

    return res;
}

QString VigenereCipher::defaultKey() const
{
    return "виженер";
}

bool VigenereCipher::setKey(const QString &key)
{
    key_ = key;

    return true;
}

QString VigenereCipher::repeatKeyToSize(const int size)
{
    QString res;
    for(int i = 0; i < size; i++)
    {
        res.push_back(key_.at(i % key_.size()));
    }

    return res;
}
