#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "cipherstcpclient.h"

#include "ciphers/transpositioncipher.h"
#include "ciphers/magicsquarecipher.h"
#include "ciphers/caesarcipher.h"
#include "ciphers/gronsfeldcipher.h"
#include "ciphers/playfaircipher.h"
#include "ciphers/giovanniportacipher.h"
#include "ciphers/vigenerecipher.h"
#include "ciphers/trithemiuscipher.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<TranspositionCipher>("Ciphers.Transposition", 1, 0, "TranspositionCipher");
    qmlRegisterType<MagicSquareCipher>("Ciphers.MagicSquare", 1, 0, "MagicSquareCipher");
    qmlRegisterType<CaesarCipher>("Ciphers.Caesar", 1, 0, "CaesarCipher");
    qmlRegisterType<GronsfeldCipher>("Ciphers.Gronsfeld", 1, 0, "GronsfeldCipher");
    qmlRegisterType<PlayfairCipher>("Ciphers.Playfair", 1, 0, "PlayfairCipher");
    qmlRegisterType<GiovanniPortaCipher>("Ciphers.GiovanniPorta", 1, 0, "GiovanniPortaCipher");
    qmlRegisterType<VigenereCipher>("Ciphers.Vigenere", 1, 0, "VigenereCipher");
    qmlRegisterType<TrithemiusCipher>("Ciphers.Trithemius", 1, 0, "TrithemiusCipher");
    qmlRegisterType<CiphersTcpClient>("CiphersTcpClient", 1, 0, "TcpClient");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
