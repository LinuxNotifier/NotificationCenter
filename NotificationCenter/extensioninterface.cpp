#include "extensioninterface.h"

ExtensionInterface::ExtensionInterface()
{
    // TODO: set version metadata info here
}

ExtensionInterface::~ExtensionInterface()
{
#if DEBUG
    qDebug() << "interface destroyed";
#endif
}

QWidget* ExtensionInterface::centralWidget()
{
    return nullptr;
}

QWidget* ExtensionInterface::settingsWidget()
{
    return nullptr;
}
