#include "presenter.h"

Presenter::Presenter(MainWindow *mainWindow)
{
    QObject::connect(mainWindow, SIGNAL(pushBtnReplace_clicked()), this, SLOT(mwPushBtnReplaceClicked()));
}

void Presenter::mwPushBtnReplaceClicked()
{
    qInfo() << "push button replace";
}
