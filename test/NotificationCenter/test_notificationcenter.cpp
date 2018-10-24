#include "notificationcenter.h"
#include "ncmessage.h"
#include "messagemanager.h"
#include "nclogging.h"
#include <QApplication>
#include <Catch2/catch.hpp>

TEST_CASE("test NotificationCenter", "[notificationcenter]") {
    qSetMessagePattern("[%{type}] " __FILENAME__ ":%{line} <%{function}> %{message}");
    int argc = 1;
    char *argv[] = {(char *)"./test_main"};
    QApplication app(argc, argv);
    NotificationCenter &nc = NotificationCenter::instance();
    MessageManager msgManager(&nc);
    nc.setMessageModel(&msgManager);
    NcMessage &msg = NotificationCenter::createMessage();
    msg.setTitle("hello")
        .setContent("hello world");
    REQUIRE(NotificationCenter::notify(msg));
    REQUIRE(!NotificationCenter::notify(msg));
}
