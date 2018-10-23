#include "selectprojectdialog.h"
#include "ui_selectprojectdialog.h"

SelectProjectDialog::SelectProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectProjectDialog)
{
    ui->setupUi(this);

    QObject::connect(ui.get()->lineEdit_name, SIGNAL(textChanged(QString)),
                     this, SIGNAL(lineEditName_textChanged(QString)));
    QObject::connect(ui.get()->lineEdit_dir, SIGNAL(textChanged(QString)),
                     this, SIGNAL(lineEditDir_textChanged(QString)));
    QObject::connect(ui.get()->toolButton, SIGNAL(clicked(bool)),
                     this, SIGNAL(toolBtn_clicked()));
}

SelectProjectDialog::~SelectProjectDialog() {
}

void SelectProjectDialog::setLineEditDirText(const QString &text) {
    ui.get()->lineEdit_dir->setText(text);
}
