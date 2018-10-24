#ifndef NCLOGGING_H
#define NCLOGGING_H

#include <QDebug>

#undef qDebug
#define qDebug QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).debug().noquote
#undef qInfo
#define qInfo QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).info().noquote
#undef qWarning
#define qWarning QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).warning().noquote
#undef qCritical
#define qCritical QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).critical().noquote
#undef qFatal
#define qFatal QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).fatal().noquote

#endif // NCLOGGING_H
