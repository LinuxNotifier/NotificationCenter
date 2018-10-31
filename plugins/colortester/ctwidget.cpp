#include "ctwidget.h"
#include "ui_colortester.h"
#include <QColor>
#include <QPalette>
#include <QDebug>

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
    qDebug() << "!!!!! in ColorTester destructor";
    delete ui;
}

void CtWidget::setTestingWidget(QWidget *widget)
{
    // TODO: highlighten the border of the widget for a period
    m_testingWidget = widget;
    qDebug() << m_testingWidget;
    QColor color = widget->palette().color(QPalette::Background);
    m_bgRgba = widget->palette().color(QPalette::Background).rgba();
    ui->bgRedSlider->setValue(qRed(m_bgRgba));
    ui->bgGreenSlider->setValue(qGreen(m_bgRgba));
    ui->bgBlueSlider->setValue(qBlue(m_bgRgba));
    ui->bgAlphaSlider->setValue(qAlpha(m_bgRgba));

    m_fgRgba = widget->palette().color(QPalette::Foreground).rgba();
    ui->fgRedSlider->setValue(qRed(m_fgRgba));
    ui->fgGreenSlider->setValue(qGreen(m_fgRgba));
    ui->fgBlueSlider->setValue(qBlue(m_fgRgba));
    ui->fgAlphaSlider->setValue(qAlpha(m_fgRgba));
}

void CtWidget::onValueChanged(int value)
{
    QSlider *slider = qobject_cast<QSlider*>(sender());
    if (m_bgMap.contains(slider))
    {
        m_bgMap[slider]->setText(QString::number(value));
    //     if (m_testingWidget) {
    // qDebug() << m_testingWidget;
    //         int red = ui->bgRed->text().toInt();
    //         int green = ui->bgGreen->text().toInt();
    //         int blue = ui->bgBlue->text().toInt();
    //         int alpha = ui->bgAlpha->text().toInt();
    //         m_testingWidget->setStyleSheet(QString("background-color: rgba(%1, %2, %3, %4);").arg(red).arg(green).arg(blue).arg(alpha));
    //         // QColor color(red, green, blue, alpha);
    //         // QPalette palette = m_testingWidget->palette();
    //         // palette.setColor(QPalette::Background, color);
    //         // m_testingWidget->setPalette(palette);
    //     }
    }
    else if (m_fgMap.contains(slider))
    {
        m_fgMap[slider]->setText(QString::number(value));
    //     if (m_testingWidget) {
    // qDebug() << m_testingWidget;
    //         int red = ui->fgRed->text().toInt();
    //         int green = ui->fgGreen->text().toInt();
    //         int blue = ui->fgBlue->text().toInt();
    //         int alpha = ui->fgAlpha->text().toInt();
    //         m_testingWidget->setStyleSheet(QString("color: rgba(%1, %2, %3, %4);").arg(red).arg(green).arg(blue).arg(alpha));
    //         // QColor color(red, green, blue, alpha);
    //         // QPalette palette = m_testingWidget->palette();
    //         // palette.setColor(QPalette::Foreground, color);
    //         // m_testingWidget->setPalette(palette);
    //     }
    }
    int bgRed = ui->bgRed->text().toInt();
    int bgGreen = ui->bgGreen->text().toInt();
    int bgBlue = ui->bgBlue->text().toInt();
    int bgAlpha = ui->bgAlpha->text().toInt();
    // m_testingWidget->setStyleSheet(QString("background-color: rgba(%1, %2, %3, %4);").arg(red).arg(green).arg(blue).arg(alpha));
    int fgRed = ui->fgRed->text().toInt();
    int fgGreen = ui->fgGreen->text().toInt();
    int fgBlue = ui->fgBlue->text().toInt();
    int fgAlpha = ui->fgAlpha->text().toInt();
    m_testingWidget->setStyleSheet(QString("background-color: rgba(%1, %2, %3, %4); color: rgba(%5, %6, %7, %8);").arg(bgRed).arg(bgGreen).arg(bgBlue).arg(bgAlpha).arg(fgRed).arg(fgGreen).arg(fgBlue).arg(fgAlpha));
}

void CtWidget::onReset()
{
    if (m_testingWidget) {
        ui->bgRedSlider->setValue(qRed(m_bgRgba));
        ui->bgGreenSlider->setValue(qGreen(m_bgRgba));
        ui->bgBlueSlider->setValue(qBlue(m_bgRgba));
        ui->bgAlphaSlider->setValue(qAlpha(m_bgRgba));

        ui->fgRedSlider->setValue(qRed(m_fgRgba));
        ui->fgGreenSlider->setValue(qGreen(m_fgRgba));
        ui->fgBlueSlider->setValue(qBlue(m_fgRgba));
        ui->fgAlphaSlider->setValue(qAlpha(m_fgRgba));
    }
}
