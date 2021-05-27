#include "spiralcipher.h"

#include <QDebug>
#include <cmath>
#include <QRandomGenerator>

SpiralCipher::SpiralCipher(QObject *parent) : EncryptionAlgorithm(parent)
{

}


QString SpiralCipher::encrypt(const QString &textForEncrypt)
{
    auto data = textForEncrypt.split(",");
    auto ans = QString::number(pointToDist(data.at(0).toDouble(), data.at(1).toDouble()));

    //генерируем начальную рандомную точку
    auto randomPhi = QRandomGenerator::global()->generateDouble() * 2 * M_PI - 0.00001;
    int randomNumberOfCoils = QRandomGenerator::global()->generate() % 1000;

    //начинаем крутится по спирали и генерить х,у по которым будем смотреть буквы
    bool isFound = false;
    while(!isFound)
    {
        while(randomPhi < 2 * M_PI - 0.1)
        {
            //теперь у нас есть х,у для проверочки
            double x = randomNumberOfCoils / 2 / M_PI * randomPhi * cos(randomPhi);
            double y = randomNumberOfCoils / 2 / M_PI * randomPhi * sin(randomPhi);
            qDebug() << x << y << pointToDist(x, y);
            if(QRandomGenerator::global()->generate() % 1000 == 5)
            {
                isFound = true;
                qDebug() << "YA WSE";
                break;
            }
            randomPhi += QRandomGenerator::global()->generateDouble() / randomNumberOfCoils + 0.01;
        }
        randomNumberOfCoils++;
        randomPhi = 0.0;
    }



    return ans;
}

QString SpiralCipher::decrypt(const QString &encryptedText)
{

}

QString SpiralCipher::defaultKey() const
{
    return "спираль";
}

bool SpiralCipher::setKey(const QString &key)
{
    key_ = key;

    return true;
}

double SpiralCipher::pointToDist(double x, double y) const
{
    //x = a / 2 / pi * phi * cos(phi)
    //y = a / 2 / pi * phi * sin(phi)
    double phi = atan(y / x);
    double ro = sqrt( x * x + y * y ) +
            ( distanceBetweenCoils_ / 10 ); //ВОТ ЭТА ЧАСТЬ НУЖНА ДЛЯ ТОГО, ЧТОБЫ ЕСЛИ МЫ ЧУТКА ОШИБЛИСЬ В ТОЧНОСТИ ДАБЛА ОН НЕ ПОЛЕТЕЛ НА ВИТОК НАЗАД
    double calculated = 0.0;
    int numberOfCoils = 0;
    while(ro >= calculated)
    {
        calculated = distanceBetweenCoils_ / 2 / M_PI * ( 2 * M_PI * numberOfCoils );
        numberOfCoils += 1;
    }
    numberOfCoils -= 2;

    return polarToDist(phi + numberOfCoils * 2 * M_PI );
}

double SpiralCipher::polarToDist(double phi) const
{
    return ( static_cast<double>(distanceBetweenCoils_) / ( 4 * M_PI ) * ( phi * sqrt( 1 + phi * phi ) + log( phi + sqrt( 1 + phi * phi ) ) ) );
}
