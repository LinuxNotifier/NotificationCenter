#include "datetimewidget.h"
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>
#include <QFontMetrics>
#include <QDebug>
#include <QPainter>

DateTimeWidget::DateTimeWidget(QWidget *parent) :
    QFrame(parent),
    m_dateTime(QDateTime::currentDateTime()),
    m_timer(new QTimer),
    m_dateLabel(new QLabel(this)),
    m_timeLabel(new QLabel(this))
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    m_dateLabel->setText(m_dateTime.date().toString(Qt::SystemLocaleLongDate));
    m_timeLabel->setText(m_dateTime.time().toString("HH:mm:ss"));

    QFont timeFont = m_timeLabel->font();
    timeFont.setPixelSize(46);
    timeFont.setWeight(QFont::Light);
    m_timeLabel->setFont(timeFont);

    m_dateLabel->setWordWrap(true);

    m_layout = new QVBoxLayout(this);
    m_layout->setSpacing(0);
    m_layout->setMargin(0);
    m_layout->addStretch();
    m_layout->addWidget(m_timeLabel);
    m_layout->addWidget(m_dateLabel);
    m_layout->addStretch();

    // this->resize(200, 700);
    QString _c("QFrame { \
        background-color: transparent; \
    }");
    setStyleSheet(_c);
   // setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateDateTime()));

    // fix msec difference with extra 75 msec waitting for time to change
    int remainingMsec = 1075 - (m_dateTime.currentMSecsSinceEpoch() % 1000);
    QTimer::singleShot(remainingMsec, this, &DateTimeWidget::startTimer);
}

DateTimeWidget::~DateTimeWidget()
{
    delete m_timer;
    delete m_layout;
    delete m_timeLabel;
    delete m_dateLabel;
}

void DateTimeWidget::updateDateTime()
{
    m_dateTime = QDateTime::currentDateTime();
    m_dateLabel->setText(m_dateTime.date().toString(Qt::SystemLocaleLongDate));
    m_timeLabel->setText(m_dateTime.time().toString("HH:mm:ss"));
}

void DateTimeWidget::startTimer()
{
    // TODO: maybe stop it when not visiable
    m_timer->start(1000);
    // m_timer->start(200);
}
