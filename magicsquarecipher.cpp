#include "magicsquarecipher.h"

MagicSquareCipher::MagicSquareCipher(QObject *parent) : EncryptionAlgorithm(parent)
{

}

MagicSquareCipher::MagicSquareCipher(const Matrix &magicSquare, QObject *parent) : EncryptionAlgorithm(parent)
{
    matrix_ = magicSquare;

    matrixSize_ = 0;
    std::size_t checkEqualsRowsSize = 0;

    //получаем размер квадрата
    for(std::size_t i = 0; i < matrix_.size(); i++)
    {
        matrixSize_ += matrix_[i].size();
        //проверяем на то, что матрица соответсвует по размеру
        if(checkEqualsRowsSize == 0)
        {
            checkEqualsRowsSize = matrix_[i].size();
        }
        else
        {
            if(checkEqualsRowsSize != matrix_[i].size())
            {
                error_ = QString("Строки в магическом квадрате обладают разной длиной! %1 %2").arg(checkEqualsRowsSize, matrix_[i].size());
            }
        }
    }
}

MagicSquareCipher::~MagicSquareCipher()
{

}

QString MagicSquareCipher::encrypt(const QString &textForEncrypt)
{
    QString res;

    if( matrixSize_ != static_cast<std::size_t>(textForEncrypt.size()) )
    {
        error_.append(QString("Количество символов в тексте не соответсвтует количеству значений в магическом квадрате"));
    }
    else
    {
        for(std::size_t i = 0; i < matrix_.size(); i++)
        {
            for(std::size_t j = 0; j < matrix_.at(i).size(); j++)
            {
                res += textForEncrypt.at(matrix_.at(i).at(j) - 1);
            }
        }
    }

    return res;
}

QString MagicSquareCipher::decrypt(const QString &encryptedText)
{
    if( matrixSize_ != static_cast<std::size_t>(encryptedText.size()) )
    {
        error_.append(QString("Количество символов в тексте не соответсвтует количеству значений в магическом квадрате"));
    }
    else
    {

    }
}
