#include <QApplication>
#include "presenter.h"
#include "mainwindow.h"

static Presenter* pPresenter{NULL};
static MainWindow* pMainWindow{NULL};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    pMainWindow = new MainWindow();
    pPresenter = new Presenter(pMainWindow);

    pMainWindow->show();
    return app.exec();
}
