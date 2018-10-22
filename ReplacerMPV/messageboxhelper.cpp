#include "messageboxhelper.h"

MessageBoxHelper::MessageBoxHelper()
{

}

void MessageBoxHelper::infoMsgBox(const QString &info, const QString &info2, QWidget *parent)
{
    QMessageBox msgBox(parent);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText(info);
    msgBox.setInformativeText(info2);
    msgBox.exec();
}

void MessageBoxHelper::warnMsgBox(const QString &info, const QString &info2, QWidget *parent)
{
    QMessageBox mBox(parent);
    mBox.setIcon(QMessageBox::Warning);
    mBox.setText(info);
    mBox.setInformativeText(info2);
    mBox.exec();
}

QMessageBox::StandardButton MessageBoxHelper::saveDiscardCancelMsgBox(const QString &info, const QString &info2, QWidget *parent)
{
    QMessageBox mBox(parent);
    mBox.setIcon(QMessageBox::Question);
    mBox.setText(info);
    mBox.setInformativeText(info2);
    mBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    mBox.setDefaultButton(QMessageBox::Save);
    return static_cast<QMessageBox::StandardButton>(mBox.exec());
}
