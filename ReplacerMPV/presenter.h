#ifndef PRESENTER_H
#define PRESENTER_H

#include<QObject>
#include<QDebug>

#include"mainwindow.h"


class Presenter : public QObject
{
    Q_OBJECT

    // private member
    MainWindow* m_pMainWindow{NULL};

public:
    // constructor
    Presenter(MainWindow* mainWindow);

public slots:
    void mwPushBtnReplaceClicked();
};

#endif // PRESENTER_H
