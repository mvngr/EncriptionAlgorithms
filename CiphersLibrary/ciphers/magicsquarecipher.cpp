#include "magicsquarecipher.h"

#include <QtMath>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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
    error_ = "";
    QString res;

    if( matrixSize_ != static_cast<std::size_t>(textForEncrypt.size()) )
    {
        error_ = QString("Количество символов в тексте не соответсвтует количеству значений в магическом квадрате");
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
    error_ = "";
    QString res(encryptedText.size());

    if( matrixSize_ != static_cast<std::size_t>(encryptedText.size()) )
    {
        error_.append(QString("Количество символов в тексте не соответсвтует количеству значений в магическом квадрате"));
    }
    else
    {
        for(int i = 0; i < encryptedText.size(); i++)
        {
            int row = i / matrix_.size();
            int column = i % matrix_.size();
            int cell = matrix_.at(row).at(column);
            res[cell - 1] = encryptedText.at(i);
        }
    }

    return res;
}

QString MagicSquareCipher::defaultKey() const
{
    return "4,9,2;3,5,7;8,1,6;";
}

bool MagicSquareCipher::setKey(const QString &key)
{
    bool res = true;

    std::size_t matrixSize = 0;
    Matrix newMatrix;

    QStringList rowList = key.split(";");
    for(int i = 0; i < rowList.size(); i++)
    {
        if(rowList.at(i).isEmpty())
            break;
        newMatrix.push_back(std::vector<int>());
        QStringList values = rowList.at(i).split(",");
        bool isOk = false;
        for(const auto &value : qAsConst(values))
        {
            int data = value.toInt(&isOk);
            if(!isOk)
            {
                res = false;
            }
            else
            {
                newMatrix.at(i).push_back(data);
            }
        }

        matrixSize += newMatrix.at(i).size();
        if(!res)
            break;
    }
    if(res)
    {
        matrix_ = newMatrix;
        matrixSize_ = matrixSize;
    }
    else
    {
        error_ = tr("Ошибка при распознавании ключа\nИспользуйте \",\" для разделения значений и \";\" для разделения строк");
    }

    return res;
}
