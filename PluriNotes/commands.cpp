#include "commands.h"
#include "application.h"
#include <qdebug.h>

deleteNoteCommand::deleteNoteCommand(NoteEntity* note, QUndoCommand *parent) : QUndoCommand(parent), note(note){}


void deleteNoteCommand::undo()
{ std::cout<<"annuler suppression";}

void deleteNoteCommand::redo()
{

    std::cout<<"suppression de la note";

    /*
    PluriNotes manager = PluriNotes::getManager();

    unsigned int i = 0;
    for (auto note: notes) {
        if (note==currentSelectedNote) {
            manager.notes.erase(notes.begin()+i);
            manager.corbeille.push_back(currentSelectedNote);
            break;
        }
        ++i;
    }
    */
}
