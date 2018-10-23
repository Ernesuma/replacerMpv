#include "selectprojectdialogpresenter.h"


SelectProjectDialogPresenter::SelectProjectDialogPresenter(QObject *parentObject, QWidget *parentWidget) :
    QObject(parentObject),
    m_pSelPrjDlg(new SelectProjectDialog(nullptr))
{
    // connect signals to this classes slots
    QObject::connect(m_pSelPrjDlg.get(), SIGNAL(lineEditName_textChanged(QString)),
                     this, SLOT(selProjDlg_lineEditNameChanged(QString)));
    QObject::connect(m_pSelPrjDlg.get(), SIGNAL(lineEditDir_textChanged(QString)),
                     this, SLOT(selProjDlg_lineEditDirChanged(QString)));
    QObject::connect(m_pSelPrjDlg.get(), SIGNAL(toolBtn_clicked()),
                     this, SLOT(selProjDlg_toolBtnClicked()));
}

QDialog::DialogCode SelectProjectDialogPresenter::exec(QString &name, QDir &path)
{
    QDialog::DialogCode answer = static_cast<QDialog::DialogCode> (m_pSelPrjDlg.get()->exec());
    name = this->getName();
    path = QDir(this->getPath());
    return answer;
}

/** getter and setter *
  * ----------------- */
QString SelectProjectDialogPresenter::getName() const {
    return m_name;
}

QString SelectProjectDialogPresenter::getPath() const {
    return m_path;
}

void SelectProjectDialogPresenter::setName(const QString &name) {
    m_name = name;
}

void SelectProjectDialogPresenter::setPath(const QString &path) {
    m_path = path;
}

/** slot implementations *
 *  -------------------- */
void SelectProjectDialogPresenter::selProjDlg_toolBtnClicked()
{
    qDebug() << "toolBtnClicked()";
    QString tmpStr{QFileDialog::getExistingDirectory(this->m_pSelPrjDlg.get()->parentWidget(),
                                                     "Select Directory",
                                                     "Where do you want to save your new project to?")};
    qDebug() << tmpStr;
    m_pSelPrjDlg.get()->setLineEditDirText(tmpStr);
}


void SelectProjectDialogPresenter::selProjDlg_lineEditNameChanged(QString text) {
    qDebug() << "selProjDlg_lineEditNameChanged" << text;
}

void SelectProjectDialogPresenter::selProjDlg_lineEditDirChanged(QString text) {
    qDebug() << "selProjDlg_lineEditDirChanged" << text;
}
