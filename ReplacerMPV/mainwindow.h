#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QAbstractItemModel>
#include<QItemSelectionModel>
#include<QMenu>
#include<QAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    // member
    // ------
    // pointer to the autogenerated ui
    Ui::MainWindow *ui{nullptr};

    // pointer to the menu parts
    QMenu *m_menuMenu{nullptr};
    QMenu *m_menuData{nullptr};
    QMenu *m_menuHelp{nullptr};

    QAction *m_actionSave{nullptr};
    QAction *m_actionExportPlain{nullptr};
    QAction *m_actionExportFinal{nullptr};
    QAction *m_actionExportTagList{nullptr};

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // getter
    QString getPlainText() const;
    QString getNewTag() const;
    QString getNewTagValue() const;
    const QItemSelectionModel *getTagMapSelection();

    // setter
    void setTagMapModel(QAbstractItemModel* pTagMapModel);
    void setFinalText(const QString& text);
    void clearAddTagLineEdits();
    void focusAddTagLineEdit();

    void enableC2CPlainBtn(const bool bEnable);
    void enableC2CFinalBtn(const bool bEnable);
    void enableExportFinalBtn(const bool bEnable);
    void enableRemoveSelTagsBtn(const bool bEnable);
    void enableRemoveAllTagsBtn(const bool bEnable);

private:
    void createMenus();


signals:
    void pushBtnReplace_clicked();
    void pushBtnC2cPlain_clicked();
    void pushBtnExportFinal_clicked();
    void pushBtnC2cFinal_clicked();
    void pushBtnAddTag_clicked();
    void pushBtnRemoveSelectedTags_clicked();
    void pushBtnRemoveAllTags_clicked();

    void textEditPlain_textChanged();

    void menuExit();
};

#endif // MAINWINDOW_H
