#ifndef NCDATABASE_P_H
#define NCDATABASE_P_H

#include <QSqlDatabase>

class Database;

class DatabasePrivate
{
    friend class Database;

    public:
        ~DatabasePrivate();

    private:
        DatabasePrivate(Database *q_ptr);

        bool m_valid = false;
        QSqlDatabase m_db;

        QString m_dbName;

        Database *q_ptr = nullptr;
};

#endif // NCDATABASE_P_H
