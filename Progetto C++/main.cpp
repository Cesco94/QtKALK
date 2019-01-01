#include "view.h"
#include "model.h"
#include "controller.h"
#include<QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    View myView;
    Model myModel;
    Controller myController(&myModel);
    myView.setController(&myController);
    myView.show();

    return app.exec();
}
