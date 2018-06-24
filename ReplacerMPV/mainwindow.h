#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // getter
    QString getPlainText() const;

private:
    Ui::MainWindow *ui;

public:
    void setTagMapModel(QAbstractItemModel* pTagMapModel);

signals:
    void pushBtnReplace_clicked();
    void pushBtnC2cPlain_clicked();
    void pushBtnExportFinal_clicked();
    void pushBtnC2cFinal_clicked();
    void pushBtnAddTag_clicked();
    void pushBtnRemoveSelectedTags_clicked();
    void pushBtnRemoveAllTags_clicked();

    void textEditPlain_textChanged();
};

#endif // MAINWINDOW_H
