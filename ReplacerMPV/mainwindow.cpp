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
    QObject::connect(m_menuMenu, SIGNAL(aboutToShow()),
                     this, SIGNAL(menuMenu_aboutToShow()));
    QObject::connect(m_menuData, SIGNAL(aboutToShow()),
                     this, SIGNAL(menuData_aboutToShow()));
    QObject::connect(m_menuHelp, SIGNAL(aboutToShow()),
                     this, SIGNAL(menuHelp_aboutToShow()));

    QObject::connect(ui->pushButton_replace, SIGNAL(clicked()),
                     this, SIGNAL(pushBtnReplace_clicked()));
    QObject::connect(ui->pushButton_c2c_plain, SIGNAL(clicked()),
                     this, SIGNAL(pushBtnC2cPlain_clicked()));
    QObject::connect(ui->pushButton_exportFinal, SIGNAL(clicked()),
                     this, SIGNAL(pushBtnExportFinal_clicked()));
    QObject::connect(ui->pushButton_c2c_final, SIGNAL(clicked()),
                     this, SIGNAL(pushBtnC2cFinal_clicked()));
    QObject::connect(ui->pushButton_add_2_tag_list, SIGNAL(clicked()),
                     this, SIGNAL(pushBtnAddTag_clicked()));
    QObject::connect(ui->pushButton_remove_selected_tags, SIGNAL(clicked()),
                     this, SIGNAL(pushBtnRemoveSelectedTags_clicked()));
    QObject::connect(ui->pushButton_remove_all_tags, SIGNAL(clicked()),
                     this, SIGNAL(pushBtnRemoveAllTags_clicked()));

    QObject::connect(ui->textEdit_plain, SIGNAL(textChanged()),
                     this, SIGNAL(textEditPlain_textChanged()));
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

void MainWindow::setPlainText(const QString &text)
{
    // show the given text in the text edit
    ui->textEdit_plain->setPlainText(text);
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

void MainWindow::enableMenuActionExportPlain(const bool bEnable)
{
    // enable the menu action to export the plain text if
    // bEnable is true et vice versa
    m_actionExportPlain->setEnabled(bEnable);
}

void MainWindow::enableMenuActionExportFinal(const bool bEnable)
{
    // enable the menu action to export the final text if bEnable
    // is true et vice versa
    m_actionExportFinal->setEnabled(bEnable);
}

void MainWindow::enableMenuActionExportTags(const bool bEnable)
{
    // enable the menu action to export tags if bEnable is true
    // et vice versa
    m_actionExportTagList->setEnabled(bEnable);
}

void MainWindow::setProjectLabel(const QString &text)
{
    ui->lbl_currentProject->setText(text);
}

void MainWindow::createMenus()
{
    // add menus to menubar
    // --------------------
    // use tr(…) function to mark charecter acting as <Alt-…> keybinding
    // (Note that menuBar takes ownership of the new menu! -> No explicit deletion of m_menuMenu needed!)
    m_menuMenu = ui->menuBar->addMenu(tr("&Menu"));
    m_menuData = ui->menuBar->addMenu(tr("&Data"));
    m_menuHelp = ui->menuBar->addMenu(tr("&Help"));

    // setup actions for the menu entries
    // ----------------------------------
    // create "Exit" action
    QAction *exitAction = new QAction(tr("&Exit"), this);
    // add standard shortcut for closing
    exitAction->setShortcut(QKeySequence::Quit);
    // add status bar tooltip
    exitAction->setStatusTip(tr("close this application"));
    // connect this actions triggered SIGNAL to the menu exit signal
    QObject::connect(exitAction, SIGNAL(triggered(bool)), this, SIGNAL(menuExit()));

    // setup action for entry 'New'
    QAction *newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("create new project"));
    QObject::connect(newAction, SIGNAL(triggered(bool)), this, SIGNAL(menuNew()));

    // setup action for entry 'Save'
    m_actionSave = new QAction(tr("&Save"), this);
    m_actionSave->setShortcut(QKeySequence::Save);
    m_actionSave->setStatusTip(tr("save project"));
    QObject::connect(m_actionSave, SIGNAL(triggered(bool)), this, SIGNAL(menuSave()));

    // setup for entry 'Save As'
    QAction *saveAsAction = new QAction(tr("Save &As"), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("save project as …"));
    QObject::connect(saveAsAction, SIGNAL(triggered(bool)), this, SIGNAL(menuSaveAs()));

    // setup action for entry 'Load'
    QAction *loadAction = new QAction(tr("&Load"), this);
    loadAction->setShortcut(QKeySequence::Open);
    loadAction->setStatusTip(tr("load project"));
    QObject::connect(loadAction, SIGNAL(triggered(bool)), this, SIGNAL(menuLoad()));

    // setup action for entry 'Import Plain Text from File'
    QAction* importPlainAction = new QAction(tr("&Import Plain Text from File"), this);
    importPlainAction->setStatusTip(tr("import plain text from a text file"));
    QObject::connect(importPlainAction, SIGNAL(triggered(bool)), this, SIGNAL(menuImportPlain()));

    // setup action for entry 'Import Tag List from File'
    QAction* importTagList = new QAction(tr("&Import Tag List from File"), this);
    importTagList->setStatusTip(tr("import tag list from a file"));
    QObject::connect(importTagList, SIGNAL(triggered(bool)), this, SIGNAL(menuImportTags()));

    // setup action for entry 'Export Plain Text to File'
    m_actionExportPlain = new QAction(tr("&Export Plain Text to File"), this);
    m_actionExportPlain->setStatusTip("write plain text to a file");
    QObject::connect(m_actionExportPlain, SIGNAL(triggered(bool)), this, SIGNAL(menuExportPlain()));

    // setup action for entry 'Export Final Text to File'
    m_actionExportFinal = new QAction(tr("&Export Final Text to File"), this);
    m_actionExportFinal->setStatusTip(tr("write final text to file"));
    QObject::connect(m_actionExportFinal, SIGNAL(triggered(bool)), this, SIGNAL(menuExportFinal()));

    // setup action for entry 'Export Tag List to File'
    m_actionExportTagList = new QAction(tr("&Export Tag List to File"), this);
    m_actionExportTagList->setStatusTip("write the tag list to a file");
    QObject::connect(m_actionExportTagList, SIGNAL(triggered(bool)), this, SIGNAL(menuExportTags()));

    // setup action for entry 'About'
    QAction *aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("show about dialog"));
    QObject::connect(aboutAction, SIGNAL(triggered(bool)), this, SIGNAL(menuAbout()));

    // add actions to menus
    // --------------------
    // the QMenu::addAction takes ownership of the returned QAction!
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
