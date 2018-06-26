#ifndef PRESENTER_H
#define PRESENTER_H

#include<QObject>
#include<QDebug>
#include<QErrorMessage>
#include<QApplication>
#include<QClipboard>
#include<QMessageBox>
#include<QItemSelectionModel>

#include"model.h"
#include"mainwindow.h"
#include"replacer.h"


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
    void mwMenuExit();
};

#endif // PRESENTER_H
