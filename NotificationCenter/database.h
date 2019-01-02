#ifndef NCDATABASE_H
#define NCDATABASE_H

#include "notification.h"
#include "database_p.h"
#include "debug.h"
#include <QSqlDatabase>
#include <QObject>
#include <memory>

class NotificationCenter;
class QSqlDatabase;
class QIcon;
class QByteArray;
class DatabasePrivate;
class QSqlDatabase;

/**
 * This class manages storing data on local machine. Every plugin should
 * use QSqlQuery query(Database::instance().internalDatabase())
 * to get a query handle, and use it to create tables, query values, etc.
 */
class Database : public QObject
{
    Q_OBJECT
    public:
        static Database& instance();
        QString dbName() const;
        inline bool isValid() const {
            return d_ptr->m_valid;
        };

        inline QSqlDatabase internalDatabase() {
            return d_ptr->m_db;
        };

    private:
        Q_DISABLE_COPY(Database);
        explicit Database(NotificationCenter *parent);
        ~Database();

        void initDatabase();

        std::shared_ptr<DatabasePrivate> d_ptr;
};

#endif // NCDATABASE_H
