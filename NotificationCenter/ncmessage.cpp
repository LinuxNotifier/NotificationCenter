#include "ncmessage.h"
#include "ncmessage_p.h"
#include "nclogging.h"
#include <QDateTime>

NcMessagePrivate::NcMessagePrivate(NcMessage *q_ptr) :
    q_ptr(q_ptr),
    m_createdTime(QDateTime::currentDateTime().toString())
{
    setIcon(":/images/ncmessage_default_icon.png");
    setDuration(NcMessage::Duration::Default);
}

NcMessagePrivate::~NcMessagePrivate()
{

}

const QString& NcMessagePrivate::createdTime() const
{
    return m_createdTime;
}

const QIcon& NcMessagePrivate::icon() const
{
    return m_icon;
}

NcMessagePrivate& NcMessagePrivate::setIcon(const QString& icon)
{
    m_icon = QIcon(icon);
    return *this;
}

NcMessagePrivate& NcMessagePrivate::setIcon(const QIcon& icon)
{
    m_icon = const_cast<QIcon&>(icon);
    return *this;
}

const QString& NcMessagePrivate::title() const
{
    return m_title;
}

NcMessagePrivate& NcMessagePrivate::setTitle(const QString& title)
{
    m_title = title;
    return *this;
}

const QString& NcMessagePrivate::preview() const
{
    return m_preview;
}

NcMessagePrivate& NcMessagePrivate::setPreview(const QString& preview)
{
    m_preview = preview;
    return *this;
}

const QString& NcMessagePrivate::content() const
{
    return m_content;
}

NcMessagePrivate& NcMessagePrivate::setContent(const QString& content)
{
    m_content = content;
    return *this;
}

const QString& NcMessagePrivate::sound() const
{
    return m_sound;
}

NcMessagePrivate& NcMessagePrivate::setSound(NcMessage::Sound sound)
{
    switch(sound) {
        case NcMessage::Sound::Quiet:
            setSound(QString());
            break;
        case NcMessage::Sound::Default:
        default:
            setSound(":/sounds/ncmessage_default_sound.wav");
    }
    return *this;
}

NcMessagePrivate& NcMessagePrivate::setSound(const QString& sound)
{
    m_sound = const_cast<QString&>(sound);
    return *this;
}

NcMessage::Priority NcMessagePrivate::priority() const
{
    return m_priority;
}

NcMessagePrivate& NcMessagePrivate::setPriority(NcMessage::Priority priority)
{
    m_priority = priority;
    return *this;
}

NcMessage::Action NcMessagePrivate::action() const
{
    return m_action;
}

NcMessagePrivate& NcMessagePrivate::setAction(NcMessage::Action action)
{
    switch (action) {
        // case NcMessagePrivate::Create:
        case NcMessage::Action::Create:
        case NcMessage::Action::Replace:
        case NcMessage::Action::GroupByNotificationId:
            m_action = action;
            break;
        default:
            m_action = NcMessage::Action::Create;
    }
    return *this;
}

int NcMessagePrivate::duration() const
{
    return m_duration;
}

NcMessagePrivate& NcMessagePrivate::setDuration(NcMessage::Duration duration)
{
    switch (duration) {
        case NcMessage::Duration::UntilConfirmation:
        case NcMessage::Duration::UntilShutdown:
            setDuration(static_cast<int>(duration));
        case NcMessage::Duration::Default:
        default:
            setDuration(NcMessagePrivate::default_duration);
    }
    return *this;
}

NcMessagePrivate& NcMessagePrivate::setDuration(int duration)
{
    if (duration <= 0) {
        NcMessage::Duration durationType = static_cast<NcMessage::Duration>(duration);
        if (durationType != NcMessage::Duration::UntilConfirmation && durationType != NcMessage::Duration::UntilShutdown) {
            qWarning() << QObject::tr("duration must be  greater than 0");
            setDuration(NcMessage::Duration::Default);
        }
    }
    m_duration = duration;
    return *this;
}

const QString& NcMessagePrivate::messageId() const
{
    return m_messageId;
}

NcMessagePrivate& NcMessagePrivate::setMessageId(const QString& messageId)
{
    m_messageId = messageId;
    return *this;
}

const QString& NcMessagePrivate::notificationId() const
{
    return m_notificationId;
}

NcMessagePrivate& NcMessagePrivate::setNotificationId(const QString& notificationId)
{
    m_notificationId = notificationId;
    return *this;
}

const QString& NcMessagePrivate::applicationId() const
{
    return m_applicationId;
}

NcMessagePrivate& NcMessagePrivate::setApplicationId(const QString& applicationId)
{
    m_applicationId = applicationId;
    return *this;
}

NcMessage::NcMessage() :
    d_ptr(new NcMessagePrivate(this))
{

}

NcMessage::~NcMessage()
{

}

const QString& NcMessage::createdTime() const
{
    // Q_D(NcMessage);
    return d_ptr->createdTime();
}

const QIcon& NcMessage::icon() const
{
    return d_ptr->icon();
}

NcMessage& NcMessage::setIcon(const QString& icon)
{
    d_ptr->setIcon(icon);
    return *this;
}

NcMessage& NcMessage::setIcon(const QIcon& icon)
{
    d_ptr->setIcon(icon);
    return *this;
}

const QString& NcMessage::title() const
{
    return d_ptr->title();
}

NcMessage& NcMessage::setTitle(const QString& title)
{
    d_ptr->setTitle(title);
    return *this;
}

const QString& NcMessage::preview() const
{
    return d_ptr->preview();
}

NcMessage& NcMessage::setPreview(const QString& preview)
{
    d_ptr->setPreview(preview);
    return *this;
}

const QString& NcMessage::content() const
{
    return d_ptr->content();
}

NcMessage& NcMessage::setContent(const QString& content)
{
    d_ptr->setContent(content);
    return *this;
}

const QString& NcMessage::sound() const
{
    return d_ptr->sound();
}

NcMessage& NcMessage::setSound(Sound sound)
{
    d_ptr->setSound(sound);
    return *this;
}

NcMessage& NcMessage::setSound(const QString& sound)
{
    d_ptr->setSound(sound);
    return *this;
}

NcMessage::Priority NcMessage::priority() const
{
    return d_ptr->priority();
}

NcMessage& NcMessage::setPriority(NcMessage::Priority priority)
{
    d_ptr->setPriority(priority);
    return *this;
}

NcMessage::Action NcMessage::action() const
{
    return d_ptr->action();
}

NcMessage& NcMessage::setAction(NcMessage::Action action)
{
    d_ptr->setAction(action);
    return *this;
}

int NcMessage::duration() const
{
    return d_ptr->duration();
}

NcMessage& NcMessage::setDuration(NcMessage::Duration duration)
{
    d_ptr->setDuration(duration);
    return *this;
}

NcMessage& NcMessage::setDuration(int duration)
{
    d_ptr->setDuration(duration);
    return *this;
}

const QString& NcMessage::messageId() const
{
    return d_ptr->messageId();
}

NcMessage& NcMessage::setMessageId(const QString& messageId)
{
    d_ptr->setMessageId(messageId);
    return *this;
}

const QString& NcMessage::notificationId() const
{
    return d_ptr->notificationId();
}

NcMessage& NcMessage::setNotificationId(const QString& notificationId)
{
    d_ptr->setNotificationId(notificationId);
    return *this;
}

const QString& NcMessage::applicationId() const
{
    return d_ptr->applicationId();
}

NcMessage& NcMessage::setApplicationId(const QString& applicationId)
{
    d_ptr->setApplicationId(applicationId);
    return *this;
}
