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
    // setNotificationId(QUuid::createUuid().toString());
    // setCreatedTime(QDateTime::currentDateTime().toString());
    // setIcon(":/images/ncmessage_default_icon.png");
    setDuration(Duration::Default);
    setApplicationId("org.linuxnotifier.Notification");
}

NcMessage::~NcMessage()
{
#if DEBUG
    qDebug() << "NcMessage:" << notificationId() << "destroyed";
#endif
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

QString NcMessage::title() const
{
    return d_ptr->m_title;
}

NcMessage& NcMessage::setTitle(const QString& title)
{
    d_ptr->m_title = title;
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

QString NcMessage::data() const
{
    return d_ptr->m_data;
}

NcMessage& NcMessage::setData(const QString& data)
{
    d_ptr->m_data = data;
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

NcMessage::Duration NcMessage::duration() const
{
    return d_ptr->m_duration;
}

NcMessage& NcMessage::setDuration(Duration duration)
{
    d_ptr->m_duration = duration;
    return *this;
}

QString NcMessage::triggerTime() const
{
    return d_ptr->m_triggerTime;
}

NcMessage& NcMessage::setTriggerTime(const QString& triggerTime)
{
    d_ptr->m_triggerTime = triggerTime;
    return *this;
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

bool NcMessage::isNew() const
{
    return d_ptr->m_isNew;
}

NcMessage& NcMessage::setIsNew(bool isNew)
{
    d_ptr->m_isNew = isNew;
    return *this;
}
