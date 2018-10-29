#include "projectManager.h"

ProjectManager::ProjectManager() :
    m_pDialogPresenter(new ProjectManagerDialogsPresenter()) {
}

ProjectManager::~ProjectManager() {
    //delete m_pCurrentProject;
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

    Project *pProject{nullptr};
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
            qInfo() << "proect name: " << pProject->getName();
            qInfo() << "save text to: " << pProject->getPlainTextFilePath();
            qInfo() << "save tags to: " << pProject->getTagsFilePath();

            eState = EStates::eNew;
            break;
        case eSaveB4NewNoProj:
        {
            const IProjectManagerDialogsPresenter::EResult answer = m_pDialogPresenter.get()->selectProject(*pProject, parent);
            qDebug() << eState << ": answer: " << answer;
            qDebug() << "project: " << pProject->getName() << ", " << pProject->getProjectDir();
            if (IProjectManagerDialogsPresenter::EResult::OK == answer) {
                eState = EStates::eSaveB4New;
            } else {
                eState = EStates::eFinished;
            }
        }
            break;
        case eWannaSave:
        {
            // ask if the user wants to save unsaved changes
            const IProjectManagerDialogsPresenter::EResult answer = m_pDialogPresenter.get()->wannaSaveB4New(parent);
            // yes
            if (IProjectManagerDialogsPresenter::EResult::YES == answer) {
                // is the allready a project set to save the changes to?
                if (nullptr != this->getCurrentProject()) {
                    pProject = new Project(this->getCurrentProject()->getName(), this->getCurrentProject()->getProjectDir());
                    eState = EStates::eSaveB4New;
                } else {
                    pProject = new Project();
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
    delete(pProject);
    return EResult::OK;
}



bool ProjectManager::projectSet() const {
    return (!(nullptr == this->getCurrentProject()));
}

bool ProjectManager::allSaved() const {
    return !m_bUnsavedChangesExist;
}

const Project *ProjectManager::getCurrentProject() const
{
    return m_pCurrentProject.get();
}

void ProjectManager::setCurrentProject() {
    // todo: implement
}

