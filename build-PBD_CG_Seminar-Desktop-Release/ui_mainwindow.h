/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "canvas.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open_Model;
    QAction *action_Exit;
    QAction *actionCube;
    QAction *actionCylinder;
    QAction *actionSphere;
    QAction *actionTorus;
    QAction *actionSoft_Mode;
    QAction *actionScene_1;
    QAction *actionScene_2;
    QAction *actionScene_3;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    Canvas *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelSolver;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelIterations;
    QSpinBox *spinBox;
    QPushButton *resetButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuChoose_Primitive;
    QMenu *menuChoose_Scene_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        action_Open_Model = new QAction(MainWindow);
        action_Open_Model->setObjectName(QStringLiteral("action_Open_Model"));
        action_Exit = new QAction(MainWindow);
        action_Exit->setObjectName(QStringLiteral("action_Exit"));
        actionCube = new QAction(MainWindow);
        actionCube->setObjectName(QStringLiteral("actionCube"));
        actionCylinder = new QAction(MainWindow);
        actionCylinder->setObjectName(QStringLiteral("actionCylinder"));
        actionSphere = new QAction(MainWindow);
        actionSphere->setObjectName(QStringLiteral("actionSphere"));
        actionTorus = new QAction(MainWindow);
        actionTorus->setObjectName(QStringLiteral("actionTorus"));
        actionSoft_Mode = new QAction(MainWindow);
        actionSoft_Mode->setObjectName(QStringLiteral("actionSoft_Mode"));
        actionScene_1 = new QAction(MainWindow);
        actionScene_1->setObjectName(QStringLiteral("actionScene_1"));
        actionScene_2 = new QAction(MainWindow);
        actionScene_2->setObjectName(QStringLiteral("actionScene_2"));
        actionScene_3 = new QAction(MainWindow);
        actionScene_3->setObjectName(QStringLiteral("actionScene_3"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        widget = new Canvas(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_4->addWidget(label);

        doubleSpinBox = new QDoubleSpinBox(centralWidget);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));

        horizontalLayout_4->addWidget(doubleSpinBox);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelSolver = new QLabel(centralWidget);
        labelSolver->setObjectName(QStringLiteral("labelSolver"));

        horizontalLayout_3->addWidget(labelSolver);

        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_3->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelIterations = new QLabel(centralWidget);
        labelIterations->setObjectName(QStringLiteral("labelIterations"));

        horizontalLayout_2->addWidget(labelIterations);

        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        horizontalLayout_2->addWidget(spinBox);


        verticalLayout->addLayout(horizontalLayout_2);

        resetButton = new QPushButton(centralWidget);
        resetButton->setObjectName(QStringLiteral("resetButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(resetButton->sizePolicy().hasHeightForWidth());
        resetButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(resetButton);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 27));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuChoose_Primitive = new QMenu(menuFile);
        menuChoose_Primitive->setObjectName(QStringLiteral("menuChoose_Primitive"));
        menuChoose_Scene_2 = new QMenu(menuFile);
        menuChoose_Scene_2->setObjectName(QStringLiteral("menuChoose_Scene_2"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(menuChoose_Scene_2->menuAction());
        menuFile->addAction(menuChoose_Primitive->menuAction());
        menuFile->addAction(action_Exit);
        menuChoose_Primitive->addAction(actionCube);
        menuChoose_Primitive->addAction(actionCylinder);
        menuChoose_Primitive->addAction(actionSphere);
        menuChoose_Primitive->addAction(actionTorus);
        menuChoose_Primitive->addAction(action_Open_Model);
        menuChoose_Scene_2->addAction(actionScene_1);
        menuChoose_Scene_2->addAction(actionScene_2);
        menuChoose_Scene_2->addAction(actionScene_3);

        retranslateUi(MainWindow);
        QObject::connect(action_Exit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action_Open_Model->setText(QApplication::translate("MainWindow", "&Open Model", 0));
        action_Exit->setText(QApplication::translate("MainWindow", "&Exit", 0));
        actionCube->setText(QApplication::translate("MainWindow", "Cube", 0));
        actionCylinder->setText(QApplication::translate("MainWindow", "Cylinder", 0));
        actionSphere->setText(QApplication::translate("MainWindow", "Sphere", 0));
        actionTorus->setText(QApplication::translate("MainWindow", "Torus", 0));
        actionSoft_Mode->setText(QApplication::translate("MainWindow", "Soft Mode", 0));
        actionScene_1->setText(QApplication::translate("MainWindow", "Scene 1", 0));
        actionScene_2->setText(QApplication::translate("MainWindow", "Scene 2", 0));
        actionScene_3->setText(QApplication::translate("MainWindow", "Scene 3", 0));
        label->setText(QApplication::translate("MainWindow", "Bending Stiffness:", 0));
        labelSolver->setText(QApplication::translate("MainWindow", "Solver:", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Gauss-Seidel", 0)
         << QApplication::translate("MainWindow", "Weighted Jacobi", 0)
        );
        labelIterations->setText(QApplication::translate("MainWindow", "Iterations:", 0));
        resetButton->setText(QApplication::translate("MainWindow", "Reset", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuChoose_Primitive->setTitle(QApplication::translate("MainWindow", "Choose Object", 0));
        menuChoose_Scene_2->setTitle(QApplication::translate("MainWindow", "Choose Scene", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
