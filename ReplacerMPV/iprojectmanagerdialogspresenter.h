#ifndef IPROJECTMANAGERDIALOGSPRESENTER_H
#define IPROJECTMANAGERDIALOGSPRESENTER_H

#include<QString>

#include "project.h"

class IProjectManagerDialogsPresenter {

public:

    enum EResult {
        OK,
        YES,
        NO,
        CANCEL,
        ERROR
    };

    virtual EResult wannaSave(QString text, QWidget* parent = nullptr) const = 0;
    virtual EResult wannaSaveB4New(QWidget* parent = nullptr) const = 0;
    virtual EResult selectProject(Project &project, QWidget* parent = nullptr) const = 0;
};

#endif // IPROJECTMANAGERDIALOGSPRESENTER_H
