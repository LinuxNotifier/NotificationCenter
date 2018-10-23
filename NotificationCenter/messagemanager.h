#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <QObject>

class NotificationCenter;

/**
 * This class manages the lifetime of messages.
 */
class MessageManager : QObject
{
    Q_OBJECT
    public:
        MessageManager& instance();

    private:
        explicit MessageManager(NotificationCenter *parent);
        ~MessageManager();
        Q_DISABLE_COPY(MessageManager)
    
};

#endif // MESSAGEMANAGER_H
