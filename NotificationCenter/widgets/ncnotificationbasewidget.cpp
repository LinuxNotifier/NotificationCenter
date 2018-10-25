#include "ncnotificationbasewidget.h"
#include "ncmessage.h"
#include <QVBoxLayout>
#include <QWidget>

NcNotificationBaseWidget::NcNotificationBaseWidget(QWidget *parent) :
    NcWidget(parent),
    m_messageWidget(new QWidget(this)),
    m_messageLayout(new QVBoxLayout(this))
    // NOTE: we cannot do like this, since the initialization order
    // of initialization list is unpredictable!!
    // m_messageLayout(new QVBoxLayout(m_messageWidget))
{
    m_messageLayout->addStretch();
    m_messageWidget->setLayout(m_messageLayout);
    m_mainLayout->addWidget(m_messageWidget);
    setMaximumHeight(100);
}

NcNotificationBaseWidget::~NcNotificationBaseWidget()
{
    
}

bool NcNotificationBaseWidget::addMessage(NcMessage *msg)
{
    m_messageList[msg->messageId()] = msg;
    return true;
}

bool NcNotificationBaseWidget::removeMessage(QString& msgId)
{
    int count = m_messageList.remove(msgId);
    if (m_messageList.empty())
        emit close();
    return static_cast<bool>(count);
}
