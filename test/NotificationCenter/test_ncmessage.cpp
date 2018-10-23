#include "ncmessage.h"
#include "notificationcenter.h"
#include <Catch2/catch.hpp>
#include <QIcon>

TEST_CASE("test NcMessage", "[ncmessage], [message]") {
    NcMessage &msg = NotificationCenter::createMessage();
    QIcon icon("test_icon");
    msg.setIcon("test_icon")
        .setIcon(icon)
        .setTitle("test_title")
        .setPreview("test_preview")
        .setContent("test_content")
        .setSound("test_sound")
        .setDuration(100)
        .setPriority(NcMessage::Priority::High);
    // REQUIRE(msg.icon() == icon);
    REQUIRE(msg.title() == "test_title");
    REQUIRE(msg.preview() == "test_preview");
    REQUIRE(msg.content() == "test_content");
    REQUIRE(msg.sound() == "test_sound");
    REQUIRE(msg.duration() == 100);
    REQUIRE(msg.priority() == NcMessage::Priority::High);
}
