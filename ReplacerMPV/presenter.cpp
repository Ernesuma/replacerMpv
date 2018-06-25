#include "presenter.h"

Presenter::Presenter(MainWindow *pMainWindow, Model *pModel) :
    m_pMainWindow(pMainWindow),
    m_pModel(pModel)
{
    QObject::connect(pMainWindow, SIGNAL(pushBtnReplace_clicked()),
                     this, SLOT(mwPushBtnReplaceClicked()));
    QObject::connect(pMainWindow, SIGNAL(pushBtnAddTag_clicked()),
                     this, SLOT(mwPushBtnAddTag_clicked()));
    QObject::connect(pMainWindow, SIGNAL(textEditPlain_textChanged()),
                     this, SLOT(mwTextEditPlainChanged()));

    // connect the tag map model to the tag map list widget
    // this way the model will be updated directly by the view et vice versa
    m_pMainWindow->setTagMapModel(m_pModel->getTagMapModelRawPtr());
}

void Presenter::mwPushBtnReplaceClicked()
{
    // TODO: delete test output
    qInfo() << "push button replace";
    qInfo() << m_pModel->getPlainText();
}

void Presenter::mwPushBtnAddTag_clicked()
{
    qInfo() << "push button 'add tag' clicked";

    QString tag = m_pMainWindow->getNewTag();
    QString value = m_pMainWindow->getNewTagValue();

    m_pModel->addTag2List(tag, value);

    m_pMainWindow->clearAddTagLineEdits();
    m_pMainWindow->focusAddTagLineEdit();
}

/*
 * copy the text from the mainwindows text edit into the model
 */
void Presenter::mwTextEditPlainChanged()
{
    m_pModel->setPlainText(m_pMainWindow->getPlainText());
}
