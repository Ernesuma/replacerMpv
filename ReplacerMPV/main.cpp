#include <QApplication>
#include <memory>

#include "presenter.h"
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // the unique ptr frees the memory before going out of scope
    std::unique_ptr<MainWindow> pMainWindow(new MainWindow());
    std::unique_ptr<Presenter> pPresenter(new Presenter(pMainWindow.get()));

    pMainWindow->show();
    return app.exec();
}
