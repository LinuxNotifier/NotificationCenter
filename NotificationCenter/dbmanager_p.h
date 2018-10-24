#ifndef DBMANAGER_P_H
#define DBMANAGER_P_H

#include <QSqlDatabase>

class DatabaseManager;

class DatabaseManagerPrivate
{
    friend class DatabaseManager;

    public:
        ~DatabaseManagerPrivate();

    private:
        DatabaseManagerPrivate(DatabaseManager *q_ptr);
        Q_DECLARE_PUBLIC(DatabaseManager)

        bool m_valid = false;
        QSqlDatabase m_db;

        DatabaseManager *q_ptr;
};

#endif // DBMANAGER_P_H
