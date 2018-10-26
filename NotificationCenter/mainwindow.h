#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QRect>
#include <memory>
#include <QHash>

using namespace std;

class PluginInterface;
class NcNotificationWidget;
class QPluginLoader;
class QFocusEvent;
class QEvent;
class QVBoxLayout;
class QRect;
class QSystemTrayIcon;
class NcMessage;
class QString;

typedef QHash<QString, NcNotificationWidget*> MsgId2Widget;
typedef QHash<NcNotificationWidget*, QString> Widget2MsgId;

namespace Ui {
class MainWindow;
}

#define NOTIFICATIONCENTER_WIDTH 343

class MainWindow : public QWidget
{
    Q_OBJECT

    friend class NotificationCenter;

    signals:
        void messageClosed(const QString messageId);

        void pluginEnabled(const QString pluginId);
        void pluginDisabled(const QString pluginId);
        void pluginRemoved(const QString pluginId);

    public slots:
        void show();
        void hide();

    private slots:
        void focusChanged(QWidget *old, QWidget *now);
        void onNewMessage(shared_ptr<NcMessage> message);
        void onMessageClosed(const QString messageId);
        void onMessageExpired(const QString messageId);
        void onNewNotification(NcNotificationWidget *widget);
        void onNotificationClosed();
        void onModeChanged(bool quiet);

        void onNewPlugin(shared_ptr<QPluginLoader> plugin);
        void onPluginDeleted(const QString pluginId);

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        bool eventFilter(QObject *watched, QEvent *event) override;

        bool loadTheme(QString name);

    protected:
        void paintEvent(QPaintEvent *event) override;
        void hideEvent(QHideEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;

    private:
        Q_DISABLE_COPY(MainWindow)

        void showNotification(NcNotificationWidget *widget);

        void setupGeometry();
        void setupSystemTrayIcon();
        void initUi();

        Ui::MainWindow *ui;
        QRect m_geometry;
        const int m_notificationCenterWidth = NOTIFICATIONCENTER_WIDTH;
        QSystemTrayIcon *m_systemTrayIcon;

        QVBoxLayout *m_todayTabLayout;
        QVBoxLayout *m_pluginsLayout;
        QVBoxLayout *m_notificationsTabLayout;
        QVBoxLayout *m_notificationsLayout;

        MsgId2Widget m_msgId2Widget;
        Widget2MsgId m_widget2MsgId;
};

#endif // MAINWINDOW_H
