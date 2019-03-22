#include "notifier.h"
#include "notification.h"
#include "notificationevent.h"
#include "notificationservice.h"
#include "notificationcenter.h"
#include "notificationlistener.h"
#include "notificationwidget.h"
#include <QEvent>
#include <QMoveEvent>
#include <QVBoxLayout>
#include <QObject>
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <assert.h>

int Notifier::count = 0;
QWidget *Notifier::centralWidget = nullptr;
QWidget *Notifier::masterWidget = nullptr;
QHash<QString, int> Notifier::notificationIndexMap;

Notifier::Notifier(QWidget *parent) :
    QFrame(parent),
    m_index(count++),
    m_layout(new QVBoxLayout(this))
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | windowFlags());
    setObjectName("notifier");

    // make sure Notifier::setCentral/MasterWidget() is called before any instanization
    assert(centralWidget);  
    assert(masterWidget);

    resize(400, 100);
    move(QApplication::desktop()->screenGeometry().topRight()); // for slipping in effect

    // QPainterPath mask;
    // mask.addRoundedRect(rect(), 7, 7);
    // setMask(mask.toFillPolygon().toPolygon());

    connect(this, SIGNAL(notifierDestroyed(const int)), centralWidget, SIGNAL(notifierDestroyed(const int)));
    connect(centralWidget, SIGNAL(notifierDestroyed(const int)), this, SLOT(onNotifierDestroyed(const int)));

    connect(this, SIGNAL(reposition(bool)), centralWidget, SIGNAL(reposition(bool)));
    connect(masterWidget, SIGNAL(reposition(bool)), this, SLOT(onReposition(bool)));
    connect(centralWidget, SIGNAL(reposition(bool)), this, SLOT(onReposition(bool)));

    emit reposition(true);
}

Notifier::~Notifier()
{
    notificationIndexMap.remove(m_notification->notificationId());
    --count;    // this must be done before emitting notifierDestroyed()
    emit notifierDestroyed(m_index);
#if DEBUG
    qDebug() << "Notifier with" << m_notification->notificationId() << "deleted";
#endif
}

void Notifier::onNewNotifier()
{
    
}

void Notifier::onNotifierDestroyed(const int index)
{
    if (m_index > index)
        --m_index;
    onReposition(true);
}

void Notifier::initialize()
{
    // NotificationService::createNotificationChannel("org.linuxnotifier.Notifier", listener);
}

void Notifier::setCentralWidget(QWidget *widget)
{
    centralWidget = widget;
}

void Notifier::setMasterWidget(QWidget *widget)
{
    masterWidget = widget;
}

std::shared_ptr<Notification> Notifier::notification() const
{
    return m_notification;
}

void Notifier::setNotification(std::shared_ptr<Notification> notification)
{
    m_notification = notification;
    QLabel *title = new QLabel(this);
    title->setText(notification->title());
    m_layout->addWidget(title);
    QLabel *content = new QLabel(this);
    content->setText(notification->content() + '\n' + notification->notificationId());
    m_layout->addWidget(content);
    QHBoxLayout *signalLayout = new QHBoxLayout;
    QPushButton *expireButton = new QPushButton;
    QPushButton *closeButton = new QPushButton;
    expireButton->setText("ExpireMe");
    closeButton->setText("CloseMe");
    signalLayout->addWidget(expireButton);
    signalLayout->addWidget(closeButton);
    m_layout->addLayout(signalLayout);

    notificationIndexMap[notification->notificationId()] = m_index;

    connect(expireButton, SIGNAL(clicked(bool)), this, SLOT(onExpireClicked()));
    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(onCloseClicked()));
}

int Notifier::index() const
{
    return m_index;
}

void Notifier::showEvent(QShowEvent *event)
{
    onReposition();
}

void Notifier::onReposition(bool indexChaned)
{
    QPoint p = masterWidget->pos() + QPoint(-420, 112 * (count - m_index - 1) + 30);
    if (indexChaned) {
        QPropertyAnimation *reindexAnimation = new QPropertyAnimation(this, "pos", this);
        reindexAnimation->setDuration(300);
        reindexAnimation->setStartValue(pos());
        reindexAnimation->setEndValue(p);
        reindexAnimation->setEasingCurve(QEasingCurve::InOutQuad);
        reindexAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else {
        move(p);
    }
}

void Notifier::onExpireClicked()
{
    NotificationEvent *e = new NotificationEvent(NotificationEvent::Type::NotificationExpired);
    e->setNotificationId(m_notification->notificationId());
    NotificationService::postEvent(e);
}

void Notifier::onCloseClicked()
{
    NotificationEvent *e = new NotificationEvent(NotificationEvent::Type::NotificationRemoved);
    e->setNotificationId(m_notification->notificationId());
    NotificationService::postEvent(e);
}
