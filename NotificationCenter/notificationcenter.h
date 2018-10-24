#ifndef NOTIFICATIONCENTER_H
#define NOTIFICATIONCENTER_H

#include <QObject>
#include <QScopedPointer>

class NcMessage;
class NotificationCenterPrivate;
class MainWindow;
class MessageManager;

class NotificationCenter : public QObject
{
    Q_OBJECT

    public:
        static NotificationCenter& instance(QObject *parent = nullptr);

        void setView(MainWindow *view);
        void setMessageModel(MessageManager *messageModel);
        // void setPluginModel(QObject *pluginModel);

        static NcMessage& createMessage();
        static bool notify(NcMessage& message);

    signals:
        void newMessage(const NcMessage& message);
        void messageExpired(const QString& messageId);
        void messageClosed(const QString& messageId);

    private:
        explicit NotificationCenter(QObject *parent = nullptr);
        ~NotificationCenter();
        Q_DISABLE_COPY(NotificationCenter);
        Q_DECLARE_PRIVATE(NotificationCenter)

        QScopedPointer<NotificationCenterPrivate> d_ptr;
};

#endif // NOTIFICATIONCENTER_H
