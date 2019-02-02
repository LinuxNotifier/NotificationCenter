#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <QFrame>
#include <QPoint>
#include <memory>
#include <QHash>

class QObject;
class QEvent;
class QShowEvent;
class MainWindow;
class Notification;

// const int NotificationBoxInterval 20;

/*
 * Notification bubble
 */
class Notifier : public QFrame
{
    Q_OBJECT
    friend class MainWindow;
    signals:
        void newNotifier();
        void reposition(bool indexChaned = false);
        void notifierDestroyed(const int index);
        void notificationClosed(const QString notificationId);
        // XXX: temporary, remove it when implemented NotificationService
        void notificationExpired(const QString notificationId);

    public slots:
        void onNotificationExpired(const QString notificationId);
        void onReposition(bool indexChaned = false);

        void onExpireClicked();
        void onCloseClicked();

    private slots:
        void onNewNotifier();
        void onNotifierDestroyed(const int index);

    public:
        ~Notifier();

        // NOTE: This method should be called before any instanization.
        static void setCentralWidget(QWidget *widget);
        static void setMasterWidget(QWidget *widget);
        void setNotification(std::shared_ptr<Notification> notification);

    protected:
        void showEvent(QShowEvent *event) override;

    private:
        Notifier(QWidget *parent = nullptr);

        static int count;
        static QWidget *centralWidget;
        static QWidget *masterWidget;
        static QHash<QString, int> notificationIndexMap;

        int m_index;
        std::shared_ptr<Notification> m_notification;
};

#endif // NOTIFIER_H
