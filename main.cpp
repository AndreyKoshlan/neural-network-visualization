#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtGui>
#include <QtQuick3D/qquick3d.h>

#include "qml/instancetable.h"
#include "qml/controller.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    QSurfaceFormat::setDefaultFormat(QQuick3D::idealSurfaceFormat(4));

    qmlRegisterType<InstanceTable>("instancetable", 1, 0, "InstanceTable");
    qmlRegisterType<Controller>("controller", 1, 0, "Controller");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return a.exec();
}
