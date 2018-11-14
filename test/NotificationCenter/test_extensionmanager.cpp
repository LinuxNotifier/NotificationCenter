#include "ncglobal.h"
#include "extensionmanager.h"
#include "notificationcenter.h"
#include <QApplication>
#include <Catch2/catch.hpp>

TEST_CASE("test ExtensionManager", "[plugin], [database]") {
    qSetMessagePattern("[%{type}] " __FILENAME__ ":%{line} <%{function}> %{message}");
    int argc = 1;
    char *argv[] = {(char *)"./test_main"};
    QApplication app(argc, argv);

    NotificationCenter &nc = NotificationCenter::instance();
    ExtensionManager extensionManager(&nc);
    nc.setPluginModel(&extensionManager);
    extensionManager.onPluginDisabled("hello");
    extensionManager.onPluginRemoved("hello");
    extensionManager.initPluginTable();
    extensionManager.loadExtensions();

}
