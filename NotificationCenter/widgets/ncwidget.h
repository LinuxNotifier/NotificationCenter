#ifndef NBASEWIDGET_H
#define NBASEWIDGET_H

#include <QWidget>
#include <QString>
#include <QIcon>

class QPaintEvent;
class QVBoxLayout;
class QHBoxLayout;
class QCloseEvent;
class QPushButton;
class QLabel;

/**
 * Base class for Notification widget, like desktop popup, notification widget, plugin widget.
 * @param parent parent of this widget
 * @param name name of the widget, this will be used as the title of the widget
 * @param icon used as the icon the of widget
 */
class NcWidget : public QWidget
{
    Q_OBJECT

    public:
        enum class Style {
            Preview,
            Normal,
            Extended,
        };
        Q_ENUM(Style)

        explicit NcWidget(QWidget *parent=nullptr);
        virtual ~NcWidget();

        inline bool isCallable();
        void setCallable(bool callable=true);
        void setWidget(QWidget *widget);
        bool eventFilter(QObject *watched, QEvent *event) override;

        QWidget *frameWidget();

        Style getStyle();
        void setStyle(Style style);
        void toggleStyle();

        void setWindowIcon(const QIcon& icon);
        void setWindowTitle(const QString& title);
        // // FIXME: figure out will the icon since it's reference
        // void setIcon(const QIcon& icon);
        // void setTitle(const QString& title);

    protected:
        void closeEvent(QCloseEvent *event) override;
        void paintEvent(QPaintEvent *event) override;

        // inline QHBoxLayout* frameLayout();     // used for custom title bar
        // inline QVBoxLayout* mainLayout();

        QHBoxLayout *m_frameLayout;
        QVBoxLayout *m_mainLayout;

    signals:
        void startUpApp();
        void closed();

    public slots:
        virtual void onStartUpApp();
        virtual void refreshContents();          // used when the NC contents needs udpated

    private:

        QString m_title;
        QIcon m_icon;
        bool m_callable = false;
        QWidget *m_widget;
        QWidget *m_frameWidget;
        QPushButton *m_iconButton;
        QPushButton *m_moveButton;
        QLabel *m_titleLabel;
        Style m_style = Style::Preview;
};

#endif // NBASEWIDGET_H
