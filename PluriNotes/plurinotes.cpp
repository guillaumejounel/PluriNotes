#include "application.h"
#include "relationswindows.h"
#include <QApplication>
#include <QDebug>

PluriNotes* PluriNotes::instanceUnique;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    PluriNotes& manager = PluriNotes::getManager();
    //Load data from UML
    manager.load();

    //! test functionnalities
    manager.testFunction();

    //! Load data into UI
    manager.loadDataIntoUi();

    manager.show();
    return a.exec();
}
