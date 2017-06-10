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

    w.show();


    return a.exec();
}
