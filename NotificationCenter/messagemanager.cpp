#include "messagemanager.h"
#include "dbmanager.h"
#include "notificationcenter.h"
#include "ncmessage.h"
#include "nclogging.h"

MessageManager::MessageManager(NotificationCenter *parent) :
    QObject(parent)
{
    connect(parent, SIGNAL(messageClosed(const QString&)), this, SLOT(messageClosed(const QString&)));
}

MessageManager::~MessageManager()
{
    
}

bool MessageManager::insertMessage(const NcMessage& message)
{
    return DatabaseManager::instance().insertMessage(message);
}

void MessageManager::messageClosed(const QString& messageId)
{
    qDebug() << "message closed:" << messageId;
}
