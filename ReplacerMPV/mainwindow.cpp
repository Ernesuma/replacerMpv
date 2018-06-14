#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // route the needed gui widgets signals to the mainwindows signals
    QObject::connect(ui->pushButton_replace, SIGNAL(clicked()), this, SIGNAL(pushBtnReplace_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
