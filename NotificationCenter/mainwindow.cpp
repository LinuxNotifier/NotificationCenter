#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ncmessage.h"
#include "notificationcenter.h"
#include "ncdebug.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QPainter>
#include <QStyleOption>
#include <QPaintEvent>
#include <QScrollArea>
#include <QVector>
#include <QPropertyAnimation>
#include <QDesktopWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QDir>
#include <QScrollBar>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | windowFlags());
    // setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground, true);

    setupGeometry();
    connect(qApp->desktop(), &QDesktopWidget::resized, this, &MainWindow::setupGeometry);
    loadTheme("dark");
    setupSystemTrayIcon();
    initUi();

    NotificationCenter &nc = NotificationCenter::instance();
    connect(&NotificationCenter::instance(), SIGNAL(newMessage(shared_ptr<NcMessage>)), this, SLOT(onNewMessage(shared_ptr<NcMessage>)));
    connect(&nc, SIGNAL(messageExpired(const QString&)), this, SLOT(onMessageExpired(const QString&)));
    connect(&nc, SIGNAL(messageExpired(const QString&)), this, SLOT(onMessageExpired(const QString&)));
    connect(&nc, SIGNAL(modeChanged(bool)), this, SLOT(onModeChanged(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupGeometry()
{
    int menuBarHeight = 0;
    int width = m_notificationCenterWidth;;
    const QRect &screenGeometry = QApplication::desktop()->screenGeometry();
    QRegion screenReion = QRegion(screenGeometry);
    QRegion availableReion = QRegion(QApplication::desktop()->availableGeometry());
    QVector<QRect> menuBarRects = screenReion.subtracted(availableReion).rects();
#ifdef DEBUG
    qDebug() << "screen Geometry:" << screenReion;
    qDebug() << "available Geometry:" << availableReion;
    qDebug() << "menu bar geometry:" << menuBarRects;
#endif
    // find out the right (hopefully) menu bar height
    for (auto it : menuBarRects) {
        if (it.contains(screenGeometry.topRight())) {
            menuBarHeight = it.height();
            break;
        }
    }

    int height = screenGeometry.height() - menuBarHeight;

    move(screenGeometry.width() - width, menuBarHeight);
    setFixedWidth(width);
    setFixedHeight(height);
    m_geometry.setRect(screenGeometry.width() - width, menuBarHeight, width, height);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void MainWindow::hideEvent(QHideEvent *event)
{
    QWidget::hideEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    int modifiers = event->modifiers();

    if (modifiers & Qt::CTRL) {
        if (key == Qt::Key_PageUp)
            ui->tabWidget->setCurrentIndex(0);
        else if(key == Qt::Key_PageDown)
            ui->tabWidget->setCurrentIndex(1);
    }
}

void MainWindow::focusChanged(QWidget *old, QWidget *now)
{
    if (!now)                   // losing focus
        hide();
}

void MainWindow::show()
{
    QPropertyAnimation *showAnimation = new QPropertyAnimation(this, "pos", this);
    showAnimation->setDuration(200);
    showAnimation->setStartValue(m_geometry.topRight());
    showAnimation->setEndValue(m_geometry.topLeft());
    showAnimation->setEasingCurve(QEasingCurve::InSine);
    showAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    QWidget::show();
}

void MainWindow::hide()
{
    QPropertyAnimation *hideAnimation = new QPropertyAnimation(this, "pos", this);
    hideAnimation->setDuration(200);
    hideAnimation->setStartValue(pos());
    hideAnimation->setEndValue(m_geometry.topRight());
    hideAnimation->setEasingCurve(QEasingCurve::InSine);
    hideAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    connect(hideAnimation, &QPropertyAnimation::finished, this, [this] () {
            QWidget::hide();
    });
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched, event);
}

bool MainWindow::loadTheme(QString name)
{
    if (!name.endsWith(".qss"))
        name.append(".qss");

    qInfo() << tr("loading qss file:") << name;

    QDir themesDir(qApp->applicationDirPath());
    themesDir.cd("themes");
    if (!themesDir.exists())
        themesDir.mkdir(".");
    QFile file(themesDir.filePath(name));
    if (!file.exists()) {
        qWarning() << tr("%1 not found").arg(name);
        return false;
    }
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        setStyleSheet(file.readAll());
        return true;
    }
    else {
        qWarning() << tr("loading %1 failed").arg(name);
        return false;
    }
}

void MainWindow::setupSystemTrayIcon()
{
    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        m_systemTrayIcon = new QSystemTrayIcon(this);
        QIcon *systemTrayIcon = new QIcon(":/images/notificationcenter_icon.png");
        if (systemTrayIcon->isNull()) {
            qWarning() << tr("loading system-tray icon failed");
            return;
        }
        m_systemTrayIcon->setIcon(*systemTrayIcon);
        QMenu *menu = new QMenu;
        m_systemTrayIcon->setContextMenu(menu);

        // FIXME: this does not work in Ubuntu 16.04
        connect(m_systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(show()));
        connect(menu, SIGNAL(aboutToShow()), this, SLOT(show()));
        connect(menu, SIGNAL(aboutToHide()), this, SLOT(hide()));

        m_systemTrayIcon->show();
    }
    else
        qInfo() << tr("no system tray");
}

void MainWindow::initUi()
{
    m_todayTabLayout = new QVBoxLayout(ui->todayTab);
    ui->todayTab->setLayout(m_todayTabLayout);
    m_todayTabLayout->setContentsMargins(0, 0, 0, 0);

    // FIXME: scroll is very jumpy
    QScrollArea *scrollArea = new QScrollArea;
    m_todayTabLayout->addWidget(scrollArea);
    scrollArea->setWidgetResizable(true);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QWidget *pluginWidget = new QWidget(scrollArea);
    scrollArea->setWidget(pluginWidget);
    m_pluginsLayout = new QVBoxLayout(pluginWidget);
    pluginWidget->setLayout(m_pluginsLayout);
    m_pluginsLayout->setAlignment(Qt::AlignTop);
    m_pluginsLayout->setContentsMargins(0, 0, 0, 0);
    m_pluginsLayout->setSpacing(10);
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)), this, SLOT(focusChanged(QWidget *, QWidget *)));
}

void MainWindow::onNewMessage(shared_ptr<NcMessage> message)
{
    // TODO
    qDebug() << "received a new message:" << message->title();
}

void MainWindow::onMessageExpired(const QString& messageId)
{
    // TODO
    qDebug() << "received a message expired" << messageId;
}

void MainWindow::onModeChanged(bool quiet)
{
    qDebug() << "mode changed:" << quiet;
}
