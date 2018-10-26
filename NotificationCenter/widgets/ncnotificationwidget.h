#ifndef NCNOTIFICATIONWIDGET_H
#define NCNOTIFICATIONWIDGET_H

#include "ncwidget.h"

class QPushButton;

class NcNotificationWidget : public NcWidget
{
    signals:

    public:
        NcNotificationWidget(QWidget *parent = nullptr);
        ~NcNotificationWidget();

    private:
        QPushButton *m_closeButton;
};

#endif // NCNOTIFICATIONWIDGET_H
