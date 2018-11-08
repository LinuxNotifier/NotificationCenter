#include "ctwidget.h"
#include "ui_colortester.h"
#include <QColor>
#include <QPalette>
#include <QRegExp>

CtWidget::CtWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CtWidget)
{
    ui->setupUi(this);

    connect(ui->bgRedSlider, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
    connect(ui->bgGreenSlider, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
    connect(ui->bgBlueSlider, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
    connect(ui->bgAlphaSlider, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
    m_bgMap[ui->bgRedSlider] = ui->bgRed;
    m_bgMap[ui->bgGreenSlider] = ui->bgGreen;
    m_bgMap[ui->bgBlueSlider] = ui->bgBlue;
    m_bgMap[ui->bgAlphaSlider] = ui->bgAlpha;

    connect(ui->fgRedSlider, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
    connect(ui->fgGreenSlider, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
    connect(ui->fgBlueSlider, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
    connect(ui->fgAlphaSlider, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
    m_fgMap[ui->fgRedSlider] = ui->fgRed;
    m_fgMap[ui->fgGreenSlider] = ui->fgGreen;
    m_fgMap[ui->fgBlueSlider] = ui->fgBlue;
    m_fgMap[ui->fgAlphaSlider] = ui->fgAlpha;

    connect(ui->resetButton, SIGNAL(clicked(bool)), this, SLOT(onReset()));
}

CtWidget::~CtWidget()
{
    delete ui;
}

void CtWidget::setTestingWidget(QWidget *widget)
{
    // TODO: highlighten the border of the widget for a period
    m_testingWidget = widget;
    QString ss = m_testingWidget->styleSheet();
    if (!m_styleSheetMap.contains(m_testingWidget))
        m_styleSheetMap[m_testingWidget] = ss;

    QRegExp bgRegExp("background-color: rgba\\((\\d+), (\\d+), (\\d+), (\\d+)\\);?");
    if (bgRegExp.indexIn(ss) != -1) {
        int bgRed = bgRegExp.cap(1).toInt();
        int bgGreen = bgRegExp.cap(2).toInt();
        int bgBlue = bgRegExp.cap(3).toInt();
        int bgAlpha = bgRegExp.cap(4).toInt();
        ui->bgRedSlider->setValue(bgRed);
        ui->bgGreenSlider->setValue(bgGreen);
        ui->bgBlueSlider->setValue(bgBlue);
        ui->bgAlphaSlider->setValue(bgAlpha);
    }
    QRegExp fgRegExp(" color: rgba\\((\\d+), (\\d+), (\\d+), (\\d+)\\);?");
    if (fgRegExp.indexIn(ss) != -1) {
        int fgRed = fgRegExp.cap(1).toInt();
        int fgGreen = fgRegExp.cap(2).toInt();
        int fgBlue = fgRegExp.cap(3).toInt();
        int fgAlpha = fgRegExp.cap(4).toInt();
        ui->fgRedSlider->setValue(fgRed);
        ui->fgGreenSlider->setValue(fgGreen);
        ui->fgBlueSlider->setValue(fgBlue);
        ui->fgAlphaSlider->setValue(fgAlpha);
    }
}

void CtWidget::onValueChanged(int value)
{
    QSlider *slider = qobject_cast<QSlider*>(sender());
    if (m_bgMap.contains(slider))
        m_bgMap[slider]->setText(QString::number(value));
    else if (m_fgMap.contains(slider))
        m_fgMap[slider]->setText(QString::number(value));

    int bgRed = ui->bgRed->text().toInt();
    int bgGreen = ui->bgGreen->text().toInt();
    int bgBlue = ui->bgBlue->text().toInt();
    int bgAlpha = ui->bgAlpha->text().toInt();
    int fgRed = ui->fgRed->text().toInt();
    int fgGreen = ui->fgGreen->text().toInt();
    int fgBlue = ui->fgBlue->text().toInt();
    int fgAlpha = ui->fgAlpha->text().toInt();
    if (m_testingWidget) {
        QString ss = m_testingWidget->styleSheet();

        QRegExp bgRegExp("background-color: rgba\\((\\d+), (\\d+), (\\d+), (\\d+)\\);?");
        if (bgRegExp.indexIn(ss) != -1)
            ss.replace(bgRegExp, QString("background-color: rgba(%1, %2, %3, %4);").arg(bgRed).arg(bgGreen).arg(bgBlue).arg(bgAlpha));
        else
            ss.append(QString(" background-color: rgba(%1, %2, %3, %4);").arg(bgRed).arg(bgGreen).arg(bgBlue).arg(bgAlpha));


        // FIXME: properly match "color" but not "background-color"
        QRegExp fgRegExp(" color: rgba\\((\\d+), (\\d+), (\\d+), (\\d+)\\);?");
        int index = fgRegExp.indexIn(ss);
        if (index != -1) {
            ss.replace(fgRegExp, QString(" color: rgba(%1, %2, %3, %4);").arg(fgRed).arg(fgGreen).arg(fgBlue).arg(fgAlpha));
            
        }
        else
            ss.append(QString(" color: rgba(%1, %2, %3, %4);").arg(fgRed).arg(fgGreen).arg(fgBlue).arg(fgAlpha));

        m_testingWidget->setStyleSheet(ss);
    }
}

void CtWidget::onReset()
{
    if (m_testingWidget && m_styleSheetMap.contains(m_testingWidget))
        m_testingWidget->setStyleSheet(m_styleSheetMap[m_testingWidget]);
    else {
        ui->fgRedSlider->setValue(0);
        ui->fgGreenSlider->setValue(0);
        ui->fgBlueSlider->setValue(0);
        ui->fgAlphaSlider->setValue(0);

        ui->bgRedSlider->setValue(0);
        ui->bgGreenSlider->setValue(0);
        ui->bgBlueSlider->setValue(0);
        ui->bgAlphaSlider->setValue(0);
    }
}
