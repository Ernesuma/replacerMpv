#include "projectmanagerdialogspresenter.h"

ProjectManagerDialogsPresenter::ProjectManagerDialogsPresenter() {

}

IProjectManagerDialogsPresenter::EResult ProjectManagerDialogsPresenter::wannaSaveB4New(QWidget *parent) const {
    return wannaSave("Do you want to save your changes before creating a new project?", parent);
}

IProjectManagerDialogsPresenter::EResult ProjectManagerDialogsPresenter::wannaSave(QString text, QWidget *parent) const {

    QMessageBox::StandardButton answer = MessageBoxHelper::saveDiscardCancelMsgBox(
                                            "There are unsaved modifications!", text, parent);
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
        // do nothing
        break;
    }
    return IProjectManagerDialogsPresenter::EResult::ERROR;
}

IProjectManagerDialogsPresenter::EResult ProjectManagerDialogsPresenter::selectProject(Project &project,
                                                                                      QWidget *parent) const {
    std::unique_ptr<SelectProjectDialogPresenter> pSelPrjDlgPresenter(
                new SelectProjectDialogPresenter(nullptr, parent));

    QString name{};
    QDir path{};
    QDialog::DialogCode answer = pSelPrjDlgPresenter.get()->exec(name, path);
    project.setName(name);
    project.setProjectDir(path);
    qDebug() << "answer: '" << answer << "'";

    return IProjectManagerDialogsPresenter::EResult::OK;
}
