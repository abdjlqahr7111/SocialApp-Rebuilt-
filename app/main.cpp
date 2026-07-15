#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "databasehandler.h"
#include "camerahandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<DatabaseHandler>("SocialApp.Core", 1, 0, "DatabaseHandler");
    qmlRegisterType<CameraHandler>("SocialApp.Core", 1, 0, "CameraHandler");

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
    );

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
