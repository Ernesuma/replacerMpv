#include "presenter.h"

Presenter::Presenter(MainWindow *pMainWindow) :
    m_pMainWindow(pMainWindow)
{
    QObject::connect(pMainWindow, SIGNAL(pushBtnReplace_clicked()), this, SLOT(mwPushBtnReplaceClicked()));
}

void Presenter::mwPushBtnReplaceClicked()
{
    qInfo() << "push button replace";
}
