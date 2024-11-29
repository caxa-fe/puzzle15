#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "gameboard.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    GameBoard model;
    qmlRegisterType<GameBoard>("Game", 1,0, "GameBoardModel");
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Qml_15Game", "Main");

    return app.exec();
}
