#include "presenter.h"

/*
 * constructor
 */
Presenter::Presenter(MainWindow *pMainWindow, Model *pModel) :
    m_pMainWindow(pMainWindow),
    m_pModel(pModel)
{
    // connect the main windows signals to the presenters slots
    // --------------------------------------------------------
    // push buttons
    QObject::connect(m_pMainWindow, SIGNAL(pushBtnReplace_clicked()),
                     this, SLOT(mwPushBtnReplaceClicked()));
    QObject::connect(m_pMainWindow, SIGNAL(pushBtnC2cPlain_clicked()),
                     this, SLOT(mwPushBtnC2CPlainClicked()));
    QObject::connect(m_pMainWindow, SIGNAL(pushBtnC2cFinal_clicked()),
                     this, SLOT(mwPushBtnC2CFinalClicked()));
    QObject::connect(m_pMainWindow, SIGNAL(pushBtnAddTag_clicked()),
                     this, SLOT(mwPushBtnAddTag_clicked()));
    QObject::connect(m_pMainWindow, SIGNAL(pushBtnRemoveSelectedTags_clicked()),
                     this, SLOT(mwPushBtnRemoveSelTags()));
    QObject::connect(m_pMainWindow, SIGNAL(pushBtnRemoveAllTags_clicked()),
                     this, SLOT(mwPushBtnRemoveAllTags()));

    // text edits
    QObject::connect(m_pMainWindow, SIGNAL(textEditPlain_textChanged()),
                     this, SLOT(mwTextEditPlainChanged()));

    // menu 'Menu'
    QObject::connect(m_pMainWindow, SIGNAL(menuNew()),
                     this, SLOT(mwMenuNew()));
    QObject::connect(m_pMainWindow, SIGNAL(menuLoad()),
                     this, SLOT(mwMenuLoad()));
    QObject::connect(m_pMainWindow, SIGNAL(menuSave()),
                     this, SLOT(mwMenuSave()));
    QObject::connect(m_pMainWindow, SIGNAL(menuSaveAs()),
                     this, SLOT(mwMenuSaveAs()));
    QObject::connect(m_pMainWindow, SIGNAL(menuExit()),
                     this, SLOT(mwMenuExit()));

    // menu 'Data'
    QObject::connect(m_pMainWindow, SIGNAL(menuImportPlain()),
                     this, SLOT(mwMenuImportPlain()));
    QObject::connect(m_pMainWindow, SIGNAL(menuImportTags()),
                     this, SLOT(mwMenuImportTags()));
    QObject::connect(m_pMainWindow, SIGNAL(menuExportPlain()),
                     this, SLOT(mwMenuExportPlain()));
    QObject::connect(m_pMainWindow, SIGNAL(menuExportFinal()),
                     this, SLOT(mwMenuExportFinal()));
    QObject::connect(m_pMainWindow, SIGNAL(menuExportTags()),
                     this, SLOT(mwMenuExportTags()));

    // menu 'Help'
    QObject::connect(m_pMainWindow, SIGNAL(menuAbout()),
                     this, SLOT(mwMenuAbout()));

    // connect tag map
    // ---------------
    // connect the tag map model to the tag map list widget
    // this way the model will be updated directly by the view et vice versa
    m_pMainWindow->setTagMapModel(m_pModel->getTagMapModelRawPtr());

    // connect the tag maps error signals to this presenter
    QObject::connect(m_pModel->getTagMapModelRawPtr(), SIGNAL(setData_filteredKey(const QString, const QString)),
                     this, SLOT(tmmFilteredKey(const QString, const QString)));
    QObject::connect(m_pModel->getTagMapModelRawPtr(), SIGNAL(setData_emptyKey()),
                     this, SLOT(tmmEmptyKey()));
    QObject::connect(m_pModel->getTagMapModelRawPtr(), SIGNAL(setData_doubletKey(const QString)),
                     this, SLOT(tmmDoubletKey(const QString)));
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
    // read the tag from the line edit
    QString tag = m_pMainWindow->getNewTag();

    // check tag for syntactical validity
    if (!TagMapModel::isKeyValid(tag))
    {
        // tag invalid: show message to user and set focus to tag line edit
        MessageBoxHelper::warnMsgBox(
            tr("Invalid tag: ") + "'" + tag + tr("'"),
            tr("Only use characters from set:\n") + TagMapModel::getValidKeyCharsString(),
            m_pMainWindow);
        m_pMainWindow->focusAddTagLineEdit();
    }
    else if (m_pModel->getTagMapModelRawPtr()->isKeyInUse(tag))
    {
        // tag is already in use
        // show message and set focus to tag line edit
        MessageBoxHelper::warnMsgBox(
            tr("The key '") + tag + tr("' is already in use."),
            tr("Aborting to add new tag!"),
            m_pMainWindow);
        m_pMainWindow->focusAddTagLineEdit();
    }
    else
    {
        // tag is valid

        // read the value from the line edit
        QString value = m_pMainWindow->getNewTagValue();
        // provide the values to the model
        m_pModel->addTag2List(tag, value);
        // clear the line edits and set focus to conveniently input the next tag
        m_pMainWindow->clearAddTagLineEdits();
        m_pMainWindow->focusAddTagLineEdit();
        // enable the tag removal buttons
        enableDisableTagRemovalBtns();
    }
}

void Presenter::mwPushBtnRemoveSelTags()
{
    // identify the selected rows
    const QItemSelectionModel* pSelect{m_pMainWindow->getTagMapSelection()};
    QModelIndexList rows = pSelect->selectedRows();

    if (!rows.isEmpty())
    {
        if (!m_pModel->removeTags(rows))
        {
            qCritical("Could not remove the selected tags");
        }
    }
    // disable the tag removal buttons if neccessary
    enableDisableTagRemovalBtns();
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

        // enable or disable the tag removal buttons
        enableDisableTagRemovalBtns();
    }
}

void Presenter::mwTextEditPlainChanged()
{
    // copy the text from the mainwindows text edit into the model
    m_pModel->setPlainText(m_pMainWindow->getPlainText());

    // disable the Copy2Clipboard button if there is no plain text
    m_pMainWindow->enableC2CPlainBtn(!m_pModel->getPlainText().isEmpty());
}

void Presenter::mwMenuNew()
{
    qInfo() << "New";
}

void Presenter::mwMenuLoad()
{
    qInfo() << "Load";
}

void Presenter::mwMenuSave() const
{
    qInfo() << "Save";
}

void Presenter::mwMenuSaveAs() const
{
    qInfo() << "SaveAs";
}

void Presenter::mwMenuExit()
{
    // close the main window
    m_pMainWindow->close();
}

void Presenter::mwMenuImportPlain()
{
    importPlain();
}

void Presenter::mwMenuImportTags()
{
    importTags();
}

void Presenter::mwMenuExportPlain() const
{
    qInfo() << "Export Plain";
}

void Presenter::mwMenuExportFinal() const
{
    qInfo() << "Export Final";
}

void Presenter::mwMenuExportTags() const
{
    qInfo() << "Export Tags";
}

void Presenter::mwMenuAbout() const
{
    qInfo() << "About";
}

void Presenter::tmmFilteredKey(const QString original,
                               const QString filtered) const
{
    MessageBoxHelper::warnMsgBox(
        tr("Filtered out invalid characters from changed tag. Instead of '") +
            original + tr("' there will be '") + filtered + tr("' used."),
        tr("Next time please use only characters from set:\n") +
            TagMapModel::getValidKeyCharsString() + tr("."),
        m_pMainWindow);
}

void Presenter::tmmEmptyKey() const
{
    MessageBoxHelper::warnMsgBox(tr("Empty tag is not allowed."),
                                 tr("Aborting tag change!"),
                                 m_pMainWindow);
}

void Presenter::tmmDoubletKey(const QString tag) const
{
    MessageBoxHelper::warnMsgBox(
        tr("The tag '") + tag + tr("' is already in use."),
        tr("Aborting tag change!"),
        m_pMainWindow);
}

void Presenter::enableDisableTagRemovalBtns()
{
    // disable the tag removal buttons depending on the tag map emptiness
    m_pMainWindow->enableRemoveSelTagsBtn(!m_pModel->isTagMapEmpty());
    m_pMainWindow->enableRemoveAllTagsBtn(!m_pModel->isTagMapEmpty());
}

void Presenter::importPlain()
{
    // open file dialog
    QString tmpStr{QFileDialog::getOpenFileName(m_pMainWindow,
                                                tr("Choose file to import plain text from"))};
    // if file dialog returned something (not cancelled by user)
    if (!tmpStr.isNull())
    {
        // convert to QDir object
        QDir importFilePath{tmpStr};

        // read files content
        QString plainText{};
        if (FileHelper::ResultCode::OK == FileHelper::readFile2String(importFilePath, plainText))
        {
            // set plain text in view (this will trigger model update)
            m_pMainWindow->setPlainText(plainText);

            // inform user about succesfull import
            MessageBoxHelper::infoMsgBox(tr("Imported plain text from file:"),
                                         importFilePath.absolutePath(),
                                         m_pMainWindow);
        }
        else
        {
            // inform user about failed import
            MessageBoxHelper::warnMsgBox(tr("Could not import chosen file:"),
                                         importFilePath.absolutePath(),
                                         m_pMainWindow);
        }
    }
}

void Presenter::importTags()
{
    // open file dialog
    QString tmpStr = QFileDialog::getOpenFileName(m_pMainWindow,
                                                  tr("Choose file to import tag list from"));
    // if file has been chosen
    if (!tmpStr.isNull())
    {
        // convert str of chosen file to QDir object
        QDir importFilePath{tmpStr};

        // read tags from file
        TagMapModel::tagMap tmpTagMap{};
        int readResult = FileHelper::readFile2TagMap(importFilePath, tmpTagMap);
        if (FileHelper::ResultCode::OK == readResult)
        {
            // clear all old tags and add the read ones
            m_pModel->clearAllTags();
            foreach(auto key, tmpTagMap.uniqueKeys())
            {
                m_pModel->getTagMapModelRawPtr()->insert(key, tmpTagMap[key]);
            }
            // disable or enable the tag removal buttons
            enableDisableTagRemovalBtns();

            // inform user about successful tag import
            MessageBoxHelper::infoMsgBox(tr("Import of tag list from file successful:"),
                                         importFilePath.absolutePath(),
                                         m_pMainWindow);
        }
        // reading tags from file failed
        else if (FileHelper::ResultCode::ERROR_FILE_OPEN == readResult)
        {
            MessageBoxHelper::warnMsgBox(tr("Failed to open file:"),
                                         importFilePath.absolutePath(),
                                         m_pMainWindow);
        }
        else if (FileHelper::ResultCode::ERROR_INVALID_FILE == readResult)
        {
            MessageBoxHelper::warnMsgBox(tr("Invalid tag file:"),
                                         importFilePath.absolutePath(),
                                         m_pMainWindow);
        }
        else
        {
            MessageBoxHelper::warnMsgBox(tr("Unknown Error during import of tag file:"),
                                         importFilePath.absolutePath(),
                                         m_pMainWindow);
        }
    }
}
