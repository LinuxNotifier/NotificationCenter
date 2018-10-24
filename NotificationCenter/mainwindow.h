#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QRect>
#include <memory>

using namespace std;

class QFocusEvent;
class QEvent;
class QVBoxLayout;
class QRect;
class QSystemTrayIcon;
class NcMessage;
class QString;

namespace Ui {
class MainWindow;
}

#define NOTIFICATIONCENTER_WIDTH 343

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        bool eventFilter(QObject *watched, QEvent *event) override;

        bool loadTheme(QString name);

    protected:
        void paintEvent(QPaintEvent *event) override;
        void hideEvent(QHideEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;

    signals:
        void messageClosed(const QString& messageId);

    public slots:
        void show();
        void hide();

    private slots:
        void focusChanged(QWidget *old, QWidget *now);
        void onNewMessage(shared_ptr<NcMessage> message);
        void onMessageExpired(const QString& message);
        void onModeChanged(bool quiet);

    private:
        Q_DISABLE_COPY(MainWindow)

        void setupGeometry();
        void setupSystemTrayIcon();
        void initUi();

        Ui::MainWindow *ui;
        QRect m_geometry;
        const int m_notificationCenterWidth = NOTIFICATIONCENTER_WIDTH;
        QSystemTrayIcon *m_systemTrayIcon;

        QVBoxLayout *m_todayTabLayout;
        QVBoxLayout *m_pluginsLayout;
        QVBoxLayout *m_notificationsTabLayout;
        QVBoxLayout *m_notificationsLayout;
};

#endif // MAINWINDOW_H
