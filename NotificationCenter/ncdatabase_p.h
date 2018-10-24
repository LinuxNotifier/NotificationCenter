#ifndef NCDATABASE_P_H
#define NCDATABASE_P_H

#include <QSqlDatabase>

class NcDatabase;

class NcDatabasePrivate
{
    friend class NcDatabase;

    public:
        ~NcDatabasePrivate();

    private:
        NcDatabasePrivate(NcDatabase *q_ptr);

        bool m_valid = false;
        QSqlDatabase m_db;

        NcDatabase *q_ptr;
};

#endif // NCDATABASE_P_H
