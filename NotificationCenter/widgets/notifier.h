#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <QFrame>
#include <QPoint>
#include <memory>
#include <QHash>

class NotificationEvent;
class NotificationListener;
class QVBoxLayout;
class NotificationWidget;
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

    public slots:
        void onReposition(bool indexChaned = false);

        void onExpireClicked();
        void onCloseClicked();

    private slots:
        void onNewNotifier();
        void onNotifierDestroyed(const int index);

    public:
        virtual ~Notifier();

        // NOTE: This method should be called before any instanization.
        static void initialize();
        static void setCentralWidget(QWidget *widget);
        static void setMasterWidget(QWidget *widget);
        std::shared_ptr<Notification> notification() const;
        virtual void setNotification(std::shared_ptr<Notification> notification);

        int index() const;

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
        QVBoxLayout *m_layout;
};

#endif // NOTIFIER_H
