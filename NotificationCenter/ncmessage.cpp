#include "ncmessage.h"
#include "ncmessage_p.h"
#include "ncdebug.h"
#include "ncglobal.h"
#include <QUuid>
#include <QDateTime>

NcMessagePrivate::NcMessagePrivate(NcMessage *q_ptr) :
    q_ptr(q_ptr)
{

}

NcMessagePrivate::~NcMessagePrivate()
{

}

NcMessage::NcMessage() :
    d_ptr(new NcMessagePrivate(this))
{
    setMessageId(QUuid::createUuid().toString());
    setCreatedTime(QDateTime::currentDateTime().toString());
    setIcon(":/images/ncmessage_default_icon.png");
    setDuration(Duration::Default);
}

NcMessage::~NcMessage()
{

}

QString NcMessage::createdTime() const
{
    return d_ptr->m_createdTime;
}

NcMessage& NcMessage::setCreatedTime(const QString& createdTime)
{
    d_ptr->m_createdTime = createdTime;
    return *this;
}

QIcon NcMessage::icon() const
{
    return d_ptr->m_icon;
}

NcMessage& NcMessage::setIcon(const QString& icon)
{
    d_ptr->m_icon = QIcon(icon);
    return *this;
}

NcMessage& NcMessage::setIcon(const QIcon& icon)
{
    if (!icon.pixmap(ICON_SIZE, ICON_SIZE).isNull())
        d_ptr->m_icon = const_cast<QIcon&>(icon);
    return *this;
}

QString NcMessage::title() const
{
    return d_ptr->m_title;
}

NcMessage& NcMessage::setTitle(const QString& title)
{
    d_ptr->m_title = title;
    return *this;
}

QString NcMessage::preview() const
{
    return d_ptr->m_preview;
}

NcMessage& NcMessage::setPreview(const QString& preview)
{
    d_ptr->m_preview = preview;
    return *this;
}

QString NcMessage::content() const
{
    return d_ptr->m_content;
}

NcMessage& NcMessage::setContent(const QString& content)
{
    d_ptr->m_content = content;
    return *this;
}

NcMessage::Priority NcMessage::priority() const
{
    return d_ptr->m_priority;
}

NcMessage& NcMessage::setPriority(Priority priority)
{
    d_ptr->m_priority = priority;
    return *this;
}

NcMessage::Action NcMessage::action() const
{
    return d_ptr->m_action;
}

NcMessage& NcMessage::setAction(Action action)
{
    switch (action) {
        // case NcMessage::Create:
        case Action::Create:
        case Action::Replace:
        case Action::GroupByNotificationId:
            d_ptr->m_action = action;
            break;
        default:
            d_ptr->m_action = Action::Create;
    }
    return *this;
}

int NcMessage::duration() const
{
    return d_ptr->m_duration;
}

NcMessage& NcMessage::setDuration(Duration duration)
{
    switch (duration) {
        case Duration::UntilConfirmation:
        case Duration::UntilShutdown:
            setDuration(static_cast<int>(duration));
        case Duration::Default:
        default:
            setDuration(NcMessagePrivate::default_duration);
    }
    return *this;
}

NcMessage& NcMessage::setDuration(int duration)
{
    if (duration <= 0) {
        Duration durationType = static_cast<Duration>(duration);
        if (durationType != Duration::UntilConfirmation && durationType != Duration::UntilShutdown) {
            qWarning() << QObject::tr("duration must be  greater than 0");
            setDuration(Duration::Default);
        }
    }
    d_ptr->m_duration = duration;
    return *this;
}

QString NcMessage::messageId() const
{
    return d_ptr->m_messageId;
}

NcMessage& NcMessage::setMessageId(const QString& messageId)
{
    d_ptr->m_messageId = messageId;
    return *this;
}

QString NcMessage::notificationId() const
{
    return d_ptr->m_notificationId;
}

NcMessage& NcMessage::setNotificationId(const QString& notificationId)
{
    d_ptr->m_notificationId = notificationId;
    return *this;
}

QString NcMessage::applicationId() const
{
    return d_ptr->m_applicationId;
}

NcMessage& NcMessage::setApplicationId(const QString& applicationId)
{
    d_ptr->m_applicationId = applicationId;
    return *this;
}

bool NcMessage::isValid() const
{
    return d_ptr->valid;
}

NcMessage& NcMessage::setValid(bool valid)
{
    d_ptr->valid = valid;
    return *this;
}
