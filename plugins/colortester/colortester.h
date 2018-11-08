#ifndef ColorTester_PLUGIN_H
#define ColorTester_PLUGIN_H

#include "plugininterface.h"
#include <QObject>

class QWidget;
class CtWidget;
class NotificationCenter;
class QEvent;

class ColorTester : public QObject, public PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
    Q_PLUGIN_METADATA(IID PluginInterface_IID FILE "colortester.json")

    public:
        ColorTester(QObject *parent = nullptr);
        ~ColorTester();

        bool eventFilter(QObject *watched, QEvent *event) override;

        QJsonObject metadata() const override;
        void initialize(NotificationCenter *nc) override;
        QWidget* centralWidget() override;
        QWidget* settingsWidget() override;
        QString interfaceVersion() const override;

    private:
        CtWidget *m_widget = nullptr;
        QTime *m_lastClickTime;
};

#endif // ColorTester_PLUGIN_H
