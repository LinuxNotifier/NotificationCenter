#include "notificationcenter.h"
#include "ncmessage.h"
#include "nclogging.h"
#include <QApplication>
#include <Catch2/catch.hpp>

TEST_CASE("test NotificationCenter", "[notificationcenter]") {
    int argc = 1;
    char *argv[] = {(char *)"./test_main"};
    QApplication app(argc, argv);
    NcMessage &msg = NotificationCenter::createMessage();
    msg.setTitle("hello")
        .setContent("hello world");
    REQUIRE(NotificationCenter::notify(msg));
}
