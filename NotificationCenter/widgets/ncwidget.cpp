#include "ncwidget.h"
#include "ncglobal.h"
#include <QPropertyAnimation>
#include <QSizePolicy>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QStyleOption>
#include <QSize>

NcWidget::NcWidget(QWidget *parent) :
    QWidget(parent),
    m_widget(nullptr),
    m_frameWidget(new QWidget(this)),
    m_iconButton(new QPushButton(this)),
    m_titleLabel(new QLabel(this)),
    m_mainLayout(new QVBoxLayout),
    m_frameLayout(new QHBoxLayout)

{
    connect(this, SIGNAL(startUpApp()), this, SLOT(onStartUpApp()));
    // XXX: WARNING this will prevent it from receiving closeEvent!!
    // installEventFilter(this);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    setAttribute(Qt::WA_DeleteOnClose, true);

    setMinimumHeight(WIDGET_MINIMUM_HEIGHT);
    setMaximumHeight(WIDGET_MAXIMUM_HEIGHT_IN_PREVIEW);


    m_iconButton->resize(10, 10);
    m_iconButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // m_titleLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // m_frameLayout->setAlignment(Qt::AlignVCenter);


    // FIXME: don't know whether it does work yet.
    QSizePolicy sp_retain = sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    setSizePolicy(sp_retain);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_frameLayout->setContentsMargins(0, 0, 0, 0);
    m_frameLayout->addWidget(m_iconButton, Qt::AlignLeft);
    m_frameLayout->addWidget(m_titleLabel, Qt::AlignLeft | Qt::AlignVCenter);
    m_frameLayout->addStretch();
    m_frameWidget->setLayout(m_frameLayout);
    m_frameWidget->setStyleSheet("QWidget {border-width: 1px; background-color: grey;}");
    m_frameWidget->setFixedHeight(20);
    setStyleSheet("QWidget {border-width: 1px; background-color: green; border-color: red;}");

    // TODO: try to remove unneccessary m_frameWidget,
    // see https://forum.qt.io/topic/88586/adding-widgets-dynamically-to-layout-causes-to-them-to-be-misplaced/25
    m_mainLayout->addWidget(m_frameWidget);
    // m_frameWidget->hide();

    // m_mainLayout->addLayout(m_frameLayout, Qt::AlignTop);
    qDebug() <<"count of widgets after add frame layout: " << m_mainLayout->count();
    qDebug() << "the original layout is " << layout();
    // FIXME: alreay has a layout, but where?
    setLayout(m_mainLayout);
    qDebug() << "the later layout is " << layout();
    printf("**[13]**\n");

    // setMaskWidth(10);


}

int NcWidget::maskWidth() const
{
    return m_maskWidth;
}

void NcWidget::setMaskWidth(int maskWidget)
{
    m_maskWidth = maskWidget;
    setMask(QRegion(QRect(0, 0, m_maskWidth, height())));
}

bool NcWidget::isCallable()
{
    return m_callable;
}

void NcWidget::setCallable(bool callable)
{
    m_callable = callable;
    if (m_callable) {
        // TODO: set button clickable
        connect(m_iconButton, SIGNAL(clicked(bool)), this, SLOT(onStartUpApp()));
    }
    else {
        disconnect(m_iconButton, SIGNAL(clicked(bool)), this, SLOT(onStartUpApp()));
    }
}

bool NcWidget::eventFilter(QObject *watched, QEvent *event)
{
    return false;
}

void NcWidget::onStartUpApp()
{
    qDebug() << "starting app " << m_title;
}

void NcWidget::refreshContents()
{

}

NcWidget::~NcWidget()
{

}

void NcWidget::closeEvent(QCloseEvent *event)
{

    // TODO: don't use new
    QPropertyAnimation *closeAnime = new QPropertyAnimation(this, "maskWidth");
    closeAnime->setParent(this);          // for auto-delete
    // FIXME: it seems the anime playing is delayed, when the anime is in half,
    // this widget is removed (finished() signal emitted).
    // closeAnime->setDuration(150);
    closeAnime->setDuration(200);
    closeAnime->setStartValue(width());
    closeAnime->setEndValue(0);
    closeAnime->setEasingCurve(QEasingCurve::InSine);
    closeAnime->start(QAbstractAnimation::DeleteWhenStopped);
    // TODO: reduce opacity along with 

    connect(closeAnime, SIGNAL(finished()), this, SIGNAL(closed()));
    closeAnime->start();

    QString s("delete widget");
    // qDebug() << "emit newNotification signal";
    // emit newNotification(s);
    event->ignore();
    // closeAnime->deleteLater();
}

void NcWidget::setWidget(QWidget *widget)
{
    m_widget = widget;
    m_widget->setMinimumHeight(40);
    m_widget->setParent(this);
    qDebug() << "count of mainlayout: " << m_mainLayout->count();
    // m_mainLayout->insertWidget(m_mainLayout->count(), m_widget);
    m_mainLayout->addWidget(m_widget);
    // FIXME: 
    setWindowIcon(m_widget->windowIcon());
    setWindowTitle(m_widget->windowTitle());
}

void NcWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

NcWidget::Style NcWidget::getStyle()
{
    return m_style;
}

void NcWidget::setStyle(Style style)
{
    if (m_style == style)
        return;

    m_style = style;
    if (m_style == Style::Preview)
        setMaximumHeight(100);
    else if (m_style == Style::Extended)
        setMaximumHeight(QWIDGETSIZE_MAX);
#if DEBUG
    // setFixedHeight(400);
    qDebug() << "sizeHint of widget:" << sizeHint();
    qDebug() << "size of widget:" << size();
    qDebug() << "sizeHint of messageWidget:" << m_widget->sizeHint();
    qDebug() << "size of messageWidget:" << m_widget->size();
#endif

}

void NcWidget::toggleStyle()
{
    if (m_style == Style::Preview)
        setStyle(Style::Extended);
    else
        setStyle(Style::Preview);
}

// QHBoxLayout* NcWidget::frameLayout()
// {
//     return m_frameLayout;
// }
//
// QVBoxLayout* NcWidget::mainLayout()
// {
//     return m_mainLayout;
// }

QWidget* NcWidget::frameWidget()
{
    return m_frameWidget;
}

QSize NcWidget::sizeHint() const
{
    // return QSize(100, 200);
    return m_widget->sizeHint();
    // return size();
}

void NcWidget::setWindowIcon(const QIcon& icon)
{
    // m_icon = icon;
    // m_iconButton->setIcon(m_icon);
    // m_iconButton->show();

    // TODO: more detailed distinction between with/without icon
    if (!m_icon.isNull()) {
        m_iconButton->setIcon(m_icon);
    }
    else {
        m_iconButton->hide();
    }
}

void NcWidget::setWindowTitle(const QString& title)
{
    m_title = title;
    m_titleLabel->setText(m_title);
}
