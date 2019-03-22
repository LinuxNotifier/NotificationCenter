#include "testplugin.h"
#include "notifyme.h"
#include "notificationcenter.h"
#include "global.h"
#include "debug.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

TestPlugin::TestPlugin() :
    QObject()
{
    qDebug() << "construct testplugin";
}

TestPlugin::~TestPlugin()
{
    qDebug() << "deconstruct testplugin";
}

bool TestPlugin::initialize(NotificationCenter *nc)
{
    return true;
}

QJsonObject TestPlugin::metadata() const
{
    QJsonObject json;
    return json;
}

QWidget* TestPlugin::centralWidget()
{
    NotifyMe *w = new NotifyMe;
    return w;
}

QWidget* TestPlugin::settingsWidget()
{
    return new QWidget;
}
