#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <QObject>

class NotificationCenter;
class NotificationCenterPrivate;
class NcMessage;
class QString;

/**
 * This class manages the lifetime of messages.
 */
class MessageManager : QObject
{
    Q_OBJECT

    friend class NotificationCenter;
    friend class NotificationCenterPrivate;

    public:

    signals:
        void newMessage(const NcMessage& message);
        void messageExpired(const QString& messageId);

    private slots:
        void messageClosed(const QString& messageId);

    private:
        explicit MessageManager(NotificationCenter *parent);
        ~MessageManager();
        Q_DISABLE_COPY(MessageManager)

        bool insertMessage(const NcMessage& message);

        bool addMessage(const NcMessage& message);
    
};

#endif // MESSAGEMANAGER_H
