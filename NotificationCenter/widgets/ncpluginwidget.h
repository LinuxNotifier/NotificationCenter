#ifndef NcPluginWidget_H
#define NcPluginWidget_H

#include "ncwidget.h"
#include <QString>


/*!
 * \brief used for widget plugin.
 */
class NcPluginWidget : public NcWidget
{
    Q_OBJECT
public:

    NcPluginWidget(QWidget *parent=nullptr);
    ~NcPluginWidget();


protected:

signals:

public slots:

private:
};

// weird, if we move this class def to widgets.h (it was located in ncpluginwidget.h originally),
// it works perfectly!!
// I think I've found the reason, because 'ncpluginwidget.h' is not in the plugin folder!
// And the dde-control does not suffer this bug is because it doesn't use basewidget defined in main program.
// Got it!! we need to add ncbasewidget.h nbasewidget.cpp to notify.pro
// class NcWidget : public QPushButton
// {
//     // using Q_OBJECT macro will cause cannot load plugin
//     Q_OBJECT
//     public:
//         NcWidget(QString parent) : QPushButton(parent) {}
// };

#endif // NcPluginWidget_H
