#ifndef PROJECTMANAGERDIALOGSPRESENTER_H
#define PROJECTMANAGERDIALOGSPRESENTER_H

#include <QMessageBox>
#include <QDebug>

#include "iprojectmanagerdialogspresenter.h"
#include "messageboxhelper.h"
#include "selectprojectdialogpresenter.h"
#include "project.h"


class ProjectManagerDialogsPresenter : public IProjectManagerDialogsPresenter {

public:
    // constructor
    ProjectManagerDialogsPresenter();

public:
    IProjectManagerDialogsPresenter::EResult wannaSave(QString text, QWidget* parent=nullptr) const;
    IProjectManagerDialogsPresenter::EResult wannaSaveB4New(QWidget* parent=nullptr) const;

    IProjectManagerDialogsPresenter::EResult selectProject(Project &project, QWidget* parent=nullptr) const;

};

#endif // PROJECTMANAGERDIALOGSPRESENTER_H
