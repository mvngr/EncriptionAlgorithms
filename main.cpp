#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "ciphers/transpositioncipher.h"
#include "ciphers/magicsquarecipher.h"
#include "ciphers/caesarcipher.h"
#include "ciphers/gronsfeldcipher.h"
#include "ciphers/playfaircipher.h"

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
