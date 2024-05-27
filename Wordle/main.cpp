#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "WordleLogic.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    WordleLogic wordleLogic;  // Instance of the WordleLogic

    engine.rootContext()->setContextProperty("wordleLogic", &wordleLogic);  // Expose the instance to QML

    const QUrl url(QStringLiteral("qrc:/main.qml"));  // Load the main QML file
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;  // Exit if no QML objects were loaded

    return app.exec();  // Start the Qt event loop
}
