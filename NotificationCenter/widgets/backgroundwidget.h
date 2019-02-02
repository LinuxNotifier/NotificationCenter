#ifndef BACKGROUNDWIDGET_H
#define BACKGROUNDWIDGET_H

#include <QLabel>

class QMoveEvent;

class BackGroundWidget : public QLabel
{
    Q_OBJECT
    signals:
        void reposition(bool indexChaned = false);
        void notifierDestroyed(const int index);

    protected:
        void moveEvent(QMoveEvent *event) override;
};

#endif // BACKGROUNDWIDGET_H
