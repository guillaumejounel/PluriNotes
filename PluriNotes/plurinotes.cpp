#include "notes.h"
#include "application.h"
#include <QApplication>

PluriNotes* PluriNotes::instanceUnique;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PluriNotes& w = PluriNotes::getManager();
    w.show();
    return a.exec();
}
