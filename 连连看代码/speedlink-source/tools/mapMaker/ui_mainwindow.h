/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Jul 13 08:05:47 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>
#include <maparea.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    MapArea *mapLabel;
    QLabel *label_2;
    QLabel *patternNum;
    QLabel *label_3;
    QLabel *pairNum;
    QLabel *label_4;
    QSpinBox *kindNum;
    QLineEdit *fileNameInput;
    QPushButton *generateMap;
    QPushButton *clear;
    QPushButton *fill;
    QLabel *label;
    QLabel *label_5;
    QLabel *label_6;
    QSpinBox *yMax;
    QSpinBox *xMax;
    QLabel *label_7;
    QLabel *numPerPair;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(892, 500);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        mapLabel = new MapArea(centralWidget);
        mapLabel->setObjectName(QString::fromUtf8("mapLabel"));
        mapLabel->setGeometry(QRect(10, 0, 720, 480));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(740, 150, 51, 17));
        patternNum = new QLabel(centralWidget);
        patternNum->setObjectName(QString::fromUtf8("patternNum"));
        patternNum->setGeometry(QRect(810, 150, 62, 17));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(741, 190, 51, 20));
        pairNum = new QLabel(centralWidget);
        pairNum->setObjectName(QString::fromUtf8("pairNum"));
        pairNum->setGeometry(QRect(810, 190, 62, 17));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(740, 320, 62, 17));
        kindNum = new QSpinBox(centralWidget);
        kindNum->setObjectName(QString::fromUtf8("kindNum"));
        kindNum->setGeometry(QRect(820, 320, 54, 23));
        fileNameInput = new QLineEdit(centralWidget);
        fileNameInput->setObjectName(QString::fromUtf8("fileNameInput"));
        fileNameInput->setGeometry(QRect(740, 420, 141, 23));
        generateMap = new QPushButton(centralWidget);
        generateMap->setObjectName(QString::fromUtf8("generateMap"));
        generateMap->setGeometry(QRect(800, 450, 85, 27));
        clear = new QPushButton(centralWidget);
        clear->setObjectName(QString::fromUtf8("clear"));
        clear->setGeometry(QRect(740, 230, 85, 27));
        fill = new QPushButton(centralWidget);
        fill->setObjectName(QString::fromUtf8("fill"));
        fill->setGeometry(QRect(740, 270, 85, 27));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(740, 390, 91, 17));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(740, 50, 62, 17));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(740, 90, 62, 17));
        yMax = new QSpinBox(centralWidget);
        yMax->setObjectName(QString::fromUtf8("yMax"));
        yMax->setGeometry(QRect(810, 40, 55, 27));
        yMax->setValue(10);
        xMax = new QSpinBox(centralWidget);
        xMax->setObjectName(QString::fromUtf8("xMax"));
        xMax->setGeometry(QRect(810, 90, 55, 27));
        xMax->setValue(8);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(740, 350, 62, 17));
        numPerPair = new QLabel(centralWidget);
        numPerPair->setObjectName(QString::fromUtf8("numPerPair"));
        numPerPair->setGeometry(QRect(820, 360, 62, 17));
        MainWindow->setCentralWidget(centralWidget);
#ifndef QT_NO_SHORTCUT
        label_4->setBuddy(kindNum);
        label->setBuddy(fileNameInput);
        label_5->setBuddy(yMax);
        label_6->setBuddy(xMax);
#endif // QT_NO_SHORTCUT

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\345\234\260\345\233\276\347\224\237\346\210\220\345\231\250", 0, QApplication::UnicodeUTF8));
        mapLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "\345\233\276\345\235\227\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        patternNum->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "\345\257\271\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        pairNum->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "\345\233\276\346\241\210\347\247\215\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        generateMap->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        clear->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272", 0, QApplication::UnicodeUTF8));
        fill->setText(QApplication::translate("MainWindow", "\345\241\253\345\205\205", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "\345\234\260\345\233\276\346\226\207\344\273\266\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "\346\250\252\345\220\221\345\235\227\346\225\260", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "\347\272\265\345\220\221\345\235\227\346\225\260", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "\346\257\217\347\247\215\345\257\271\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        numPerPair->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
