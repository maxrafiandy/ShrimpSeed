#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQuickImageProvider>
#include "mainqml.h"
#include "imageprovider.h"

QScopedPointer<MainQml> main_qml(new MainQml);
QQuickImageProvider *img_prov;
QObject *qml_root;
QImage q_img;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlEngine qml_engine;

    img_prov = new ImageProvider();
    qml_engine.addImageProvider(QLatin1String("stream"), img_prov);
    qml_engine.rootContext()->setContextProperty("main_qml", main_qml.data());
    QQmlComponent component(&qml_engine, QUrl(QStringLiteral("qrc:/main.qml")));
    qml_root = component.create();

    return app.exec();
}
