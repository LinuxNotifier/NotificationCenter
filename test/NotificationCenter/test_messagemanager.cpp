#include "messagemanager.h"
#include "notificationcenter.h"
#include "ncdebug.h"
#include <QApplication>
#include <QDateTime>
#include <QUuid>
#include <QIcon>
#include <QSqlQuery>
#include <QSqlRecord>
#include "ncdatabase.h"
#include <Catch2/catch.hpp>

TEST_CASE("test MessageManager", "[message], [database]") {
    qSetMessagePattern("[%{type}] " __FILENAME__ ":%{line} <%{function}> %{message}");
    int argc = 1;
    char *argv[] = {(char *)"./test_main"};
    QApplication app(argc, argv);

    NotificationCenter &nc = NotificationCenter::instance();

    MessageManager msgManager(&nc);
    nc.setMessageModel(&msgManager);
    NcDatabase &ncDb = NcDatabase::instance();
    QSqlQuery query(ncDb.internalDatabase());
    query.exec("DELETE FROM messages");
    query.exec("SELECT * FROM messages");
    QSqlRecord record = query.record();


    REQUIRE(msgManager.insertMessage(QUuid::createUuid().toString(), "title1", "test preview",
                "content1", QIcon::fromTheme("edit", QIcon()), 1,
                QDateTime::currentDateTime().toString(), 1, 10,
                QUuid::createUuid().toString(), QUuid::createUuid().toString()
                ));
    REQUIRE(msgManager.insertMessage(QUuid::createUuid().toString(), "title2", "test preview",
                "content2", QIcon::fromTheme("edit-undo", QIcon()), 1,
                QDateTime::currentDateTime().toString(), 1, 10,
                QUuid::createUuid().toString(), QUuid::createUuid().toString()
                ));
    REQUIRE(msgManager.insertMessage(QUuid::createUuid().toString(), "title3", "test preview",
                "content3", QIcon(), 1,
                QDateTime::currentDateTime().toString(), 1, 10,
                QUuid::createUuid().toString(), QUuid::createUuid().toString()
                ));
    REQUIRE(!msgManager.insertMessage(QString(), "title3", "test preview",
                "content3", QIcon(), 1,
                QDateTime::currentDateTime().toString(), 1, 10,
                QUuid::createUuid().toString(), QUuid::createUuid().toString()
                ));
    std::shared_ptr<NcMessage> msg(new NcMessage);
    msg->setTitle("title111")
        .setBody("content111");
    NotificationCenter::notify(msg);
    REQUIRE(!msgManager.insertMessage(msg));     // already inserted in NotificationCenter::notify

    query.exec("SELECT * FROM messages");
    record = query.record();
    int count = 0;
    while (query.next()) {
        ++count;
        qDebug() << QString("message %1: uuid: %2 title: %3 content: %4").arg(count).arg(query.value(0).toString()).arg(query.value(1).toString()).arg(query.value(3).toString());
    }
    REQUIRE(count == 4);

    MessageList messageList = msgManager.selectAllMessages();
    REQUIRE(messageList.length() == 4);
    REQUIRE(messageList.at(0)->title() == "title1");
    REQUIRE(messageList.at(0)->body() == "content1");
    REQUIRE(messageList.at(1)->title() == "title2");
    REQUIRE(messageList.at(1)->body() == "content2");
    REQUIRE(messageList.at(2)->title() == "title3");
    REQUIRE(messageList.at(2)->body() == "content3");

    messageList = msgManager.selectAllMessages();
    REQUIRE(messageList.length() == 4);

    qDebug() << "title of message 4:" << messageList.at(3)->title();
    REQUIRE(messageList.at(3)->title() == "title111");
    qDebug() << "content of message 4:" << messageList.at(3)->body();
    REQUIRE(messageList.at(3)->body() == "content111");
}
