#ifndef NCNOTIFICATIONBASEWIDGET_H
#define NCNOTIFICATIONBASEWIDGET_H

#include "ncwidget.h"
#include <QHash>
#include <memory>

using namespace std;

class NcMessage;
class QVBoxLayout;

class NcNotificationBaseWidget : public NcWidget
{
    Q_OBJECT
    public:

        // FIXME: the parent should always be NotificationCenter?
        NcNotificationBaseWidget(QWidget *parent=nullptr);
        // FIXME: use virtual keyword for all base classes
        virtual ~NcNotificationBaseWidget();

        bool addMessage(shared_ptr<NcMessage> message);
        bool removeMessage(QString& msgUuid);
        void removeNotification();


    protected:
        QHash<QString, shared_ptr<NcMessage> > m_messageList;
        QVBoxLayout *m_messageLayout;
        QWidget *m_messageWidget;

};

#endif // NCNOTIFICATIONBASEWIDGET_H
