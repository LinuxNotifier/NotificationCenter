#include "backgroundwidget.h"
#include <QMoveEvent>
#include <QDebug>

void BackGroundWidget::moveEvent(QMoveEvent *event)
{
    emit reposition();
}
