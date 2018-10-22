#include "projectmanagerdialogspresenter.h"

ProjectManagerDialogsPresenter::ProjectManagerDialogsPresenter() {

}

IProjectManagerDialogsPresenter::EResult ProjectManagerDialogsPresenter::wannaSaveB4New() const {
    return wannaSave("Do you want to save your changes before creating a new project?");
}

IProjectManagerDialogsPresenter::EResult ProjectManagerDialogsPresenter::wannaSave(QString text) const {

    QMessageBox::StandardButton answer = MessageBoxHelper::saveDiscardCancelMsgBox(
                                            "There are unsaved modifications!", text);
    switch (answer) {
    case QMessageBox::Save:
        return IProjectManagerDialogsPresenter::EResult::YES;
        break;
    case QMessageBox::Discard:
        return IProjectManagerDialogsPresenter::EResult::NO;
        break;
    case QMessageBox::Cancel:
        return IProjectManagerDialogsPresenter::EResult::CANCEL;
        break;
    default:
        break;
    }
    return IProjectManagerDialogsPresenter::EResult::ERROR;
}
