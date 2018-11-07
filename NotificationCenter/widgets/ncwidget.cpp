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
#include <QSequentialAnimationGroup>

NcWidget::NcWidget(QWidget *parent) :
    QWidget(parent),
    m_widget(nullptr),
    m_frameWidget(new QWidget(this)),
    m_iconButton(new QPushButton(this)),
    m_titleButton(new QPushButton(this)),
    m_mainLayout(new QVBoxLayout),
    m_frameLayout(new QHBoxLayout)

{
    connect(this, SIGNAL(startUpApp()), this, SLOT(onStartUpApp()));

    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    m_iconButton->resize(ICON_SIZE, ICON_SIZE);
    m_iconButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // m_iconButton->setAlignment(Qt::AlignVCenter);

    m_titleButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_frameLayout->setAlignment(Qt::AlignVCenter);


    // keep layout of title label when icon button is invisible
    // FIXME: don't know whether it does work yet.
    QSizePolicy sp_retain = sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    setSizePolicy(sp_retain);
    // setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_mainLayout->setAlignment(Qt::AlignTop);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(10);

    setContentsMargins(0, 0, 0, 0);
    setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->addWidget(m_frameWidget);
    m_frameLayout->setContentsMargins(0, 0, 0, 0);
    m_frameLayout->addWidget(m_iconButton, Qt::AlignLeft);
    m_frameLayout->addWidget(m_titleButton, Qt::AlignLeft | Qt::AlignVCenter);
    m_frameLayout->addStretch();
    m_frameWidget->setLayout(m_frameLayout);
    m_frameWidget->setObjectName("frameWidget");
    m_frameWidget->setFixedHeight(20);
    // m_frameWidget->setFixedHeight(24);

    // test code
    setCallable(true);
}

NcWidget::~NcWidget()
{

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
        // TODO: set label clickable (maybe use QPushButton instead of QLabel)
        connect(m_iconButton, SIGNAL(clicked(bool)), this, SLOT(onStartUpApp()));
        connect(m_titleButton, SIGNAL(clicked(bool)), this, SLOT(onStartUpApp()));
    }
    else {
        disconnect(m_iconButton, SIGNAL(clicked(bool)), this, SLOT(onStartUpApp()));
        disconnect(m_titleButton, SIGNAL(clicked(bool)), this, SLOT(onStartUpApp()));
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

void NcWidget::closeEvent(QCloseEvent *event)
{
    // setStyleSheet("background: transparent; color: transparent;");
    // setAttribute(Qt::WA_TranslucentBackground);
    // setVisible(false);
    // event->ignore();
    // return;

    QSequentialAnimationGroup *animationGroup = new QSequentialAnimationGroup(this);

    QPropertyAnimation *closeAnime = new QPropertyAnimation(this, "maskWidth");
    closeAnime->setParent(this);          // for auto-delete
    // FIXME: it seems the anime playing is delayed, when the anime is in half,
    // this widget is removed (finished() signal emitted).
    closeAnime->setDuration(200);
    closeAnime->setStartValue(width());
    closeAnime->setEndValue(0);
    closeAnime->setEasingCurve(QEasingCurve::InOutQuad);
    connect(closeAnime, SIGNAL(finished()), this, SLOT(onCloseAnimationFinished()));

    QPropertyAnimation *removeAnimation = new QPropertyAnimation(this, "maximumHeight");
    removeAnimation->setParent(this);
    removeAnimation->setDuration(500);
    removeAnimation->setStartValue(height());
    removeAnimation->setEndValue(0);
    removeAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    animationGroup->addAnimation(closeAnime);
    animationGroup->addAnimation(removeAnimation);

    connect(animationGroup, SIGNAL(finished()), this, SIGNAL(closed()));
    animationGroup->start(QAbstractAnimation::DeleteWhenStopped);

    event->ignore();        // don't close widget
    setWindowOpacity(0);
}

void NcWidget::onCloseAnimationFinished()
{
    // sender()->
    NcWidget *widget = static_cast<NcWidget *>(sender());
    qDebug()  << "widget" << widget << "closed";
    widget->setVisible(false);
    // widget->hide();
}

void NcWidget::setWidget(QWidget *widget)
{
    m_widget = widget;
    m_widget->setParent(this);
    m_mainLayout->addWidget(m_widget);
    if (!m_widget->windowIcon().isNull())
        setWindowIcon(m_widget->windowIcon());
    if (!m_widget->windowTitle().isNull())
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
    m_style = style;
    if (m_style == Style::Preview)
        setMaximumHeight(100);
    else if (m_style == Style::Extended)
        setMaximumHeight(QWIDGETSIZE_MAX);
}

void NcWidget::toggleStyle()
{
    // TODO: use QTimer to increase maximumHeight to keep speed
    QPropertyAnimation *scaleAnimation = new QPropertyAnimation(this, "maximumHeight");
    scaleAnimation->setParent(this);
    scaleAnimation->setDuration(500);
    if (m_style == Style::Preview) {
        scaleAnimation->setStartValue(100);
        // FIXME: some widget would have height greater than 400
        scaleAnimation->setEndValue(400);
        m_style = Style::Extended;
    }
    else {
        scaleAnimation->setStartValue(height());
        scaleAnimation->setEndValue(100);
        m_style = Style::Preview;
    }
    scaleAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    scaleAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

QWidget* NcWidget::frameWidget()
{
    return m_frameWidget;
}

void NcWidget::setWindowIcon(const QIcon& icon)
{

    // TODO: more detailed distinction between with/without icon
    m_icon = icon;
    if (!m_icon.isNull()) {
        m_iconButton->setIcon(m_icon);
    }
    else {
        m_iconButton->hide();
    }
}

void NcWidget::setWindowTitle(const QString& title)
{
    // TODO: bold font
    m_title = title;
    m_titleButton->setText(m_title);
}
