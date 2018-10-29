#include "projectManager.h"

ProjectManager::ProjectManager() :
    m_pDialogPresenter(new ProjectManagerDialogsPresenter()) {
}

ProjectManager::~ProjectManager() {
    delete m_pCurrentProject;
}

void ProjectManager::somethingChanged() {
    qInfo() << "something changed";
    m_bUnsavedChangesExist = true;
}

ProjectManager::EResult ProjectManager::newProject(QWidget *parent) {
    enum EStates {
        eInvalid,
        eNew,
        eSaveB4New,
        eSaveB4NewNoProj,
        eWannaSave,
        eFinished
    };

    EStates eState = eInvalid;
    if (this->allSaved()) {
        eState = eNew;
    } else {
        eState = eWannaSave;
    }
    while (eFinished != eState) {
        qInfo() << eState;
        switch (eState) {
        case eNew:
            // Todo: implement
            eState = EStates::eFinished;
            break;
        case eSaveB4New:
            eState = EStates::eNew;
            break;
        case eSaveB4NewNoProj:
        {
            Project project{};
            const IProjectManagerDialogsPresenter::EResult answer = m_pDialogPresenter.get()->selectProject(project, parent);
            //if (IProjectManagerDialogsPresenter::EResult::OK ==
            eState = EStates::eSaveB4New;
        }
            break;
        case eWannaSave:
        {
            // ask if the user wants to save unsaved changes
            const IProjectManagerDialogsPresenter::EResult answer = m_pDialogPresenter.get()->wannaSaveB4New(parent);
            // yes
            if (IProjectManagerDialogsPresenter::EResult::YES == answer) {
                if (projectSet()) {
                    eState = EStates::eSaveB4New;
                } else {
                    eState = EStates::eSaveB4NewNoProj;
                }
            // no
            } else if (IProjectManagerDialogsPresenter::EResult::NO == answer) {
                eState = EStates::eNew;
            // cancel
            } else {
                eState = EStates::eFinished;
            }
        }
            break;
        case eInvalid:
            qInfo() << "ERROR: got invalid state in projectManager";
            eState = EStates::eFinished;
            break;
        default:
            eState = eInvalid;
            break;
        }
    }
    return EResult::OK;
}



bool ProjectManager::projectSet() const {
    // todo: implement
    return false;
}

bool ProjectManager::allSaved() const {
    return !m_bUnsavedChangesExist;
}

void ProjectManager::setCurrentProject() {
    // todo: implement
}

