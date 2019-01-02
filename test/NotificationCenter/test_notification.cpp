#include "notification.h"
#include "notificationcenter.h"
#include <QApplication>
#include <QIcon>
#include <Catch2/catch.hpp>

TEST_CASE("test Notification", "[notification], [message]") {
    qSetMessagePattern("[%{type}] " __FILENAME__ ":%{line} <%{function}> %{message}");
    int argc = 1;
    char *argv[] = {(char *)"./test_main"};
    QApplication app(argc, argv);
    Notification msg;
    QIcon icon("test_icon");
    msg.setIcon(icon)
        .setTitle("test_title")
        .setPreview("test_preview")
        .setContent("test_content")
        .setDuration(Notification::Duration::UntilShutdown)
        .setPriority(Notification::Priority::High);
    // REQUIRE(msg.icon() == icon);
    REQUIRE(msg.title() == "test_title");
    REQUIRE(msg.preview() == "test_preview");
    REQUIRE(msg.content() == "test_content");
    REQUIRE(msg.duration() == Notification::Duration::UntilShutdown);
    REQUIRE(msg.priority() == Notification::Priority::High);
}
