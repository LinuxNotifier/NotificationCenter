/* %Module NotificationCenter */
%Module(name=Py, call_super_init=True, keyword_arguments="Optional")
/* %DefaultMetatype PyQt5.QtCore.pyqtWrapperType */
%DefaultSupertype sip.simplewrapper

%Import QtCore/QtCoremod.sip
%Import QtGui/QtGuimod.sip
%Import QtWidgets/QtWidgetsmod.sip
%Include notification.sip
%Include extensioninterface.sip

class NotificationWidget;
class MainWindow;

class NotificationCenter : public QObject
{
    %TypeHeaderCode
        #include "notificationcenter.h"
        /* #include "notification.h" */
        #include <memory>
    %End

    signals:
        /* void newNotification(std::shared_ptr<Notification> notification); */
        /* void newNotification(Notification *notification); */
        /* %MethodCode */
        /*     Py_BEGIN_ALLOW_THREADS */
        /*     std::shared_ptr<Notification> ptr(notification); */
        /*     NotificationCenter::newNotification(ptr); */
        /*     Py_END_ALLOW_THREADS */
        /* %End */
        /*  */
        /* void newNotification(NotificationWidget *widget); */
        /* void notificationExpired(const QString notificationId); */
        /* void notificationClosed(const QString notificationId); */
        /*  */
        /* void modeChanged(bool quiet); */
        /*  */
        /* void newExtension(std::shared_ptr<ExtensionInterface> plugin); */
        /* void extensionEnabled(const QString pluginId); */
        /* void extensionDisabled(const QString pluginId); */
        /* void extensionRemoved(const QString pluginId); */
        /* void extensionDeleted(const QString pluginId); */
        // void newExtension(ExtensionInterface *plugin /Transfer/);
        //     %MethodCode
        //         std::shared_ptr<ExtensionInterface> interface(plugin);
        //         // NotificationCenter::newExtension
        //         emit NotificationCenter::instance().newExtension(interface);
        //     %End

    public:
        ~NotificationCenter();
        static NotificationCenter& instance(QObject *parent = nullptr);

        static QString version();

        /* static Notification createNotification(); */
        /*     %MethodCode */
        /*         Py_BEGIN_ALLOW_THREADS */
            /*     // FIXME: keep reference when the object is alive */
            /*     std::shared_ptr<Notification> ptr = *(new std::shared_ptr<Notification>(NotificationCenter::createSharedNotification())); */
            /*     sipRes = ptr.get(); */
            /*         sipRes = new Notification; */
            /*     Py_END_ALLOW_THREADS */
            /* %End */

        static bool notify(const Notification& notification /Transfer/);
        /* static bool notify(Notification *notification /Transfer/); */
        /*     %MethodCode */
        /*         Py_BEGIN_ALLOW_THREADS */
        /*         std::shared_ptr<Notification> ptr(a0); */
        /*         NotificationCenter::notify(ptr); */
        /*         Py_END_ALLOW_THREADS */
        /*     %End */

        // NOTE: the following method always returns true
        static bool display(NotificationWidget *widget);

        // void registerExtension(ExtensionInterface &plugin /Transfer/);
        void registerExtension(ExtensionInterface *plugin /Transfer/);

        // static QString themeName();
        static bool quietMode();
        static void setQuietMode(bool quiet = true);
        static void toggleQuietMode();

    private:
        NotificationCenter(const NotificationCenter&);
        NotificationCenter& operator=(const NotificationCenter&);

};
