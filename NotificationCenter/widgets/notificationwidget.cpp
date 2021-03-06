#include "notificationwidget.h"
#include "global.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QIcon>
#include <QDebug>

NotificationWidget::NotificationWidget(QWidget *parent) :
    Widget(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(3);
    // m_mainLayout->addStretch();


    // TODO: change to close icon
    m_closeButton = new QPushButton(this);
    m_closeButton->setIcon(QIcon(":/images/notificationwidget_clear_notification.png"));
    m_closeButton->resize(ICON_SIZE, ICON_SIZE);
    // m_closeButton->resize(4, 4);
    m_closeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // m_frameLayout->addWidget(m_closeButton, Qt::AlignLeft);
    m_frameLayout->addWidget(m_closeButton, Qt::AlignRight);
    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(close()));
    // setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
} 

NotificationWidget::~NotificationWidget()
{
    
}
