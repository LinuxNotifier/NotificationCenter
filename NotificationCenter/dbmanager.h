#ifndef DatabaseManager_H
#define DatabaseManager_H

#include "ncmessage.h"
#include "dbmanager_p.h"
#include "nclogging.h"
#include <QSqlDatabase>
#include <QObject>
#include <QScopedPointer>

class NotificationCenter;
class QSqlDatabase;
class QIcon;
class QByteArray;
class DatabaseManagerPrivate;
class QSqlDatabase;

/**
 * This class manages storing data on local machine. Every plugin should
 * use QSqlQuery query(DatabaseManager::instance().internalDatabase())
 * to get a query handle, and use it to create tables, query values, etc.
 */
class DatabaseManager : public QObject
{
    Q_OBJECT
    public:
        static DatabaseManager& instance();
        inline bool isValid() {
            return d_ptr->m_valid;
        };

        inline QSqlDatabase internalDatabase() {
            return d_ptr->m_db;
        };

    private:
        Q_DISABLE_COPY(DatabaseManager);
        explicit DatabaseManager(NotificationCenter *parent);
        ~DatabaseManager();
        Q_DECLARE_PRIVATE(DatabaseManager)

        void initDatabase();

        QScopedPointer<DatabaseManagerPrivate> d_ptr;
};

#endif // DatabaseManager_H
