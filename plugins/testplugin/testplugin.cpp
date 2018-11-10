#include "testplugin.h"
#include "notificationcenter.h"
#include "ncglobal.h"
#include "ncdebug.h"
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
    QWidget *w = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(w);
    QPushButton *pb = new QPushButton(w);
    layout->addWidget(pb);
    w->setWindowTitle("test plugin");
    pb->setText("test button");
    return w;
}

QWidget* TestPlugin::settingsWidget()
{
    return new QWidget;
}
