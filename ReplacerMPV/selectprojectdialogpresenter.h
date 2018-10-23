#ifndef SELECTPROJECTDIALOGPRESENTER_H
#define SELECTPROJECTDIALOGPRESENTER_H

#include <QObject>
#include <QDialog>
#include <QDir>
#include <memory>
#include <QDebug>
#include <QFileDialog>

#include "messageboxhelper.h"
#include "selectprojectdialog.h"

class SelectProjectDialogPresenter : public QObject
{
    Q_OBJECT

private:
    std::unique_ptr<SelectProjectDialog> m_pSelPrjDlg;
    QString m_name{};
    QString m_path{};

public:
    explicit SelectProjectDialogPresenter(QObject *parentObject = nullptr,
                                          QWidget *parentWidget = nullptr);

    QDialog::DialogCode exec(QString &name, QDir &path);
    QString getName() const;
    QString getPath() const;

    void setName(const QString &name);
    void setPath(const QString &path);

private slots:
    void selProjDlg_toolBtnClicked();
    void selProjDlg_lineEditNameChanged(QString text);
    void selProjDlg_lineEditDirChanged(QString text);
};

#endif // SELECTPROJECTDIALOGPRESENTER_H
