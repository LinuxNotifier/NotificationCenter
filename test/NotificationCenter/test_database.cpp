#include "database.h"
#include "notificationcenter.h"
#include "debug.h"
#include <QApplication>
#include <QDateTime>
#include <QUuid>
#include <QIcon>
#include <QSqlQuery>
#include <QSqlRecord>
#include <Catch2/catch.hpp>

TEST_CASE("test Database", "[database]") {

    qSetMessagePattern("[%{type}] " __FILENAME__ ":%{line} <%{function}> %{message}");
    int argc = 1;
    char *argv[] = {(char *)"./test_main"};
    QApplication app(argc, argv);
    Database &ncDb = Database::instance();
    QSqlQuery query(ncDb.internalDatabase());
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
}
