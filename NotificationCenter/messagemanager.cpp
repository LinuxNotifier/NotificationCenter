#include "messagemanager.h"
#include "notificationcenter.h"

MessageManager::MessageManager(NotificationCenter *parent) :
    QObject(parent)
{
    // TODO: connect signals
}

MessageManager::~MessageManager()
{
    
}

MessageManager& MessageManager::instance()
{
    static MessageManager messageManager(&NotificationCenter::instance());
    return messageManager;
}
