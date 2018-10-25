#include "testplugin.h"
#include "notificationcenter.h"
#include "ncglobal.h"
#include "ncdebug.h"
#include <QWidget>

TestPlugin::TestPlugin()
{
    qDebug() << "construct testplugin";
}

TestPlugin::~TestPlugin()
{
    qDebug() << "deconstruct testplugin";
}

void TestPlugin::initialize(NotificationCenter *nc)
{
    
}

QWidget* TestPlugin::centralWidget()
{
    return new QWidget;
}

QWidget* TestPlugin::settingsWidget()
{
    return new QWidget;
}

QString TestPlugin::interfaceVersion() const
{
    return __INTERFACE_VERSION__;
}
