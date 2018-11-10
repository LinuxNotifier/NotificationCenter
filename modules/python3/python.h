#ifndef PYTHON_H
#define PYTHON_H

#include "extensioninterface.h"
#include <QObject>

class NotificationCenter;

class Python : public QObject, public ExtensionInterface
{
    Q_OBJECT
    Q_INTERFACES(ExtensionInterface)
    Q_PLUGIN_METADATA(IID ExtensionInterface_IID FILE "python.json")

    public:
        Python(QObject *parent = nullptr);
        ~Python() override;

        bool initialize(NotificationCenter *nc) override;
        QJsonObject metadata() const override;

    private:
        void loadPythonPlugins();
};

#endif // PYTHON_H
