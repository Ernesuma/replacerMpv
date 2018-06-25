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

QString MainWindow::getNewTag() const
{
    // return the text from the 'newTag' line edit
    return ui->lineEdit_newTag->text();
}

QString MainWindow::getNewTagValue() const
{
    // return the text from the 'newValue' line edit
    return ui->lineEdit_newValue->text();
}

void MainWindow::setTagMapModel(QAbstractItemModel *pTagMapModel)
{
    // connect pTagMapModel to the table view
    ui->tableView->setModel(pTagMapModel);
}

void MainWindow::setFinalText(const QString &text)
{
    // show the final text in the text edit
    ui->textEdit_final->setPlainText(text);
}

void MainWindow::clearAddTagLineEdits()
{
    // clear both 'new tag' line edits
    ui->lineEdit_newTag->clear();
    ui->lineEdit_newValue->clear();
}

void MainWindow::focusAddTagLineEdit()
{
    // set the focus to the first 'new tag' line edit
    ui->lineEdit_newTag->setFocus();
}

void MainWindow::enableC2CPlainBtn(const bool bEnable)
{
    // enable button if parameter is true et vice versa
    ui->pushButton_c2c_plain->setEnabled(bEnable);
}

void MainWindow::enableC2CFinalBtn(const bool bEnable)
{
    // enable button if parameter is true et vice versa
    ui->pushButton_c2c_final->setEnabled(bEnable);
}

void MainWindow::enableExportFinalBtn(const bool bEnable)
{
    // enable button if parameter is true et vice versa
    ui->pushButton_exportFinal->setEnabled(bEnable);
}
