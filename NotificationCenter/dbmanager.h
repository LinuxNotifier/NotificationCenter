#ifndef DatabaseManager_H
#define DatabaseManager_H

#include "ncmessage.h"
#include <QSqlDatabase>
#include <QObject>

class NotificationCenter;
class QSqlDatabase;
class QIcon;
class QByteArray;


class DatabaseManager : public QObject
{
    Q_OBJECT
    public:
        static DatabaseManager& instance();
        bool insertMessage(const QString& message_id, const QString& title,
            const QString& preview, const QString& content,
            const QIcon& icon, int action,
            const QString& created_time, int priority, int duration,
            const QString& notification_id, const QString& application_id);
        // bool insertMessage(const NcMessage&);
        bool alterMessage(const QString& message_id, const QString& title,
            const QString& preview, const QString& content,
            const QIcon& icon, int action,
            const QString& created_time, int priority, int duration,
            const QString& notification_id, const QString& application_id);
        // bool alterMessage(const NcMessage&);
        bool deleteMessage(const QString& message_id);
        // NcMessage& selectMessage(const QString& message_id);
        // MessageList& selectAllMessages();  

        QSqlDatabase& internalDatabase();

    signals:

    private:
        Q_DISABLE_COPY(DatabaseManager);
        explicit DatabaseManager(NotificationCenter *parent);
        ~DatabaseManager();

        bool initDatabase();

        QSqlDatabase m_db;
        NotificationCenter *m_notificationCenter;
    
};

#endif // DatabaseManager_H
