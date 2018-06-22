#include <QApplication>
#include <memory>

#include "model.h"
#include "presenter.h"
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // the unique ptr frees the memory before going out of scope
    std::unique_ptr<MainWindow> pMainWindow(new MainWindow());
    std::unique_ptr<Model> pModel(new Model());
    std::unique_ptr<Presenter> pPresenter(new Presenter(pMainWindow.get(),
                                                        pModel.get()));

    pMainWindow->show();
    return app.exec();
}
