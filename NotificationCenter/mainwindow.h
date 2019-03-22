#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "notificationevent.h"
#include "notificationservice.h"
#include <QWidget>
#include <QRect>
#include <memory>
#include <QHash>
#include <QPixmap>

class ExtensionInterface;
class Notifier;
class NotificationWidget;
class NotificationListener;
class QPluginLoader;
class QFocusEvent;
class QEvent;
class QVBoxLayout;
class QRect;
class QSystemTrayIcon;
class Notification;
class QString;
class QLabel;
class QMoveEvent;
class SceneWidget;
class BackGroundWidget;

typedef QHash<QString, NotificationWidget*> MsgId2Widget;
typedef QHash<NotificationWidget*, QString> Widget2MsgId;

namespace Ui {
class MainWindow;
}

#define NOTIFICATIONCENTER_WIDTH 343
#define NOTIFICATIONCENTER_MARGIN 6

class MainWindow : public QWidget
{
    Q_OBJECT

    friend class NotificationCenter;

    signals:
        void notificationClosed(const QString notificationId);

        void extensionEnabled(const QString pluginId);
        void extensionDisabled(const QString pluginId);
        void extensionRemoved(const QString pluginId);
        /**
         * this signal is emitted when MainWindow is reshown.
         * extensions should connect to this signal to update contents.
         */
        void refreshContents();
        void reposition(bool indexChaned);
        void notifierDestroyed(const int index);

    public slots:
        void show();
        void hide();

    private slots:
        void onFocusChanged(QWidget *old, QWidget *now);
        void onTabChanged(int index);
        void onNewNotification(std::shared_ptr<Notification> notification);
        void onNotificationClosed(const QString notificationId);
        void onNotificationExpired(const QString notificationId);
        // this slot is called actually not when notification widget
        // is closed, but the user clicked the close button. It give
        // us time to deal with the close animation.
        void onNotificationClosed();
        void onNotificationEvent(NotificationEvent *event);
        void onModeChanged(bool quiet);

        void onNewPlugin(std::shared_ptr<QPluginLoader> pluginLoader);
        void onNewPlugin(std::shared_ptr<ExtensionInterface> plugin);
        void onPluginDeleted(const QString pluginId);

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        bool eventFilter(QObject *watched, QEvent *event) override;

        void displayNotification(NotificationWidget *widget);
        bool loadTheme(QString name);

    protected:
        void paintEvent(QPaintEvent *event) override;
        void hideEvent(QHideEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;

    private:
        Q_DISABLE_COPY(MainWindow)

        NC_APP("org.linuxnotifier.Notifier")
        void showNotification(NotificationWidget *widget);
        void showNotifier(Notifier *notifier);

        void setupGeometry();
        void setupSystemTrayIcon();
        void initUi();

        Ui::MainWindow *ui = nullptr;
        QRect m_geometry;
        const int m_notificationCenterWidth = NOTIFICATIONCENTER_WIDTH;
        QSystemTrayIcon *m_systemTrayIcon = nullptr;

        QVBoxLayout *m_todayTabLayout = nullptr;
        QVBoxLayout *m_pluginsLayout = nullptr;
        QVBoxLayout *m_notificationsTabLayout = nullptr;
        QVBoxLayout *m_notificationsLayout = nullptr;

        QPixmap m_backgroundPixmap;
        BackGroundWidget *m_backgroundScene = nullptr;

        MsgId2Widget m_msgId2Widget;
        Widget2MsgId m_widget2MsgId;
        QHash<QString, std::shared_ptr<Notification> > m_notificationMap;
        QHash<QString, Notifier *> m_notifierMap;

        NotificationListener *m_notificationListener = nullptr;
};

#endif // MAINWINDOW_H
