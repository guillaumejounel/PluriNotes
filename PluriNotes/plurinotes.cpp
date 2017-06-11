#include "notes.h"
#include "application.h"
#include "relationswindows.h"
#include <QApplication>
#include <QDebug>

PluriNotes* PluriNotes::instanceUnique;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    PluriNotes& w = PluriNotes::getManager();
    //Load data from UML
    w.load();

    //! test functionnalities
    w.testFunction();

    //! Load data into UI
    w.loadDataIntoUi();

    w.show();
    return a.exec();
}
