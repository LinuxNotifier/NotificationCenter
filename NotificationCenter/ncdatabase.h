#ifndef NCDATABASE_H
#define NCDATABASE_H

#include "ncmessage.h"
#include "ncdatabase_p.h"
#include "ncdebug.h"
#include <QSqlDatabase>
#include <QObject>
#include <memory>

class NotificationCenter;
class QSqlDatabase;
class QIcon;
class QByteArray;
class NcDatabasePrivate;
class QSqlDatabase;

/**
 * This class manages storing data on local machine. Every plugin should
 * use QSqlQuery query(NcDatabase::instance().internalDatabase())
 * to get a query handle, and use it to create tables, query values, etc.
 */
class NcDatabase : public QObject
{
    Q_OBJECT
    public:
        static NcDatabase& instance();
        inline bool isValid() {
            return d_ptr->m_valid;
        };

        inline QSqlDatabase internalDatabase() {
            return d_ptr->m_db;
        };

    private:
        Q_DISABLE_COPY(NcDatabase);
        explicit NcDatabase(NotificationCenter *parent);
        ~NcDatabase();

        void initDatabase();

        shared_ptr<NcDatabasePrivate> d_ptr;
};

#endif // NCDATABASE_H
