#ifndef PRESENTER_H
#define PRESENTER_H

#include<QObject>
#include<QDebug>

#include"model.h"
#include"mainwindow.h"


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
    void mwPushBtnReplaceClicked();
    void mwTextEditPlainChanged();
};

#endif // PRESENTER_H
