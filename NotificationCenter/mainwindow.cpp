#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ncnotificationwidget.h"
#include "datetimewidget.h"
#include "ncpluginwidget.h"
#include "ncmessage.h"
#include "notificationcenter.h"
#include "extensioninterface.h"
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
#include <QPluginLoader>
#include <QScreen>
#include <QGraphicsEffect>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene> 

QPixmap blur_render(QPixmap src, int extent = 5)
{
    if(src.isNull()) return QPixmap();   //No need to do anything else!
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    QGraphicsBlurEffect effect;
    effect.setBlurRadius(extent);
    item.setPixmap(src);
    item.setGraphicsEffect(&effect);
    scene.addItem(&item);
    QPixmap res(src.size()+QSize(extent*2, extent*2));
    res.fill(Qt::transparent);
    QPainter ptr(&res);
    scene.render(&ptr, QRectF(), QRectF( -extent, -extent, src.width()+extent*2, src.height()+extent*2 ) );
    scene.removeItem(&item);
    return res.copy(extent, extent, src.width() + extent, src.height() + extent);
}

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    m_backgroundScene(new QLabel)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | windowFlags());
    // setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground, true);

    setupGeometry();
    m_backgroundScene->setWindowFlags(windowFlags());
    setParent(m_backgroundScene);
    move(0, 0);

    connect(qApp->desktop(), &QDesktopWidget::resized, this, &MainWindow::setupGeometry);
    loadTheme("dark2");
    setupSystemTrayIcon();
    initUi();

    NotificationCenter &nc = NotificationCenter::instance();
    connect(&NotificationCenter::instance(), SIGNAL(newMessage(std::shared_ptr<NcMessage>)), this, SLOT(onNewMessage(std::shared_ptr<NcMessage>)));
    connect(&nc, SIGNAL(messageExpired(const QString)), this, SLOT(onMessageExpired(const QString)));
    connect(&nc, SIGNAL(messageClosed(const QString)), this, SLOT(onMessageClosed(const QString)));
    connect(&nc, SIGNAL(modeChanged(bool)), this, SLOT(onModeChanged(bool)));

    connect(&nc, SIGNAL(newExtension(std::shared_ptr<QPluginLoader>)), this, SLOT(onNewPlugin(std::shared_ptr<QPluginLoader>)));
    connect(&nc, SIGNAL(newExtension(std::shared_ptr<ExtensionInterface>)), this, SLOT(onNewPlugin(std::shared_ptr<ExtensionInterface>)));
    connect(&nc, SIGNAL(extensionDeleted(const QString)), this, SLOT(onPluginDeleted(const QString)));
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)), this, SLOT(onFocusChanged(QWidget *, QWidget *)));


    DateTimeWidget *m_dateTimeWidget = new DateTimeWidget;
    m_dateTimeWidget->setFixedWidth(NOTIFICATIONCENTER_WIDTH - 2 * NOTIFICATIONCENTER_MARGIN);
    m_dateTimeWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_pluginsLayout->addWidget(m_dateTimeWidget, Qt::AlignTop);

    // m_backgroundScene->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupGeometry()
{
    m_backgroundScene->setVisible(false);

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

    m_backgroundScene->setGeometry(m_geometry);
    m_backgroundScene->setFixedWidth(m_geometry.width());
    m_backgroundScene->setFixedHeight(m_geometry.height());
    m_backgroundScene->setVisible(true);
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

void MainWindow::onFocusChanged(QWidget *old, QWidget *now)
{
// #ifndef DEBUG
    if (!now) {                   // losing focus
        hide();
    }
// #endif
}

void MainWindow::onTabChanged(int index)
{
    // TODO: set focus to plugin/notifications layout
}

void MainWindow::show()
{
    // TODO: set focus
    // FIXME: background moving with MainWindow:
    // QWidget : QLabel (background image) : MainWindow
    // when moving QWidget, we also move QLabel in QWidget
    // FIXME: the border gets very bright!!
    QPixmap screen = QApplication::primaryScreen()->grabWindow(0);
    m_backgroundPixmap = blur_render(screen, 60).copy(m_geometry);
    m_backgroundScene->setPixmap(m_backgroundPixmap);
    m_backgroundScene->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QPropertyAnimation *showAnimation = new QPropertyAnimation(m_backgroundScene, "pos", this);
    showAnimation->setDuration(500);
    showAnimation->setStartValue(m_geometry.topRight());
    showAnimation->setEndValue(m_geometry.topLeft());
    showAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    showAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    m_backgroundScene->show();
    QWidget::show();

    ui->tabWidget->setFocus();
}

void MainWindow::hide()
{
    QPropertyAnimation *hideAnimation = new QPropertyAnimation(m_backgroundScene, "pos", this);
    hideAnimation->setDuration(500);
    hideAnimation->setStartValue(m_backgroundScene->pos());
    hideAnimation->setEndValue(m_geometry.topRight());
    hideAnimation->setEasingCurve(QEasingCurve::InSine);
    hideAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    connect(hideAnimation, &QPropertyAnimation::finished, this, [this] () {
            this->m_backgroundScene->hide();
    });
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    // TODO: listen clearEvent, and set maximumHeight decrease peacefully.
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QWidget *widget = qobject_cast<QWidget*>(watched);
        qDebug() << widget << " was clicked";
        if (mouseEvent->buttons() & Qt::LeftButton) {
            NcNotificationWidget * notificationWidget = static_cast<NcNotificationWidget *>(widget->parent());
            if (notificationWidget)
                notificationWidget->toggleStyle();
        }
    }

    return QWidget::eventFilter(watched, event);
}

bool MainWindow::loadTheme(QString name)
{
    if (!name.endsWith(".qss"))
        name.append(".qss");

    qInfo() << tr("loading theme file:") << name;

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
    // FIXME: scroll is very jumpy, maybe listen mouseEvent, and set scrollbar index
    // TODO: change the margin of notification layout, 已經跟那絛橫線連在一起了

    // MainWindow
    setContentsMargins(NOTIFICATIONCENTER_MARGIN, 9, NOTIFICATIONCENTER_MARGIN, 0);
    ui->verticalLayout->setContentsMargins(0, 0, 0, 0);

    m_todayTabLayout = new QVBoxLayout(ui->todayTab);
    ui->todayTab->setLayout(m_todayTabLayout);
    m_todayTabLayout->setAlignment(Qt::AlignTop);
    m_todayTabLayout->setContentsMargins(0, 0, 0, 0);
    m_todayTabLayout->setSpacing(0);

    // Today tab
    QScrollArea *scrollArea = new QScrollArea(ui->todayTab);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_todayTabLayout->addWidget(scrollArea);
    scrollArea->setWidgetResizable(true);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setContentsMargins(0, 0, 0, 0);

    QWidget *pluginWidget = new QWidget(scrollArea);
    scrollArea->setWidget(pluginWidget);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pluginWidget->setContentsMargins(0, 0, 0, 0);
    m_pluginsLayout = new QVBoxLayout(pluginWidget);
    pluginWidget->setLayout(m_pluginsLayout);
    m_pluginsLayout->setAlignment(Qt::AlignTop);
    m_pluginsLayout->setContentsMargins(0, 0, 0, 0);
    m_pluginsLayout->setSpacing(10);
    

    // Notifications tab
    m_notificationsTabLayout = new QVBoxLayout(ui->notificationsTab);
    ui->notificationsTab->setLayout(m_notificationsTabLayout);
    m_notificationsTabLayout->setAlignment(Qt::AlignTop);
    m_notificationsTabLayout->setContentsMargins(0, 0, 0, 0);
    m_notificationsTabLayout->setSpacing(10);
    // m_notificationsTabLayout->addStretch();

    QScrollArea *notificationScrollArea = new QScrollArea(ui->notificationsTab);
    notificationScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // auto *scrollBar = notificationScrollArea->verticalScrollBar();
    // scrollBar->setSingleStep(1);
    m_notificationsTabLayout->addWidget(notificationScrollArea);
    notificationScrollArea->setWidgetResizable(true);
    notificationScrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    notificationScrollArea->setContentsMargins(0, 0, 0, 0);

    QWidget *notificationsWidget = new QWidget(notificationScrollArea);
    notificationScrollArea->setWidget(notificationsWidget);
    notificationsWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    notificationsWidget->setContentsMargins(0, 0, 0, 0);
    m_notificationsLayout = new QVBoxLayout(notificationsWidget);
    notificationsWidget->setLayout(m_notificationsLayout);
    m_notificationsLayout->setAlignment(Qt::AlignTop);
    m_notificationsLayout->setContentsMargins(0, 0, 0, 0);
    m_notificationsLayout->setSpacing(10);
    m_notificationsLayout->addStretch();
}

void MainWindow::onNewMessage(std::shared_ptr<NcMessage> message)
{
    // TODO: beautify the widget UI
    qDebug() << "received a new message:" << message->title();

    NcNotificationWidget *widget = new NcNotificationWidget(this);

    QWidget *messageWidget = new QWidget(widget);
    messageWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    messageWidget->setContentsMargins(0, 0, 0, 0);
    messageWidget->setWindowTitle(message->title() + " -- " + message->createdTime());
    messageWidget->setWindowIcon(message->icon());

    QVBoxLayout *messgeLayout = new QVBoxLayout(messageWidget);
    messageWidget->setLayout(messgeLayout);
    messgeLayout->setContentsMargins(4, 0, 4, 0);
    messgeLayout->setAlignment(Qt::AlignTop);
    messgeLayout->setSpacing(0);

    QLabel *contentLabel = new QLabel(messageWidget);
    messgeLayout->addWidget(contentLabel);
    contentLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    contentLabel->setContentsMargins(0, 0, 0, 0);
    contentLabel->setTextFormat(Qt::RichText);
    contentLabel->setWordWrap(true);

    // contentLabel->setStyleSheet("color: rgb(152, 152, 157)");
    QFont timeFont = contentLabel->font();
    timeFont.setPixelSize(17);
    // timeFont.setWeight(QFont::Light);
    timeFont.setWeight(QFont::Normal);
    contentLabel->setFont(timeFont);



    // Note: use QString::toHtmlEscaped() if you don't want set plain text
    contentLabel->setText(message->content());

    widget->setWidget(messageWidget);
    showNotification(widget);

    /* this won't be overridden since the messageId should be unique,
        and every NcMessage cannot be notified twice */
    m_msgId2Widget[message->messageId()] = widget;
    m_widget2MsgId[widget] = message->messageId();
}

void MainWindow::onNewNotification(NcNotificationWidget *widget)
{
    qDebug() << "received notification" << widget;
    showNotification(widget);
}

void MainWindow::showNotification(NcNotificationWidget *widget)
{
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_notificationsLayout->insertWidget(0, widget);
    widget->setFixedWidth(NOTIFICATIONCENTER_WIDTH - 2 * NOTIFICATIONCENTER_MARGIN);
    widget->setStyle(NcWidget::Style::Preview);

    QWidget *frameWidget = widget->frameWidget();
    frameWidget->installEventFilter(this);
    // TODO: enable widget to expand whatever part of this widget is clicked
    // widget->installEventFilter(this);
    connect(widget, SIGNAL(closed()), this, SLOT(onNotificationClosed()));
}

void MainWindow::onMessageExpired(const QString messageId)
{
    qDebug() << "received a message expired" << messageId;
    onMessageClosed(messageId);
}

void MainWindow::onNotificationClosed()
{
    // FIXME: the widgets are unstable when removing a widget
    // maybe I need to implement without QVBoxLayout
    qDebug() << sender() << "closed";
    NcNotificationWidget *widget = static_cast<NcNotificationWidget *>(sender());
    // this notification widget is created by MainWindow::newMessage(std::shared_ptr<NcNotificationWidget> message)
    if (m_widget2MsgId.contains(widget)) {
        /* this will cause it receiving a messageClosed signal again,
            but it doesn't matter */
        emit messageClosed(m_widget2MsgId[widget]);
        QString messageId = m_widget2MsgId[widget];
        m_msgId2Widget.remove(messageId);
        m_widget2MsgId.remove(widget);
    }

    m_notificationsLayout->removeWidget(widget);
    sender()->deleteLater();
}

void MainWindow::onMessageClosed(const QString messageId)
{
    if (m_msgId2Widget.contains(messageId)) {
        qDebug() << messageId << "closed";
        NcNotificationWidget *widget = m_msgId2Widget[messageId];
        m_notificationsLayout->removeWidget(widget);
        widget->deleteLater();
    }
}

void MainWindow::onModeChanged(bool quiet)
{
    qDebug() << "mode changed:" << quiet;
}

void MainWindow::onNewPlugin(std::shared_ptr<QPluginLoader> pluginLoader)
{
    qDebug() << "got plugin loader" << pluginLoader->fileName();

    ExtensionInterface *interface = qobject_cast<ExtensionInterface*>(pluginLoader->instance());
    if (!interface) {
        qWarning() << pluginLoader->errorString();
        pluginLoader->unload();
        // pluginLoader->deleteLater();
        return;
    }
#if DEBUG
    qDebug() << "get plugin interface: " << interface;
#endif

    bool appliable = interface->initialize(&NotificationCenter::instance());
    if (appliable) {
        QWidget *w = interface->centralWidget();
        // TODO: try cast to NcPluginWidget. if succeeded, don't create NcPluginWidget for it
        if (w) {
            qDebug() << "title: " << w->windowTitle();
            NcPluginWidget *pluginWidget = new NcPluginWidget(this);
            pluginWidget->setWidget(w);
            pluginWidget->setMaximumHeight(300);
            w->setFixedWidth(NOTIFICATIONCENTER_WIDTH - 2 * NOTIFICATIONCENTER_MARGIN);
            m_pluginsLayout->addWidget(pluginWidget);
        }
    }
    else
        qDebug() << "not appliable";
}

void MainWindow::onNewPlugin(std::shared_ptr<ExtensionInterface> plugin)
{
    // qDebug() << "got new plugin" << pluginLoader->fileName();
#if DEBUG
    qDebug() << "get plugin interface: " << plugin.get();
    qDebug() << "plugin metadata: " << plugin->metadata();
#endif
    new std::shared_ptr<ExtensionInterface>(plugin); // keep plugin from freed
    bool appliable = plugin->initialize(&NotificationCenter::instance());
    if (appliable) {
    QWidget *w = plugin->centralWidget();
        if (w) {
            qDebug() << "title: " << w->windowTitle();
            NcPluginWidget *pluginWidget = new NcPluginWidget(this);
            pluginWidget->setWidget(w);
            pluginWidget->setMaximumHeight(300);
            w->setFixedWidth(NOTIFICATIONCENTER_WIDTH - 2 * NOTIFICATIONCENTER_MARGIN);
            m_pluginsLayout->addWidget(pluginWidget);
        }
    }
    else
        qDebug() << "not appliable";
}

void MainWindow::onPluginDeleted(const QString pluginId)
{
    qDebug() << "plugin deleted" << pluginId;
}
