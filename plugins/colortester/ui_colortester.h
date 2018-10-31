/********************************************************************************
** Form generated from reading UI file 'colortester.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORTESTER_H
#define UI_COLORTESTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CtWidget
{
public:
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_11;
    QPushButton *resetButton;
    QVBoxLayout *verticalLayout_6;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *bgRedLabel;
    QLabel *bgGreenLabel;
    QLabel *bgBlueLabel;
    QLabel *bgAlphaLabel;
    QVBoxLayout *verticalLayout;
    QSlider *bgRedSlider;
    QSlider *bgGreenSlider;
    QSlider *bgBlueSlider;
    QSlider *bgAlphaSlider;
    QVBoxLayout *verticalLayout_7;
    QLabel *bgRed;
    QLabel *bgGreen;
    QLabel *bgBlue;
    QLabel *bgAlpha;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *fgRedLabel;
    QLabel *fgGreenLabel;
    QLabel *fgBlueLabel;
    QLabel *fgAlphaLabel;
    QVBoxLayout *verticalLayout_3;
    QSlider *fgRedSlider;
    QSlider *fgGreenSlider;
    QSlider *fgBlueSlider;
    QSlider *fgAlphaSlider;
    QVBoxLayout *verticalLayout_8;
    QLabel *fgRed;
    QLabel *fgGreen;
    QLabel *fgBlue;
    QLabel *fgAlpha;

    void setupUi(QWidget *CtWidget)
    {
        if (CtWidget->objectName().isEmpty())
            CtWidget->setObjectName(QStringLiteral("CtWidget"));
        CtWidget->resize(374, 287);
        verticalLayout_9 = new QVBoxLayout(CtWidget);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_11 = new QLabel(CtWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMaximumSize(QSize(16777215, 40));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_11->setFont(font);
        label_11->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_11);

        resetButton = new QPushButton(CtWidget);
        resetButton->setObjectName(QStringLiteral("resetButton"));
        resetButton->setMinimumSize(QSize(40, 0));
        resetButton->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_3->addWidget(resetButton);


        verticalLayout_9->addLayout(horizontalLayout_3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label = new QLabel(CtWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 30));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        bgRedLabel = new QLabel(CtWidget);
        bgRedLabel->setObjectName(QStringLiteral("bgRedLabel"));

        verticalLayout_2->addWidget(bgRedLabel);

        bgGreenLabel = new QLabel(CtWidget);
        bgGreenLabel->setObjectName(QStringLiteral("bgGreenLabel"));

        verticalLayout_2->addWidget(bgGreenLabel);

        bgBlueLabel = new QLabel(CtWidget);
        bgBlueLabel->setObjectName(QStringLiteral("bgBlueLabel"));

        verticalLayout_2->addWidget(bgBlueLabel);

        bgAlphaLabel = new QLabel(CtWidget);
        bgAlphaLabel->setObjectName(QStringLiteral("bgAlphaLabel"));

        verticalLayout_2->addWidget(bgAlphaLabel);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        bgRedSlider = new QSlider(CtWidget);
        bgRedSlider->setObjectName(QStringLiteral("bgRedSlider"));
        bgRedSlider->setMaximum(255);
        bgRedSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(bgRedSlider);

        bgGreenSlider = new QSlider(CtWidget);
        bgGreenSlider->setObjectName(QStringLiteral("bgGreenSlider"));
        bgGreenSlider->setMaximum(255);
        bgGreenSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(bgGreenSlider);

        bgBlueSlider = new QSlider(CtWidget);
        bgBlueSlider->setObjectName(QStringLiteral("bgBlueSlider"));
        bgBlueSlider->setMaximum(255);
        bgBlueSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(bgBlueSlider);

        bgAlphaSlider = new QSlider(CtWidget);
        bgAlphaSlider->setObjectName(QStringLiteral("bgAlphaSlider"));
        bgAlphaSlider->setMaximum(255);
        bgAlphaSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(bgAlphaSlider);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        bgRed = new QLabel(CtWidget);
        bgRed->setObjectName(QStringLiteral("bgRed"));

        verticalLayout_7->addWidget(bgRed);

        bgGreen = new QLabel(CtWidget);
        bgGreen->setObjectName(QStringLiteral("bgGreen"));

        verticalLayout_7->addWidget(bgGreen);

        bgBlue = new QLabel(CtWidget);
        bgBlue->setObjectName(QStringLiteral("bgBlue"));

        verticalLayout_7->addWidget(bgBlue);

        bgAlpha = new QLabel(CtWidget);
        bgAlpha->setObjectName(QStringLiteral("bgAlpha"));
        bgAlpha->setMinimumSize(QSize(30, 0));

        verticalLayout_7->addWidget(bgAlpha);


        horizontalLayout_2->addLayout(verticalLayout_7);


        verticalLayout_6->addLayout(horizontalLayout_2);


        verticalLayout_9->addLayout(verticalLayout_6);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_10 = new QLabel(CtWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMaximumSize(QSize(16777215, 30));
        label_10->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_10);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        fgRedLabel = new QLabel(CtWidget);
        fgRedLabel->setObjectName(QStringLiteral("fgRedLabel"));

        verticalLayout_4->addWidget(fgRedLabel);

        fgGreenLabel = new QLabel(CtWidget);
        fgGreenLabel->setObjectName(QStringLiteral("fgGreenLabel"));

        verticalLayout_4->addWidget(fgGreenLabel);

        fgBlueLabel = new QLabel(CtWidget);
        fgBlueLabel->setObjectName(QStringLiteral("fgBlueLabel"));

        verticalLayout_4->addWidget(fgBlueLabel);

        fgAlphaLabel = new QLabel(CtWidget);
        fgAlphaLabel->setObjectName(QStringLiteral("fgAlphaLabel"));

        verticalLayout_4->addWidget(fgAlphaLabel);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        fgRedSlider = new QSlider(CtWidget);
        fgRedSlider->setObjectName(QStringLiteral("fgRedSlider"));
        fgRedSlider->setMaximum(255);
        fgRedSlider->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(fgRedSlider);

        fgGreenSlider = new QSlider(CtWidget);
        fgGreenSlider->setObjectName(QStringLiteral("fgGreenSlider"));
        fgGreenSlider->setMaximum(255);
        fgGreenSlider->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(fgGreenSlider);

        fgBlueSlider = new QSlider(CtWidget);
        fgBlueSlider->setObjectName(QStringLiteral("fgBlueSlider"));
        fgBlueSlider->setMaximum(255);
        fgBlueSlider->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(fgBlueSlider);

        fgAlphaSlider = new QSlider(CtWidget);
        fgAlphaSlider->setObjectName(QStringLiteral("fgAlphaSlider"));
        fgAlphaSlider->setMaximum(255);
        fgAlphaSlider->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(fgAlphaSlider);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        fgRed = new QLabel(CtWidget);
        fgRed->setObjectName(QStringLiteral("fgRed"));
        fgRed->setMinimumSize(QSize(30, 0));

        verticalLayout_8->addWidget(fgRed);

        fgGreen = new QLabel(CtWidget);
        fgGreen->setObjectName(QStringLiteral("fgGreen"));

        verticalLayout_8->addWidget(fgGreen);

        fgBlue = new QLabel(CtWidget);
        fgBlue->setObjectName(QStringLiteral("fgBlue"));

        verticalLayout_8->addWidget(fgBlue);

        fgAlpha = new QLabel(CtWidget);
        fgAlpha->setObjectName(QStringLiteral("fgAlpha"));

        verticalLayout_8->addWidget(fgAlpha);


        horizontalLayout->addLayout(verticalLayout_8);


        verticalLayout_5->addLayout(horizontalLayout);


        verticalLayout_9->addLayout(verticalLayout_5);


        retranslateUi(CtWidget);

        QMetaObject::connectSlotsByName(CtWidget);
    } // setupUi

    void retranslateUi(QWidget *CtWidget)
    {
        CtWidget->setWindowTitle(QApplication::translate("CtWidget", "Widget", nullptr));
        label_11->setText(QApplication::translate("CtWidget", "Color Tester", nullptr));
        resetButton->setText(QApplication::translate("CtWidget", "reset", nullptr));
        label->setText(QApplication::translate("CtWidget", "background-color:", nullptr));
        bgRedLabel->setText(QApplication::translate("CtWidget", "red", nullptr));
        bgGreenLabel->setText(QApplication::translate("CtWidget", "green", nullptr));
        bgBlueLabel->setText(QApplication::translate("CtWidget", "blue", nullptr));
        bgAlphaLabel->setText(QApplication::translate("CtWidget", "alpha", nullptr));
        bgRed->setText(QApplication::translate("CtWidget", "0", nullptr));
        bgGreen->setText(QApplication::translate("CtWidget", "0", nullptr));
        bgBlue->setText(QApplication::translate("CtWidget", "0", nullptr));
        bgAlpha->setText(QApplication::translate("CtWidget", "0", nullptr));
        label_10->setText(QApplication::translate("CtWidget", "foreground-color:", nullptr));
        fgRedLabel->setText(QApplication::translate("CtWidget", "red", nullptr));
        fgGreenLabel->setText(QApplication::translate("CtWidget", "green", nullptr));
        fgBlueLabel->setText(QApplication::translate("CtWidget", "blue", nullptr));
        fgAlphaLabel->setText(QApplication::translate("CtWidget", "alpha", nullptr));
        fgRed->setText(QApplication::translate("CtWidget", "0", nullptr));
        fgGreen->setText(QApplication::translate("CtWidget", "0", nullptr));
        fgBlue->setText(QApplication::translate("CtWidget", "0", nullptr));
        fgAlpha->setText(QApplication::translate("CtWidget", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CtWidget: public Ui_CtWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORTESTER_H
