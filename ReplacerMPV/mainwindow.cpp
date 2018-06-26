#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create the Menubar and the entries
    createMenus();

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
    // delete the ui
    delete ui;
}

QString MainWindow::getPlainText() const
{
    // return the plain text from the text edit widget
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

const QItemSelectionModel *MainWindow::getTagMapSelection()
{
    // return the selected items from the table view widget
    return ui->tableView->selectionModel();
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

void MainWindow::enableRemoveSelTagsBtn(const bool bEnable)
{
    // enable button if parameter is true et vice versa
    ui->pushButton_remove_selected_tags->setEnabled(bEnable);
}

void MainWindow::enableRemoveAllTagsBtn(const bool bEnable)
{
    // enable button if parameter is true et vice versa
    ui->pushButton_remove_all_tags->setEnabled(bEnable);
}

void MainWindow::createMenus()
{
    // add menu "Menu" to the menuBar
    // use tr(…) function to mark charecter acting as <Alt-…> keybinding
    // (Note that menuBar takes ownership of the new menu! -> No explicit deletion of m_menuMenu needed!)
    m_menuMenu = ui->menuBar->addMenu(tr("&Menu"));
    m_menuData = ui->menuBar->addMenu(tr("&Data"));
    m_menuHelp = ui->menuBar->addMenu(tr("&Help"));

    // create "Exit" action
    QAction *exitAction = new QAction(tr("&Exit"), this);
    // add standard shortcut for closing
    exitAction->setShortcut(QKeySequence::Quit);
    // add status bar tooltip
    exitAction->setStatusTip(tr("close this application"));
    // connect this actions triggered SIGNAL to the menu exit signal
    QObject::connect(exitAction, SIGNAL(triggered(bool)), this, SIGNAL(menuExit()));

    QAction *newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("create new project"));
    //connect(newAction, &QAction::triggered, this, &MainWindow::menuNew);

    m_actionSave = new QAction(tr("&Save"), this);
    m_actionSave->setShortcut(QKeySequence::Save);
    m_actionSave->setStatusTip(tr("save project"));
    //connect(m_actionSave, &QAction::triggered, this, &MainWindow::menuSave);

    QAction *saveAsAction = new QAction(tr("Save &As"), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("save project as …"));
    //connect(saveAsAction, &QAction::triggered, this, &MainWindow::menuSaveAs);

    QAction *loadAction = new QAction(tr("&Load"), this);
    loadAction->setShortcut(QKeySequence::Open);
    loadAction->setStatusTip(tr("load project"));
    //connect(loadAction, &QAction::triggered, this, &MainWindow::menuLoad);

    QAction* importPlainAction = new QAction(tr("&Import Plain Text from File"), this);
    importPlainAction->setStatusTip(tr("import plain text from a text file"));
    //connect(importPlainAction, &QAction::triggered, this, &MainWindow::menuImportPlain);

    QAction* importTagList = new QAction(tr("&Import Tag List from File"), this);
    importTagList->setStatusTip(tr("import tag list from a file"));
    //connect(importTagList, &QAction::triggered, this, &MainWindow::menuImportTagList);

    m_actionExportPlain = new QAction(tr("&Export Plain Text to File"), this);
    m_actionExportPlain->setStatusTip("write plain text to a file");
    //connect(m_actionExportPlain, &QAction::triggered, this, &MainWindow::menuExportPlain);

    m_actionExportFinal = new QAction(tr("&Export Final Text to File"), this);
    m_actionExportFinal->setStatusTip(tr("write final text to file"));
    //connect(m_actionExportFinal, &QAction::triggered, this, &MainWindow::menuExportFinal);

    m_actionExportTagList = new QAction(tr("&Export Tag List to File"), this);
    m_actionExportTagList->setStatusTip("write the tag list to a file");
    //connect(m_actionExportTagList, &QAction::triggered, this, &MainWindow::menuExportTagList);

    QAction *aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("show about dialog"));
    //connect(aboutAction, &QAction::triggered, this, &MainWindow::menuAbout);

    // add actions to menus
    // the QMenu::addAction takes ownership of the returned QAction
    m_menuMenu->addAction(newAction);
    m_menuMenu->addAction(loadAction);
    m_menuMenu->addAction(m_actionSave);
    m_menuMenu->addAction(saveAsAction);
    m_menuMenu->addSeparator();
    m_menuMenu->addAction(exitAction);

    m_menuData->addAction(importPlainAction);
    m_menuData->addAction(importTagList);
    m_menuData->addSeparator();
    m_menuData->addAction(m_actionExportPlain);
    m_menuData->addAction(m_actionExportFinal);
    m_menuData->addAction(m_actionExportTagList);

    m_menuHelp->addAction(aboutAction);

}
