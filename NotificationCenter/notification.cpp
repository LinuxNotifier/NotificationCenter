#include "notification.h"
#include "notification_p.h"
#include "debug.h"
#include "global.h"
#include <QUuid>
#include <QDateTime>

NotificationPrivate::NotificationPrivate(Notification *q_ptr) :
    q_ptr(q_ptr)
{

}

NotificationPrivate::~NotificationPrivate()
{

}

Notification::Notification() :
    d_ptr(new NotificationPrivate(this))
{
    // setNotificationId(QUuid::createUuid().toString());
    // setCreatedTime(QDateTime::currentDateTime().toString());
    // setIcon(":/images/notification_default_icon.png");
    setDuration(Duration::Default);
    // TODO: set the applicationId as the extensionId
    setApplicationId("org.linuxnotifier.Notifier");
}

Notification::~Notification()
{
#if DEBUG
    qDebug() << "Notification:" << notificationId() << "destroyed";
#endif
}

QString Notification::notificationId() const
{
    return d_ptr->m_notificationId;
}

Notification& Notification::setNotificationId(const QString& notificationId)
{
    d_ptr->m_notificationId = notificationId;
    return *this;
}

QString Notification::applicationId() const
{
    return d_ptr->m_applicationId;
}

Notification& Notification::setApplicationId(const QString& applicationId)
{
    d_ptr->m_applicationId = applicationId;
    return *this;
}

QString Notification::title() const
{
    return d_ptr->m_title;
}

Notification& Notification::setTitle(const QString& title)
{
    d_ptr->m_title = title;
    return *this;
}

QIcon Notification::icon() const
{
    return d_ptr->m_icon;
}

Notification& Notification::setIcon(const QString& icon)
{
    d_ptr->m_icon = QIcon(icon);
    return *this;
}

Notification& Notification::setIcon(const QIcon& icon)
{
    if (!icon.pixmap(ICON_SIZE, ICON_SIZE).isNull())
        d_ptr->m_icon = const_cast<QIcon&>(icon);
    return *this;
}

QString Notification::preview() const
{
    return d_ptr->m_preview;
}

Notification& Notification::setPreview(const QString& preview)
{
    d_ptr->m_preview = preview;
    return *this;
}

QString Notification::content() const
{
    return d_ptr->m_content;
}

Notification& Notification::setContent(const QString& content)
{
    d_ptr->m_content = content;
    return *this;
}

QString Notification::data() const
{
    return d_ptr->m_data;
}

Notification& Notification::setData(const QString& data)
{
    d_ptr->m_data = data;
    return *this;
}

Notification::Priority Notification::priority() const
{
    return d_ptr->m_priority;
}

Notification& Notification::setPriority(Priority priority)
{
    d_ptr->m_priority = priority;
    return *this;
}

Notification::Duration Notification::duration() const
{
    return d_ptr->m_duration;
}

Notification& Notification::setDuration(Duration duration)
{
    d_ptr->m_duration = duration;
    return *this;
}

QString Notification::triggerTime() const
{
    return d_ptr->m_triggerTime;
}

Notification& Notification::setTriggerTime(const QString& triggerTime)
{
    d_ptr->m_triggerTime = triggerTime;
    return *this;
}

QString Notification::createdTime() const
{
    return d_ptr->m_createdTime;
}

Notification& Notification::setCreatedTime(const QString& createdTime)
{
    d_ptr->m_createdTime = createdTime;
    return *this;
}

bool Notification::isNew() const
{
    return d_ptr->m_isNew;
}

Notification& Notification::setIsNew(bool isNew)
{
    d_ptr->m_isNew = isNew;
    return *this;
}
