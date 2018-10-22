#include "projectManager.h"

ProjectManager::ProjectManager() :
    m_dialogPresenter(new ProjectManagerDialogsPresenter()) {
}

ProjectManager::~ProjectManager() {
    delete m_pCurrentProject;
}

void ProjectManager::somethingChanged() {
    qInfo() << "something changed";
    m_bUnsavedChangesExist = true;
}

ProjectManager::EResult ProjectManager::newProject() {
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
            eState = EStates::eSaveB4New;
            break;
        case eWannaSave:
        {
            const IProjectManagerDialogsPresenter::EResult answer = m_dialogPresenter.get()->wannaSaveB4New();
            if (IProjectManagerDialogsPresenter::EResult::YES == answer) {
                if (projectSet()) {
                    eState = EStates::eSaveB4New;
                } else {
                    eState = EStates::eSaveB4NewNoProj;
                }
            } else if (IProjectManagerDialogsPresenter::EResult::NO == answer) {
                eState = EStates::eNew;
            } else {
                eState = EStates::eFinished;
            }
        }
            break;
        case eInvalid:
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
    return true;
}

bool ProjectManager::allSaved() const {
    return !m_bUnsavedChangesExist;
}

void ProjectManager::setCurrentProject() {
    // todo: implement
}

