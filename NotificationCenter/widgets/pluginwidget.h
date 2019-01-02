#ifndef PluginWidget_H
#define PluginWidget_H

#include "widget.h"
#include <QString>


/*!
 * \brief used for widget plugin.
 */
class PluginWidget : public Widget
{
    Q_OBJECT
    public:

        PluginWidget(QWidget *parent=nullptr);
        ~PluginWidget();


    protected:

    signals:

    public slots:

    private:
};

#endif // PluginWidget_H
