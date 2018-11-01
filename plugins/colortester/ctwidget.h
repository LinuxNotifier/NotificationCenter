#ifndef CTWIDGET_H
#define CTWIDGET_H

#include <QWidget>
#include <QHash>
#include <QColor>
#include <QPalette>

namespace Ui {
class CtWidget;
}

class QSlider;
class QLabel;


typedef QHash<QSlider*, QLabel*> SliderLabelMap;
typedef QHash<QWidget*, QString> StyleSheetMap;

class CtWidget : public QWidget
{
    Q_OBJECT

    private slots:
        void onValueChanged(int value);
        void onReset();

    public:
        explicit CtWidget(QWidget *parent = nullptr);
        ~CtWidget();

        void setTestingWidget(QWidget *widget);

    private:
        Ui::CtWidget *ui;
        QWidget *m_testingWidget = nullptr;

        SliderLabelMap m_fgMap;
        SliderLabelMap m_bgMap;
        QRgb m_fgRgba;
        QRgb m_bgRgba;
        StyleSheetMap m_styleSheetMap;
};

#endif // CTWIDGET_H
