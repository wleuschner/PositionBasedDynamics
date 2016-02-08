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
    QAction *actionScene1;
    QAction *actionScene2;
    QAction *actionScene3;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    Canvas *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QDoubleSpinBox *spinBoxPressure;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QDoubleSpinBox *spinBoxStretch;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelCompress;
    QDoubleSpinBox *spinBoxCompress;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QDoubleSpinBox *spinBoxBend;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelSolver;
    QComboBox *comboBoxSolver;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelIterations;
    QSpinBox *iterationSpinBox;
    QPushButton *resetButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuScene;
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
        actionScene1 = new QAction(MainWindow);
        actionScene1->setObjectName(QStringLiteral("actionScene1"));
        actionScene2 = new QAction(MainWindow);
        actionScene2->setObjectName(QStringLiteral("actionScene2"));
        actionScene3 = new QAction(MainWindow);
        actionScene3->setObjectName(QStringLiteral("actionScene3"));
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
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_7->addWidget(label_3);

        spinBoxPressure = new QDoubleSpinBox(centralWidget);
        spinBoxPressure->setObjectName(QStringLiteral("spinBoxPressure"));
        spinBoxPressure->setMaximum(100);
        spinBoxPressure->setSingleStep(0.1);
        spinBoxPressure->setValue(1);

        horizontalLayout_7->addWidget(spinBoxPressure);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_6->addWidget(label_2);

        spinBoxStretch = new QDoubleSpinBox(centralWidget);
        spinBoxStretch->setObjectName(QStringLiteral("spinBoxStretch"));
        spinBoxStretch->setMaximum(1);
        spinBoxStretch->setSingleStep(0.1);
        spinBoxStretch->setValue(0.5);

        horizontalLayout_6->addWidget(spinBoxStretch);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        labelCompress = new QLabel(centralWidget);
        labelCompress->setObjectName(QStringLiteral("labelCompress"));

        horizontalLayout_5->addWidget(labelCompress);

        spinBoxCompress = new QDoubleSpinBox(centralWidget);
        spinBoxCompress->setObjectName(QStringLiteral("spinBoxCompress"));
        spinBoxCompress->setMaximum(1);
        spinBoxCompress->setSingleStep(0.1);
        spinBoxCompress->setValue(0.5);

        horizontalLayout_5->addWidget(spinBoxCompress);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_4->addWidget(label);

        spinBoxBend = new QDoubleSpinBox(centralWidget);
        spinBoxBend->setObjectName(QStringLiteral("spinBoxBend"));

        horizontalLayout_4->addWidget(spinBoxBend);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelSolver = new QLabel(centralWidget);
        labelSolver->setObjectName(QStringLiteral("labelSolver"));

        horizontalLayout_3->addWidget(labelSolver);

        comboBoxSolver = new QComboBox(centralWidget);
        comboBoxSolver->setObjectName(QStringLiteral("comboBoxSolver"));

        horizontalLayout_3->addWidget(comboBoxSolver);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelIterations = new QLabel(centralWidget);
        labelIterations->setObjectName(QStringLiteral("labelIterations"));

        horizontalLayout_2->addWidget(labelIterations);

        iterationSpinBox = new QSpinBox(centralWidget);
        iterationSpinBox->setObjectName(QStringLiteral("iterationSpinBox"));
        iterationSpinBox->setMaximum(1000);
        iterationSpinBox->setValue(20);

        horizontalLayout_2->addWidget(iterationSpinBox);


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
        menuScene = new QMenu(menuFile);
        menuScene->setObjectName(QStringLiteral("menuScene"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(menuScene->menuAction());
        menuFile->addAction(action_Exit);
        menuScene->addAction(actionScene1);
        menuScene->addAction(actionScene2);
        menuScene->addAction(actionScene3);

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
        actionScene1->setText(QApplication::translate("MainWindow", "Scene1", 0));
        actionScene2->setText(QApplication::translate("MainWindow", "Scene2", 0));
        actionScene3->setText(QApplication::translate("MainWindow", "Scene3", 0));
        label_3->setText(QApplication::translate("MainWindow", "Pressure:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Stretch Stiffness:", 0));
        labelCompress->setText(QApplication::translate("MainWindow", "Compress Stiffness:", 0));
        label->setText(QApplication::translate("MainWindow", "Bending Stiffness:", 0));
        labelSolver->setText(QApplication::translate("MainWindow", "Solver:", 0));
        comboBoxSolver->clear();
        comboBoxSolver->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Gauss-Seidel", 0)
         << QApplication::translate("MainWindow", "Weighted Jacobi", 0)
        );
        labelIterations->setText(QApplication::translate("MainWindow", "Iterations:", 0));
        resetButton->setText(QApplication::translate("MainWindow", "Reset", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuScene->setTitle(QApplication::translate("MainWindow", "Scene", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
