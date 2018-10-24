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
class MessageManager : public QObject
{
    Q_OBJECT
    friend class NotificationCenter;

    public:
        explicit MessageManager(NotificationCenter *parent);
        ~MessageManager();

    signals:
        void newMessage(const NcMessage& message);
        void messageExpired(const QString& messageId);

    private slots:
        void messageClosed(const QString& messageId);

    private:
        bool insertMessage(const NcMessage& message);
        bool addMessage(const NcMessage& message);
    
};

#endif // MESSAGEMANAGER_H
