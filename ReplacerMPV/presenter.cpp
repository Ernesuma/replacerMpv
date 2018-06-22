#include "presenter.h"

Presenter::Presenter(MainWindow *pMainWindow, Model *pModel) :
    m_pMainWindow(pMainWindow),
    m_pModel(pModel)
{
    QObject::connect(pMainWindow, SIGNAL(pushBtnReplace_clicked()),
                     this, SLOT(mwPushBtnReplaceClicked()));
    QObject::connect(pMainWindow, SIGNAL(textEditPlain_textChanged()),
                     this, SLOT(mwTextEditPlainChanged()));
}

void Presenter::mwPushBtnReplaceClicked()
{
    // TODO: delete test output
    qInfo() << "push button replace";
    qInfo() << m_pModel->getPlainText();
}

/*
 * copy the text from the mainwindows text edit into the model
 */
void Presenter::mwTextEditPlainChanged()
{
    m_pModel->setPlainText(m_pMainWindow->getPlainText());
}
