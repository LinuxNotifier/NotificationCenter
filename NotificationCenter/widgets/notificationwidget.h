#ifndef NCNOTIFICATIONWIDGET_H
#define NCNOTIFICATIONWIDGET_H

#include "widget.h"

class QPushButton;

class NotificationWidget : public Widget
{
    signals:

    public:
        NotificationWidget(QWidget *parent = nullptr);
        ~NotificationWidget();

    private:
        QPushButton *m_closeButton;
};

#endif // NCNOTIFICATIONWIDGET_H
