#include "notificationcenter.h"
#include "notification.h"
#include "notificationmanager.h"
#include "debug.h"
#include <unistd.h>
#include <QApplication>
#include <QUuid>
#include <Catch2/catch.hpp>

TEST_CASE("test NotificationCenter", "[notificationcenter]") {
    qSetMessagePattern("[%{type}] " __FILENAME__ ":%{line} <%{function}> %{message}");
    int argc = 1;
    char *argv[] = {(char *)"./test_main"};
    QApplication app(argc, argv);
    // NotificationCenter &nc = NotificationCenter::instance();
    // NotificationManager msgManager(&nc);
    // nc.setNotificationModel(&msgManager);
    // Notification msg;
    // msg.setTitle("hello")
    //     .setNotificationId(QUuid::createUuid().toString())
    //     .setApplicationId(QUuid::createUuid().toString())
    //     .setContent("hello world");
    // REQUIRE(NotificationCenter::notify(msg));
    // REQUIRE(NotificationCenter::notify(msg));
}
