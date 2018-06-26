#include "presenter.h"

Presenter::Presenter(MainWindow *pMainWindow, Model *pModel) :
    m_pMainWindow(pMainWindow),
    m_pModel(pModel)
{
    QObject::connect(pMainWindow, SIGNAL(pushBtnReplace_clicked()),
                     this, SLOT(mwPushBtnReplaceClicked()));
    QObject::connect(pMainWindow, SIGNAL(pushBtnC2cPlain_clicked()),
                     this, SLOT(mwPushBtnC2CPlainClicked()));
    QObject::connect(pMainWindow, SIGNAL(pushBtnC2cFinal_clicked()),
                     this, SLOT(mwPushBtnC2CFinalClicked()));
    QObject::connect(pMainWindow, SIGNAL(pushBtnAddTag_clicked()),
                     this, SLOT(mwPushBtnAddTag_clicked()));
    QObject::connect(pMainWindow, SIGNAL(pushBtnRemoveSelectedTags_clicked()),
                     this, SLOT(mwPushBtnRemoveSelTags()));
    QObject::connect(pMainWindow, SIGNAL(pushBtnRemoveAllTags_clicked()),
                     this, SLOT(mwPushBtnRemoveAllTags()));

    QObject::connect(pMainWindow, SIGNAL(textEditPlain_textChanged()),
                     this, SLOT(mwTextEditPlainChanged()));

    // connect the tag map model to the tag map list widget
    // this way the model will be updated directly by the view et vice versa
    m_pMainWindow->setTagMapModel(m_pModel->getTagMapModelRawPtr());
}

void Presenter::mwPushBtnReplaceClicked()
{
    // let the tmpFinalText just be valid inside this scope {…}
    {
        QString tmpFinalText{""};
        // call replacer on plain text and save to QString varible 'tmpFinalText'
        if (!Replacer::replace(m_pModel->getPlainText(),
                               tmpFinalText,
                               m_pModel->getTagMap()))
        {
            // if call to replace returns error value: log the error
            qCritical("Could not replace the tags");
        }
        // set final text in the model
        m_pModel->setFinalText(tmpFinalText);
    }

    // set final text in the main window, which will print it to the user
    m_pMainWindow->setFinalText(m_pModel->getFinalText());

    // enable export and copy2Clipboard buttons for final text, if text is not empty
    const bool bEnableBtns = !m_pModel->getFinalText().isEmpty();
    m_pMainWindow->enableC2CFinalBtn(bEnableBtns);
    m_pMainWindow->enableExportFinalBtn(bEnableBtns);
}

void Presenter::mwPushBtnC2CPlainClicked() const
{
    // copy plain text from model to the clipboard
    const QString& tmp = m_pModel->getPlainText();
    QApplication::clipboard()->setText(tmp);
}

void Presenter::mwPushBtnC2CFinalClicked() const
{
    // copy final text from model to the clipboard
    const QString& tmp = m_pModel->getFinalText();
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

    // enable the tag removal buttons
    if (!m_pModel->isTagMapEmpty())
    {
        m_pMainWindow->enableRemoveSelTagsBtn(true);
        m_pMainWindow->enableRemoveAllTagsBtn(true);
    }
}

void Presenter::mwPushBtnRemoveSelTags()
{
    qInfo() << "remove selected tags";
}

void Presenter::mwPushBtnRemoveAllTags()
{
    // create Message Box to ask user for confirmation
    QMessageBox mBox(m_pMainWindow);
    mBox.setText(tr("Do you really want to delete all tags?"));
    mBox.setInformativeText(tr("Click 'OK' to delete all tags."));
    mBox.setIcon(QMessageBox::Question);
    mBox.setStandardButtons(QMessageBox::Abort | QMessageBox::Ok);
    mBox.setDefaultButton(QMessageBox::Abort);
    auto retVal = mBox.exec();

    // if user confirmed removal of all tags:
    if (QMessageBox::Ok == retVal)
    {
        m_pModel->clearAllTags();
        //m_pMainWindow->clearSelectionOfTagMapTableView();

        // disable the tag removal buttons
        if (m_pModel->isTagMapEmpty())
        {
            m_pMainWindow->enableRemoveSelTagsBtn(false);
            m_pMainWindow->enableRemoveAllTagsBtn(false);
        }
    }
}

void Presenter::mwTextEditPlainChanged()
{
    // copy the text from the mainwindows text edit into the model
    m_pModel->setPlainText(m_pMainWindow->getPlainText());

    // disable the Copy2Clipboard button if there is no plain text
    m_pMainWindow->enableC2CPlainBtn(!m_pModel->getPlainText().isEmpty());
}
