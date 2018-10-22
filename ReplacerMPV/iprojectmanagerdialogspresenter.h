#ifndef IPROJECTMANAGERDIALOGSPRESENTER_H
#define IPROJECTMANAGERDIALOGSPRESENTER_H

#include<QString>

class IProjectManagerDialogsPresenter {
public:

    enum EResult {
        YES,
        NO,
        CANCEL,
        ERROR
    };

    virtual EResult wannaSave(QString text) const = 0;
    virtual EResult wannaSaveB4New() const = 0;
};

#endif // IPROJECTMANAGERDIALOGSPRESENTER_H
