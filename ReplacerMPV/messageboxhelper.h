#ifndef MESSAGEBOXHELPER_H
#define MESSAGEBOXHELPER_H

#include <QMessageBox>

class MessageBoxHelper
{
private:
    MessageBoxHelper();

public:
    static void infoMsgBox(const QString& info,
                           const QString& info2=QString(),
                           QWidget* parent=nullptr);
    static void warnMsgBox(const QString& info,
                           const QString& info2=QString(),
                           QWidget* parent=nullptr);
    static QMessageBox::StandardButton saveDiscardCancelMsgBox(const QString& info,
                                                               const QString& info2=QString(),
                                                               QWidget* parent=nullptr);
};

#endif // MESSAGEBOXHELPER_H
