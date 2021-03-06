#ifndef DATETIMEWDIGET_H
#define DATETIMEWDIGET_H

#include <QLabel>
#include <QDateTime>
#include <QWidget>
#include <QPaintEvent>

class QTimer;
class QLabel;
class QVBoxLayout;

class DateTimeWidget : public QWidget
{
    Q_OBJECT
    public:
        DateTimeWidget(QWidget *parent=nullptr);
        ~DateTimeWidget();

    protected:

    private slots:
        void updateDateTime();
        void startTimer();

    private:
        QDateTime m_dateTime;
        QTimer *m_timer;
        QLabel *m_dateLabel;
        QLabel *m_timeLabel;
        QVBoxLayout *m_layout;
};

#endif // DATETIMELABEL_H
