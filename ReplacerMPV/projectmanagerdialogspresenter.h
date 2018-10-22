#ifndef PROJECTMANAGERDIALOGSPRESENTER_H
#define PROJECTMANAGERDIALOGSPRESENTER_H

#include <QMessageBox>

#include "iprojectmanagerdialogspresenter.h"
#include "projectManager.h"
#include "messageboxhelper.h"


class ProjectManagerDialogsPresenter : public IProjectManagerDialogsPresenter {

public:
    // constructor
    ProjectManagerDialogsPresenter();

public:
    IProjectManagerDialogsPresenter::EResult wannaSave(QString text) const;
    IProjectManagerDialogsPresenter::EResult wannaSaveB4New() const;

};

#endif // PROJECTMANAGERDIALOGSPRESENTER_H
