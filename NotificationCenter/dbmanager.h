#ifndef DatabaseManager_H
#define DatabaseManager_H

#include "ncmessage.h"
#include <QSqlDatabase>
#include <QObject>

class NotificationCenter;
class QSqlDatabase;
class QIcon;
class QByteArray;


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
        bool insertMessage(const NcMessage&);
        bool insertMessage(const QString& message_id, const QString& title,
            const QString& preview, const QString& content,
            const QIcon& icon, int action,
            const QString& created_time, int priority, int duration,
            const QString& notification_id, const QString& application_id);
        bool alterMessage(const NcMessage&);
        bool alterMessage(const QString& message_id, const QString& title,
            const QString& preview, const QString& content,
            const QIcon& icon, int action,
            const QString& created_time, int priority, int duration,
            const QString& notification_id, const QString& application_id);
        bool deleteMessage(const QString& message_id);
        /* this method return the first message with this message in database,
        thought there should be "always" at most one such message. */
        NcMessage& selectMessage(const QString& message_id);
        MessageList selectAllMessages();

        QSqlDatabase& internalDatabase();

    signals:

    private:
        Q_DISABLE_COPY(DatabaseManager);
        explicit DatabaseManager(NotificationCenter *parent);
        ~DatabaseManager();

        bool initDatabase();

        QSqlDatabase m_db;
    
};

#endif // DatabaseManager_H
