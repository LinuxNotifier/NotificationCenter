#include "plugininterface.h"
#include "notificationcenter.h"
#include "ncglobal.h"

PluginInterface::PluginInterface() :
    m_interfaceVersion(__INTERFACE_VERSION__)
{
    
}

QString PluginInterface::interfaceVersion() const
{
    return m_interfaceVersion;
}
