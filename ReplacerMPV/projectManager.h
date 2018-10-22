#ifndef PROJECT_MANAGER_H
#define PROJECT_MANAGER_H

#include <QDebug>
#include <memory>

#include "project.h"
#include "iprojectmanagerdialogspresenter.h"
#include "projectmanagerdialogspresenter.h"

class ProjectManager {
private:
    // member
    Project *m_pCurrentProject{NULL};
    bool m_bUnsavedChangesExist{false};
    std::unique_ptr<IProjectManagerDialogsPresenter> m_dialogPresenter;

public:
    enum EResult {
        OK,
        Yes,
        No,
        Cancel,
        ErrorUnknown,
        ErrorMax
    };

public:
    // constructor
    ProjectManager();
    // destructor
    ~ProjectManager();

    void somethingChanged();

    EResult newProject();


    bool projectSet() const;
    bool allSaved() const;

    const Project* getCurrentProject() const;

private:
    void setCurrentProject();
};


#endif // PROJECT_MANAGER_H
