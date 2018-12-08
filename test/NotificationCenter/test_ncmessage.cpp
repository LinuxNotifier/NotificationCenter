#include "ncmessage.h"
#include "notificationcenter.h"
#include <QApplication>
#include <QIcon>
#include <Catch2/catch.hpp>

TEST_CASE("test NcMessage", "[ncmessage], [message]") {
    qSetMessagePattern("[%{type}] " __FILENAME__ ":%{line} <%{function}> %{message}");
    int argc = 1;
    char *argv[] = {(char *)"./test_main"};
    QApplication app(argc, argv);
    NcMessage msg;
    QIcon icon("test_icon");
    msg.setIcon(icon)
        .setTitle("test_title")
        .setPreview("test_preview")
        .setBody("test_content")
        .setDuration(100)
        .setPriority(NcMessage::Priority::High);
    // REQUIRE(msg.icon() == icon);
    REQUIRE(msg.title() == "test_title");
    REQUIRE(msg.preview() == "test_preview");
    REQUIRE(msg.body() == "test_content");
    REQUIRE(msg.duration() == 100);
    REQUIRE(msg.priority() == NcMessage::Priority::High);
}
