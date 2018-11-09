#include "test_plugininterface.h"
#include "notificationcenter.h"
#include "ncglobal.h"
#include "ncdebug.h"
#include <QApplication>
#include <QWidget>
#include <Catch2/catch.hpp>

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

QJsonObject TestPlugin::metadata() const
{
    QJsonObject json;
    return json;
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
    return "0.0.1";
}

TEST_CASE("test PluginInterface", "[plugin], [interface]") {
    qSetMessagePattern("[%{type}] " __FILENAME__ ":%{line} <%{function}> %{message}");
    int argc = 1;
    char *argv[] = {(char *)"./test_main"};
    QApplication app(argc, argv);
    TestPlugin testPlugin;
    REQUIRE(testPlugin.interfaceVersion() == "0.0.1");
    testPlugin.centralWidget();
    testPlugin.settingsWidget();
}
