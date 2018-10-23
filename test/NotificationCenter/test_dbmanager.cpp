#include "dbmanager.h"
#include "notificationcenter.h"
#include "nclogging.h"
#include <QApplication>
#include <QDateTime>
#include <QUuid>
#include <QIcon>
#include <QSqlQuery>
#include <QSqlRecord>
#include <Catch2/catch.hpp>

TEST_CASE("test DatabaseManager", "[dbmanager], [database]") {

    int argc = 1;
    char *argv[] = {(char *)"./test_main"};
    QApplication app(argc, argv);
    DatabaseManager &dbManager = DatabaseManager::instance();
    QSqlQuery query(dbManager.internalDatabase());
    query.exec("DELETE FROM messages");
    query.exec("SELECT * FROM messages");
    QSqlRecord record = query.record();
    // REQUIRE(query.size() == 4);      //SQLITE does not support this method
    int count = 0;
    while (query.next()) {
        ++count;
        qDebug() << QString("message %1: uuid: %2 title: %3 content: %4").arg(count).arg(query.value(0).toString()).arg(query.value(1).toString()).arg(query.value(3).toString());
    }
    REQUIRE(count == 0);


    REQUIRE(dbManager.insertMessage(QUuid::createUuid().toString(), "title1", "test preview",
                "content1", QIcon::fromTheme("edit", QIcon()), 1,
                QDateTime::currentDateTime().toString(), 1, 10,
                QUuid::createUuid().toString(), QUuid::createUuid().toString()
                ));
    REQUIRE(dbManager.insertMessage(QUuid::createUuid().toString(), "title2", "test preview",
                "content2", QIcon::fromTheme("edit-undo", QIcon()), 1,
                QDateTime::currentDateTime().toString(), 1, 10,
                QUuid::createUuid().toString(), QUuid::createUuid().toString()
                ));
    REQUIRE(dbManager.insertMessage(QUuid::createUuid().toString(), "title3", "test preview",
                "content3", QIcon(), 1,
                QDateTime::currentDateTime().toString(), 1, 10,
                QUuid::createUuid().toString(), QUuid::createUuid().toString()
                ));
    REQUIRE(!dbManager.insertMessage(QString(), "title3", "test preview",
                "content3", QIcon(), 1,
                QDateTime::currentDateTime().toString(), 1, 10,
                QUuid::createUuid().toString(), QUuid::createUuid().toString()
                ));
    NcMessage& msg = NotificationCenter::createMessage();
    msg.setTitle("title111")
        .setContent("content111");
    REQUIRE(!dbManager.insertMessage(msg));
    NotificationCenter::notify(msg);
    REQUIRE(!dbManager.insertMessage(msg));     // already inserted in NotificationCenter::notify

    query.exec("SELECT * FROM messages");
    record = query.record();
    count = 0;
    while (query.next()) {
        ++count;
        qDebug() << QString("message %1: uuid: %2 title: %3 content: %4").arg(count).arg(query.value(0).toString()).arg(query.value(1).toString()).arg(query.value(3).toString());
    }
    REQUIRE(count == 4);

    MessageList messageList = dbManager.selectAllMessages();
    REQUIRE(messageList.length() == 4);
    REQUIRE(messageList.at(0)->title() == "title1");
    REQUIRE(messageList.at(0)->content() == "content1");
    REQUIRE(messageList.at(1)->title() == "title2");
    REQUIRE(messageList.at(1)->content() == "content2");
    REQUIRE(messageList.at(2)->title() == "title3");
    REQUIRE(messageList.at(2)->content() == "content3");

    messageList = dbManager.selectAllMessages();
    REQUIRE(messageList.length() == 4);

    qDebug() << "title of message 4:" << messageList.at(3)->title();
    REQUIRE(messageList.at(3)->title() == "title111");
    qDebug() << "content of message 4:" << messageList.at(3)->content();
    REQUIRE(messageList.at(3)->content() == "content111");
}
