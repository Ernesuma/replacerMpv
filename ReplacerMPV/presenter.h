#ifndef PRESENTER_H
#define PRESENTER_H

#include <QObject>
#include <QDebug>
#include <QErrorMessage>
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>
#include <QItemSelectionModel>
#include <QFileDialog>

#include "model.h"
#include "mainwindow.h"
#include "replacer.h"
#include "filehelper.h"
#include "messageboxhelper.h"


class Presenter : public QObject
{
    Q_OBJECT

    // private member
    MainWindow* m_pMainWindow{NULL};
    Model* m_pModel{NULL};

public:
    // constructor
    Presenter(MainWindow* pMainWindow,
              Model* pModel);

public slots:
    // slots for the main windows (mw) signals
    void mwPushBtnReplaceClicked();
    void mwPushBtnC2CPlainClicked() const;
    void mwPushBtnC2CFinalClicked() const;
    void mwPushBtnAddTag_clicked();
    void mwPushBtnRemoveSelTags();
    void mwPushBtnRemoveAllTags();
    void mwTextEditPlainChanged();
    void mwMenuNew();
    void mwMenuLoad();
    void mwMenuSave();
    void mwMenuSaveAs();
    void mwMenuExit();
    void mwMenuImportPlain();
    void mwMenuImportTags();
    void mwMenuExportPlain();
    void mwMenuExportFinal();
    void mwMenuExportTags();
    void mwMenuAbout();

    // slots for the tag map models error messages
    void tmmFilteredKey(const QString original, const QString filtered) const;
    void tmmEmptyKey() const;
    void tmmDoubletKey(const QString tag) const;

private:
    void enableDisableTagRemovalBtns();
    void importPlain();
    void importTags();
};

#endif // PRESENTER_H
