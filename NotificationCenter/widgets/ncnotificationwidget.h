#ifndef NCNOTIFICATIONWIDGET_H
#define NCNOTIFICATIONWIDGET_H

// #include "ncpluginwidget.h"
#include "ncnotificationbasewidget.h"
#include <QHash>

class NcMessage;
class QPushButton;

class NcNotificationWidget : public NcNotificationBaseWidget
{
    Q_OBJECT
    public:

        // FIXME: the parent should always be NotificationCenter?
        NcNotificationWidget(QWidget *parent=nullptr);
        ~NcNotificationWidget();

        bool addMessage(NcMessage *msg);
        bool removeMessage(QString& msgUuid);
        void removeNotification();

    private:
        QHash<QString, NcMessage *> m_messageList;
        QPushButton *m_closeButton;

};

#endif // NCNOTIFICATIONWIDGET_H
