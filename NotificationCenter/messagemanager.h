#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include "ncmessage.h"
#include <QObject>
#include <memory>
#include "ncglobal.h"

class NotificationCenter;
class NotificationCenterPrivate;
class NcMessage;
class QString;
class NcDatabase;

/**
 * This class manages the lifetime of messages.
 */
class MessageManager : public QObject
{
    Q_OBJECT

    signals:
        void newMessage(std::shared_ptr<NcMessage> message);
        void messageExpired(const QString notificationId);

    private slots:
        void messageClosed(const QString notificationId);

    friend class NotificationCenter;

    public:
        explicit MessageManager(NotificationCenter *parent);
        ~MessageManager();

        inline bool isValid() {
            return m_valid;
        };

    private:
        void initMessageTable();
        void loadMessages();


        bool insertMessage(std::shared_ptr<NcMessage> message);
        bool insertMessage(const QString& notificationId, const
                QString& applicationId, const QString& title, const QIcon&
                icon, const QString& preview, const QString& content, const
                QString& data, int priority, int duration, const QString&
                triggerTime, const QString& createdTime);
        bool alterMessage(std::shared_ptr<NcMessage> message);
        bool alterMessage(const QString& notificationId, const QString&
                applicationId, const QString& title, const QIcon& icon, const
                QString& preview, const QString& data, const QString& content,
                int priority, int duration, const QString& triggerTime, const
                QString& created_time);
        bool deleteMessage(const QString& notificationId);
        /* this method return the first message with this message in database,
        thought there should be "always" at most one such message. */
        std::shared_ptr<NcMessage> selectMessage(const QString& notificationId);
        MessageList selectAllMessages();

        NcDatabase *m_ncDb = nullptr;
        MessageMap m_messageMap;
        bool m_valid = false;
};

#endif // MESSAGEMANAGER_H
