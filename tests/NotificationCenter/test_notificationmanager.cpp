#include "notificationmanager.h"
#include "notificationcenter.h"
#include "debug.h"
#include <QApplication>
#include <QDateTime>
#include <QUuid>
#include <QIcon>
#include <QSqlQuery>
#include <QSqlRecord>
#include "database.h"
#include <Catch2/catch.hpp>

TEST_CASE("test NotificationManager", "[notification], [database]") {
    qSetMessagePattern("[%{type}] " __FILENAME__ ":%{line} <%{function}> %{message}");
    int argc = 1;
    char *argv[] = {(char *)"./test_main"};
    QApplication app(argc, argv);

    NotificationCenter &nc = NotificationCenter::instance();

    NotificationManager msgManager(&nc);
    nc.setNotificationModel(&msgManager);
    Database &ncDb = Database::instance();
    QSqlQuery query(ncDb.internalDatabase());
    query.exec("DELETE FROM notifications");
    query.exec("SELECT * FROM notifications");
    QSqlRecord record = query.record();

    REQUIRE(msgManager.insertNotification(QUuid::createUuid().toString(),
                QUuid::createUuid().toString(), "title1",
                QIcon::fromTheme("edit", QIcon()), "test preview", "content1", "",
                1, 1, QDateTime::currentDateTime().toString(),
                QDateTime::currentDateTime().toString()                ));
    REQUIRE(msgManager.insertNotification(QUuid::createUuid().toString(),
                QUuid::createUuid().toString(), "title2",
                QIcon::fromTheme("edit-undo", QIcon()), "test preview",
                "content2",  "", 1, 1, QDateTime::currentDateTime().toString(),
                QDateTime::currentDateTime().toString()
                ));
    REQUIRE(msgManager.insertNotification(QUuid::createUuid().toString(),
                QUuid::createUuid().toString(), "title3",QIcon(), "test preview",
                "content3", "", 1, 1,
                QDateTime::currentDateTime().toString(),
                QDateTime::currentDateTime().toString()
                ));
    // fail because of invalid notificationId
    REQUIRE(!msgManager.insertNotification(QString(), QString(), "title3", QIcon(), 
                "test preview", "content3", "data", 1, 1,
                QDateTime::currentDateTime().toString(),
                QDateTime::currentDateTime().toString()
                ));
    std::shared_ptr<Notification> msg(new Notification);
    msg->setTitle("title111")
        .setNotificationId("aaa")
        .setApplicationId("bbb")
        .setContent("content111");
    NotificationCenter::notify(msg);
    qDebug() << "notificationId:" << msg->notificationId();
    REQUIRE(!msgManager.insertNotification(msg));    // this notification already exists

    query.exec("SELECT * FROM notifications");
    record = query.record();
    int count = 0;
    while (query.next()) {
        ++count;
        qDebug() << QString("notification %1: uuid: %2 title: %3 content: %4").arg(count)
            .arg(query.value(0).toString()).arg(query.value(2).toString())
            .arg(query.value(5).toString());
    }
    REQUIRE(count == 4);

    NotificationList notificationList = msgManager.selectAllNotifications();
    REQUIRE(notificationList.length() == 4);
    REQUIRE(notificationList.at(0)->title() == "title1");
    REQUIRE(notificationList.at(0)->content() == "content1");
    REQUIRE(notificationList.at(1)->title() == "title2");
    REQUIRE(notificationList.at(1)->content() == "content2");
    REQUIRE(notificationList.at(2)->title() == "title3");
    REQUIRE(notificationList.at(2)->content() == "content3");

    notificationList = msgManager.selectAllNotifications();
    REQUIRE(notificationList.length() == 4);

    qDebug() << "title of notification 4:" << notificationList.at(3)->title();
    REQUIRE(notificationList.at(3)->title() == "title111");
    qDebug() << "content of notification 4:" << notificationList.at(3)->content();
    REQUIRE(notificationList.at(3)->content() == "content111");
}
