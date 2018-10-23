#include "dbmanager.h"
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
    REQUIRE(dbManager.insertMessage(QUuid::createUuid().toString(), "test title", "test preview",
                "this is a test message", QIcon::fromTheme("edit", QIcon()), 1,
                QDateTime::currentDateTime().toString(), 1, 10,
                QUuid::createUuid().toString(), QUuid::createUuid().toString()
                ));
    REQUIRE(dbManager.insertMessage(QUuid::createUuid().toString(), "test title", "test preview",
                "this is a test message", QIcon::fromTheme("edit-undo", QIcon()), 1,
                QDateTime::currentDateTime().toString(), 1, 10,
                QUuid::createUuid().toString(), QUuid::createUuid().toString()
                ));
    REQUIRE(dbManager.insertMessage(QUuid::createUuid().toString(), "test title", "test preview",
                "this is a test message", QIcon(), 1,
                QDateTime::currentDateTime().toString(), 1, 10,
                QUuid::createUuid().toString(), QUuid::createUuid().toString()
                ));
    query.exec("SELECT * FROM messages");
    QSqlRecord record = query.record();
    // REQUIRE(query.size() == 3);      //SQLITE does not support this method
    int count = 0;
    while (query.next()) {
        ++count;
        qDebug() << QString("message %1: uuid: %2 title: %3 content: %4").arg(count).arg(query.value(0).toString()).arg(query.value(1).toString()).arg(query.value(3).toString());
    }
    REQUIRE(count == 3);
}
