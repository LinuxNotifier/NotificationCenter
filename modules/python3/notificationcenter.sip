/* %Module NotificationCenter */
%Module(name=PyNc, call_super_init=True, keyword_arguments="Optional")
/* %DefaultMetatype PyQt5.QtCore.pyqtWrapperType */
%DefaultSupertype sip.simplewrapper

%Import QtCore/QtCoremod.sip
%Import QtGui/QtGuimod.sip
%Import QtWidgets/QtWidgetsmod.sip
%Include ncmessage.sip
%Include extensioninterface.sip

class NcNotificationWidget;
class MainWindow;

class NotificationCenter : public QObject
{
    %TypeHeaderCode
        #include "notificationcenter.h"
        /* #include "ncmessage.h" */
        #include <memory>
    %End

    signals:
        /* void newMessage(shared_ptr<NcMessage> message); */
        /* void newMessage(NcMessage *message); */
        /* %MethodCode */
        /*     Py_BEGIN_ALLOW_THREADS */
        /*     std::shared_ptr<NcMessage> ptr(message); */
        /*     NotificationCenter::newMessage(ptr); */
        /*     Py_END_ALLOW_THREADS */
        /* %End */
        /*  */
        /* void newNotification(NcNotificationWidget *widget); */
        /* void messageExpired(const QString messageId); */
        /* void messageClosed(const QString messageId); */
        /*  */
        /* void modeChanged(bool quiet); */
        /*  */
        /* void newPlugin(shared_ptr<ExtensionInterface> plugin); */
        /* void pluginEnabled(const QString pluginId); */
        /* void pluginDisabled(const QString pluginId); */
        /* void pluginRemoved(const QString pluginId); */
        /* void pluginDeleted(const QString pluginId); */

    public:
        ~NotificationCenter();
        static NotificationCenter& instance(QObject *parent = nullptr);

        static QString version();

        static NcMessage createMessage();
            %MethodCode
                Py_BEGIN_ALLOW_THREADS
            /*     // FIXME: keep reference when the object is alive */
            /*     std::shared_ptr<NcMessage> ptr = *(new std::shared_ptr<NcMessage>(NotificationCenter::createSharedMessage())); */
            /*     sipRes = ptr.get(); */
                    sipRes = new NcMessage;
                Py_END_ALLOW_THREADS
            %End

        /* static bool notify(shared_ptr<NcMessage> message); */

        static bool notify(const NcMessage& message);
        /*     %MethodCode */
        /*         Py_BEGIN_ALLOW_THREADS */
        /*         std::shared_ptr<NcMessage> ptr(a0); */
        /*         NotificationCenter::notify(ptr); */
        /*         Py_END_ALLOW_THREADS */
        /*     %End */

        // NOTE: the following method always returns true
        static bool notify(NcNotificationWidget *widget);

        // FIXME: prevent QObject from garbage collection
        void addPlugin(ExtensionInterface *plugin /Transfer/);

        // static QString themeName();
        static bool quietMode();
        static void setQuietMode(bool quiet = true);
        static void toggleQuietMode();

    private:
        NotificationCenter(const NotificationCenter&);
        NotificationCenter& operator=(const NotificationCenter&);

};
