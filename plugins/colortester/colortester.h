#ifndef ColorTester_PLUGIN_H
#define ColorTester_PLUGIN_H

#include "extensioninterface.h"
#include <QObject>

class QWidget;
class CtWidget;
class NotificationCenter;
class QEvent;

class ColorTester : public QObject, public ExtensionInterface
{
    Q_OBJECT
    Q_INTERFACES(ExtensionInterface)
    Q_PLUGIN_METADATA(IID ExtensionInterface_IID FILE "colortester.json")

    public:
        ColorTester(QObject *parent = nullptr);
        ~ColorTester() override;

        bool eventFilter(QObject *watched, QEvent *event) override;

        bool initialize(NotificationCenter *nc) override;
        QJsonObject metadata() const override;
        QWidget* centralWidget() override;
        QWidget* settingsWidget() override;

    private:
        CtWidget *m_widget = nullptr;
        QTime *m_lastClickTime;
};

#endif // ColorTester_PLUGIN_H
