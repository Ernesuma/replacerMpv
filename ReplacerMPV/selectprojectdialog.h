#ifndef SELECTPROJECTDIALOG_H
#define SELECTPROJECTDIALOG_H

#include <QDialog>
#include <memory>

namespace Ui {
class SelectProjectDialog;
}

class SelectProjectDialog : public QDialog
{
    Q_OBJECT

private:
    // member
    std::unique_ptr<Ui::SelectProjectDialog> ui;

public:
    explicit SelectProjectDialog(QWidget* parent = 0);
    ~SelectProjectDialog();

    void setLineEditDirText(const QString& text);

signals:
    void lineEditName_textChanged(QString);
    void lineEditDir_textChanged(QString);
    void toolBtn_clicked();
};

#endif // SELECTPROJECTDIALOG_H
