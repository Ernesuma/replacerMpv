#include "presenter.h"

Presenter::Presenter(MainWindow *pMainWindow, Model *pModel) :
    m_pMainWindow(pMainWindow),
    m_pModel(pModel)
{
    QObject::connect(pMainWindow, SIGNAL(pushBtnReplace_clicked()), this, SLOT(mwPushBtnReplaceClicked()));
}

void Presenter::mwPushBtnReplaceClicked()
{
    qInfo() << "push button replace";
}
