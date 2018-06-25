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
    QString getNewTag() const;
    QString getNewTagValue() const;

    // setter
    void setTagMapModel(QAbstractItemModel* pTagMapModel);
    void setFinalText(const QString& text);
    void clearAddTagLineEdits();
    void focusAddTagLineEdit();

    void enableC2CPlainBtn(bool bEnable);

private:
    Ui::MainWindow *ui;

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
