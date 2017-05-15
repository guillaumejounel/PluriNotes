#include "plurinotes.h"
#include "notes.h"
#include <QApplication>

NotesManager NotesManager::instanceUnique;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PluriNotes w;
    w.show();

    return a.exec();
}
