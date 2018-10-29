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
#include "projectManager.h"


class Presenter : public QObject
{
    Q_OBJECT

    // private member
    MainWindow* m_pMainWindow{NULL};
    Model* m_pModel{NULL};
    ProjectManager *m_pProjectManager{NULL};

public:
    // constructor
    Presenter(MainWindow* pMainWindow,
              Model* pModel,
              ProjectManager* pProjectManager);

private slots:
    // slots for the main windows (mw) signals
    void mwPushBtnReplaceClicked();
    void mwPushBtnC2CPlainClicked() const;
    void mwPushBtnExportFinalClicked() const;
    void mwPushBtnC2CFinalClicked() const;
    void mwPushBtnAddTag_clicked();
    void mwPushBtnRemoveSelTags();
    void mwPushBtnRemoveAllTags();
    void mwTextEditPlainChanged();
    void mwMenuNew();
    void mwMenuLoad();
    void mwMenuSave() const;
    void mwMenuSaveAs() const;
    void mwMenuExit();
    void mwMenuImportPlain();
    void mwMenuImportTags();
    void mwMenuExportPlain() const;
    void mwMenuExportFinal() const;
    void mwMenuExportTags() const;
    void mwMenuAbout() const;
    void mwMenuMenu_aboutToShow();
    void mwMenuData_aboutToShow();
    void mwMenuHelp_aboutToShow();

    // slots for the tag map models error messages
    void tmmFilteredKey(const QString original, const QString filtered) const;
    void tmmEmptyKey() const;
    void tmmDoubletKey(const QString tag) const;

    // project handling
    void somethingSavableChanged();
    void currentProjectChanged(const Project project);

private:
    void enableDisableTagRemovalBtns();
    void importPlain();
    void importTags();
    void exportText(const QString &text,
                    const QString &strFileDialogTitle,
                    const QString &strSuccessMsg,
                    const QString &strFailedMsg) const;
    void exportTags() const;
    void exportFinal() const;
};

#endif // PRESENTER_H
