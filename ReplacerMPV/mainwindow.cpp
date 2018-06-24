#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // route the needed gui widgets signals to the mainwindows signals
    QObject::connect(ui->pushButton_replace, SIGNAL(clicked()), this, SIGNAL(pushBtnReplace_clicked()));
    QObject::connect(ui->pushButton_c2c_plain, SIGNAL(clicked()), this, SIGNAL(pushBtnC2cPlain_clicked()));
    QObject::connect(ui->pushButton_exportFinal, SIGNAL(clicked()), this, SIGNAL(pushBtnExportFinal_clicked()));
    QObject::connect(ui->pushButton_c2c_final, SIGNAL(clicked()), this, SIGNAL(pushBtnC2cFinal_clicked()));
    QObject::connect(ui->pushButton_add_2_tag_list, SIGNAL(clicked()), this, SIGNAL(pushBtnAddTag_clicked()));
    QObject::connect(ui->pushButton_remove_selected_tags, SIGNAL(clicked()), this, SIGNAL(pushBtnRemoveSelectedTags_clicked()));
    QObject::connect(ui->pushButton_remove_all_tags, SIGNAL(clicked()), this, SIGNAL(pushBtnRemoveAllTags_clicked()));

    QObject::connect(ui->textEdit_plain, SIGNAL(textChanged()), this, SIGNAL(textEditPlain_textChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getPlainText() const
{
    return ui->textEdit_plain->toPlainText();
}

void MainWindow::setTagMapModel(QAbstractItemModel *pTagMapModel)
{
    ui->tableView->setModel(pTagMapModel);
}
