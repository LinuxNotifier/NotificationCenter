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

#endif // NcPluginWidget_H
