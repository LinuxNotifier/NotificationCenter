#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include "ncmessage.h"
#include <QObject>

class NotificationCenter;
class NotificationCenterPrivate;
class NcMessage;
class QString;
class DatabaseManager;

/**
 * This class manages the lifetime of messages.
 */
class MessageManager : public QObject
{
    Q_OBJECT
    friend class NotificationCenter;

    public:
        explicit MessageManager(NotificationCenter *parent);
        ~MessageManager();

        inline bool isValid();

    signals:
        void newMessage(const NcMessage& message);
        void messageExpired(const QString& messageId);

    private slots:
        void messageClosed(const QString& messageId);

    private:
        void initMessageTable();
        // bool addMessage(const NcMessage& message);
        bool insertMessage(const NcMessage&);
        bool insertMessage(const QString& messageId, const QString& title,
            const QString& preview, const QString& content,
            const QIcon& icon, int action,
            const QString& created_time, int priority, int duration,
            const QString& notificationId, const QString& applicationId);
        bool alterMessage(const NcMessage&);
        bool alterMessage(const QString& messageId, const QString& title,
            const QString& preview, const QString& content,
            const QIcon& icon, int action,
            const QString& created_time, int priority, int duration,
            const QString& notificationId, const QString& applicationId);
        bool deleteMessage(const QString& messageId);
        /* this method return the first message with this message in database,
        thought there should be "always" at most one such message. */
        NcMessage& selectMessage(const QString& messageId);
        MessageList selectAllMessages();

        DatabaseManager &m_dbManager;
        bool m_valid = false;
};

#endif // MESSAGEMANAGER_H
