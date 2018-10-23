#ifndef DatabaseManager_H
#define DatabaseManager_H

#include <QSqlDatabase>
#include <QObject>

class NotificationCenter;
class QSqlDatabase;

class DatabaseManager : public QObject
{
    Q_OBJECT
    public:
        static DatabaseManager& instance();
        bool insertMessage(const QString& message_id, const QString& title,
            const QString& preview, const QString& content,
            const QString& icon, const QString& sound, int action,
            const QString& created_time, int priority, int duration,
            const QString& notification_id, const QString& application_id);
        bool alterMessage(const QString& message_id, const QString& title,
            const QString& preview, const QString& content,
            const QString& icon, const QString& sound, int action,
            const QString& created_time, int priority, int duration,
            const QString& notification_id, const QString& application_id);
        bool deleteMessage(const QString& message_id);
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
