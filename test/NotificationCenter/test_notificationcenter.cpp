#include "notificationcenter.h"
#include "ncmessage.h"
#include <Catch2/catch.hpp>

TEST_CASE("test NotificationCenter", "[notificationcenter]") {
    NcMessage &msg = NotificationCenter::createMessage();
    msg.setTitle("hello")
        .setContent("hello world");
    REQUIRE(NotificationCenter::notify(msg));
}
