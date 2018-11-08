#include "colortester.h"
#include "ctwidget.h"
#include "notificationcenter.h"
#include "ncpluginwidget.h"
#include "ncglobal.h"
#include "ncdebug.h"
#include <QWidget>
#include <QIcon>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QTime>

ColorTester::ColorTester(QObject *parent) :
    QObject(parent)
{
    
}

ColorTester::~ColorTester()
{
    if (m_lastClickTime)
        delete m_lastClickTime;
    
}

QJsonObject ColorTester::metadata() const
{
    QJsonObject json;
    return json;
}


void ColorTester::initialize(NotificationCenter *nc)
{
    m_lastClickTime = new QTime;
    m_lastClickTime->start();
    qApp->installEventFilter(this);
    
}

QWidget* ColorTester::centralWidget()
{
    m_widget = new CtWidget;
    m_widget->setWindowTitle("Color Tester");
    m_widget->setWindowIcon(QIcon::fromTheme("edit-undo"));
    return m_widget;
}

QWidget* ColorTester::settingsWidget()
{
    return new QWidget;
}

QString ColorTester::interfaceVersion() const
{
    return __INTERFACE_VERSION__;
}

bool ColorTester::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QWidget *widget = qobject_cast<QWidget*>(watched);
        if (widget && mouseEvent->buttons() & Qt::RightButton) {
            if (m_lastClickTime->restart() < 500) {
                return QObject::eventFilter(watched, event);
            }
            if (m_widget)
                m_widget->setTestingWidget(widget);
        }
    }

    return QObject::eventFilter(watched, event);
}
