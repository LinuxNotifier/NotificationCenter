#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

class PluginInfo;
class PluginManager;
class QWidget;

class PluginInterface
{
    // public:
    //     virtual void initialize(PluginManager *pluginManager) = 0;
    //     virtual QWidget *centralWidget() = 0;
    //     virtual PluginInfo &pluginInfo() = 0;
    //
    // protected:
    //     PluginManager *m_pluginManager = nullptr;
};

// QT_BEGIN_NAMESPACE
// #define PluginInterface_iid "org.linuxnotifier.NotificationCenter"
//
// Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)
// QT_END_NAMESPACE


#endif // PLUGININTERFACE_H
