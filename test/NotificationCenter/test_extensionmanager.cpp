#include "ncglobal.h"
#include "extensionmanager.h"
#include "notificationcenter.h"
#include <QApplication>
#include <Catch2/catch.hpp>

TEST_CASE("test PluginManager", "[plugin], [database]") {
    qSetMessagePattern("[%{type}] " __FILENAME__ ":%{line} <%{function}> %{message}");
    int argc = 1;
    char *argv[] = {(char *)"./test_main"};
    QApplication app(argc, argv);

    NotificationCenter &nc = NotificationCenter::instance();
    PluginManager pluginManager(&nc);
    nc.setPluginModel(&pluginManager);
    pluginManager.onPluginDisabled("hello");
    pluginManager.onPluginRemoved("hello");
    pluginManager.initPluginTable();
    pluginManager.loadPlugins();

}
