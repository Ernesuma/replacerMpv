#ifndef PROJECT_MANAGER_H
#define PROJECT_MANAGER_H

#include <QDebug>
#include <QObject>
#include <memory>

#include "project.h"
#include "iprojectmanagerdialogspresenter.h"
#include "projectmanagerdialogspresenter.h"

class ProjectManager : public QObject {

    Q_OBJECT

private:
    // member
    std::unique_ptr<Project> m_pCurrentProject{nullptr};
    bool m_bUnsavedChangesExist{false};
    std::unique_ptr<IProjectManagerDialogsPresenter> m_pDialogPresenter;

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
    ProjectManager(QObject* parent = nullptr);
    // destructor
    ~ProjectManager();

    void somethingChanged();

    EResult newProject(QWidget *parent);


    bool projectSet() const;
    bool allSaved() const;

    const Project* getCurrentProject() const;

private:
    void setCurrentProject(std::unique_ptr<Project>& ptr);


signals:
    void currentProjectChanged(const Project project);
};


#endif // PROJECT_MANAGER_H
