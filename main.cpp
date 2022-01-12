#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "bemain.h"
#include "belang.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    BEMain beMain;
    engine.rootContext()->setContextProperty("beMain", &beMain);

    BELang beLang(&engine, {"en","es","ru"});
    engine.rootContext()->setContextProperty("beLang", &beLang);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) { if (!obj && url == objUrl) QCoreApplication::exit(-1); },
        Qt::QueuedConnection
    );
    engine.load(url);
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
