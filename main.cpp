#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "bgrmain.h"
#include "bgrlang.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    BGRMain bgrMain;
    engine.rootContext()->setContextProperty("bgrMain", &bgrMain);

    BGRLang bgrLang(&engine, {"en", "es", "ru"});
    engine.rootContext()->setContextProperty("bgrLang", &bgrLang);

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
