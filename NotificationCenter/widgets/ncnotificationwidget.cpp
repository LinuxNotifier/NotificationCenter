#include "ncnotificationwidget.h"
#include "ncmessage.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QIcon>
#include <QPushButton>
#include <QDebug>

NcNotificationWidget::NcNotificationWidget(QWidget *parent) :
    NcNotificationBaseWidget(parent)
{

    m_mainLayout->setAlignment(Qt::AlignTop);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(3);
    // m_mainLayout->addStretch();


    // TODO: change to close icon
    m_closeButton = new QPushButton(this);
    // m_closeButton->setText("close");
    m_closeButton->setIcon(QIcon(":/imgs/clear.png"));
    // m_closeButton->resize(10, 10);
    m_closeButton->resize(15, 15);
    m_closeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_frameLayout->addWidget(m_closeButton, Qt::AlignLeft);
    // m_frameLayout->addWidget(m_closeButton, Qt::AlignRight);
    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(close()));
    //
    // setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

NcNotificationWidget::~NcNotificationWidget()
{
    qDebug() << "size of notificaiton widget: " << size();
    qDebug() << "size of close button: " << m_closeButton->size();
    qDebug() << "geometry of close button: " << m_closeButton->geometry();
}

/**
 * add a message to the notification widget
 *
 * \note the notification widget will use the first message's
 *          icon as the default title bar icon
 */

// 標題應該是自動滑動展示（如果標題過長的話）, 如果內容過長，可以生成preview
// 如果preview已經被指定，而且也過長，那麼滑動展示 (only when this notification is activated,
// otherwise it would be a mess}
bool NcNotificationWidget::addMessage(shared_ptr<NcMessage> message)
{
    // FIXME: the close button will be push off the title bar
    // when the content is too long
    m_messageList[message->messageId()] = message;
    // QLabel *messageLabel = new QLabel(this);
    // messageLabel->setText(message->content());
    // messageLabel->setWindowTitle(message->title());
    // messageLabel->setWindowIcon(QIcon(":/imgs/n.png"));
    // // setWidget(messageLabel);
    // m_messageLayout->addWidget(messageLabel);

    // TODO: don't add titleLabel if the title is empty
    QWidget *messageWidget = new QWidget(this);
    // messageWidget->setMaximumHeight(200);
    QVBoxLayout *messageLayout = new QVBoxLayout(messageWidget);
    QLabel *titleLabel = new QLabel(messageWidget);
    QLabel *contentLabel = new QLabel(messageWidget);
    titleLabel->setText(message->title());
    contentLabel->setText(message->content());
    titleLabel->setFixedHeight(20);
    // titleLabel->setStyleSheet("QLabel {background-color: yellow;}");
    // contentLabel->setStyleSheet("QLabel {background-color: red;}");
    titleLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    contentLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    messageLayout->addWidget(titleLabel);
    messageLayout->addWidget(contentLabel);
    messageLayout->addStretch();
    messageWidget->setStyleSheet("QWidget {background-color: grey;}");
    // FIXME: fix to expanding, but with maximum of filling it
    messageWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // messageWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_messageLayout->insertWidget(0, messageWidget);

    // TODO: elided text plugins/myplugin/notifydelegate.cpp
    // time label
    // clickable


    return true;
}

bool NcNotificationWidget::removeMessage(QString& msgId)
{
    qDebug() << "size of notification widget: " << size();
    int count = m_messageList.remove(msgId);
    if (m_messageList.empty())
        emit close();
    return static_cast<bool>(count);
}
