#include "notifier.h"
#include "notification.h"
#include "notificationcenter.h"
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
    m_index(count++)
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

    NotificationCenter &nc = NotificationCenter::instance();
    connect(this, SIGNAL(notificationExpired(const QString)), &nc, SIGNAL(notificationExpired(const QString)));
    connect(this, SIGNAL(notificationClosed(const QString)), &nc, SIGNAL(notificationClosed(const QString)));

    connect(&nc, SIGNAL(notificationExpired(const QString)), this, SLOT(onNotificationExpired(const QString)));

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

void Notifier::setCentralWidget(QWidget *widget)
{
    centralWidget = widget;
}

void Notifier::setMasterWidget(QWidget *widget)
{
    masterWidget = widget;
}

void Notifier::setNotification(std::shared_ptr<Notification> notification)
{
    m_notification = notification;
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *title = new QLabel(this);
    title->setText(notification->title());
    layout->addWidget(title);
    QLabel *content = new QLabel(this);
    content->setText(notification->content());
    layout->addWidget(content);
    QHBoxLayout *signalLayout = new QHBoxLayout;
    QPushButton *expireButton = new QPushButton;
    QPushButton *closeButton = new QPushButton;
    expireButton->setText("ExpireMe");
    closeButton->setText("CloseMe");
    signalLayout->addWidget(expireButton);
    signalLayout->addWidget(closeButton);
    layout->addLayout(signalLayout);

    notificationIndexMap[notification->notificationId()] = m_index;

    // NotificationCenter &nc = NotificationCenter::instance();
    // connect(expireButton, SIGNAL(clicked(bool)), &nc, SIGNAL(notificationExpired(const QString)));
    connect(expireButton, SIGNAL(clicked(bool)), this, SLOT(onExpireClicked()));
    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(onCloseClicked()));
}

void Notifier::showEvent(QShowEvent *event)
{
    onReposition();
}

void Notifier::onNotificationExpired(const QString notificationId)
{
    if (notificationId == m_notification->notificationId()) {
        hide();
        deleteLater();
    }
}

void Notifier::onReposition(bool indexChaned)
{
    QPoint p = masterWidget->pos() + QPoint(-420, 112 * (count - m_index - 1) + 30);
    if (indexChaned) {
        QPropertyAnimation *reindexAnimation = new QPropertyAnimation(this, "pos", this);
        reindexAnimation->setDuration(200);
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
    emit notificationExpired(m_notification->notificationId());
}

void Notifier::onCloseClicked()
{
    emit notificationClosed(m_notification->notificationId());
    hide();
    deleteLater();
}
