#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->iterationSpinBox,SIGNAL(valueChanged(int)),ui->widget,SLOT(changeSolverLoops(int)));
    connect(ui->spinBoxStretch,SIGNAL(valueChanged(double)),ui->widget,SLOT(changeStretchStiffness(double)));
    connect(ui->spinBoxCompress,SIGNAL(valueChanged(double)),ui->widget,SLOT(changeCompressStiffness(double)));
    connect(ui->spinBoxBend,SIGNAL(valueChanged(double)),ui->widget,SLOT(changeBendStiffness(double)));
    connect(ui->resetButton,SIGNAL(clicked()),this,SLOT(reset()));
    reset();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset()
{
    ui->spinBoxBend->setValue(0.5);
    ui->spinBoxStretch->setValue(0.5);
    ui->spinBoxCompress->setValue(0.5);
    ui->iterationSpinBox->setValue(20);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    event->ignore();
}

