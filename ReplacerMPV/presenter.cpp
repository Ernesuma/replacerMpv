#include "presenter.h"

Presenter::Presenter(MainWindow *pMainWindow, Model *pModel) :
    m_pMainWindow(pMainWindow),
    m_pModel(pModel)
{
    QObject::connect(pMainWindow, SIGNAL(pushBtnReplace_clicked()),
                     this, SLOT(mwPushBtnReplaceClicked()));
    QObject::connect(pMainWindow, SIGNAL(pushBtnC2cPlain_clicked()),
                     this, SLOT(mwPushBtnC2CPlainClicked()));
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
    // call replacer on plain text and save to QString varible 'finalText'
    QString finalText{""};
    if (!Replacer::replace(m_pModel->getPlainText(),
                           finalText,
                           m_pModel->getTagMap()))
    {
        // if call to replace returns error value: log the error
        qCritical("Could not replace the tags");
    }
    // set final text in the main window, which will print it to the user
    m_pMainWindow->setFinalText(finalText);
}

void Presenter::mwPushBtnC2CPlainClicked() const
{
    // copy plain text from model to the clipboard
    const QString& tmp = m_pModel->getPlainText();
    QApplication::clipboard()->setText(tmp);
}

void Presenter::mwPushBtnAddTag_clicked()
{
    qInfo() << "push button 'add tag' clicked";

    // read the values from the line edits
    QString tag = m_pMainWindow->getNewTag();
    QString value = m_pMainWindow->getNewTagValue();

    // provide the values to the model
    m_pModel->addTag2List(tag, value);

    // clear the line edits and set focus to conveniently input the next tag
    m_pMainWindow->clearAddTagLineEdits();
    m_pMainWindow->focusAddTagLineEdit();
}

void Presenter::mwTextEditPlainChanged()
{
    // copy the text from the mainwindows text edit into the model
    m_pModel->setPlainText(m_pMainWindow->getPlainText());

    // disable the Copy2Clipboard button if there is no plain text
    m_pMainWindow->enableC2CPlainBtn(!m_pModel->getPlainText().isEmpty());
}
