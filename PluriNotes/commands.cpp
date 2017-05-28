#include "commands.h"
#include "application.h"
#include <qdebug.h>


deleteNoteCommand::deleteNoteCommand(NoteEntity* note, QUndoCommand *parent)
    : QUndoCommand(parent), note(note){}


void deleteNoteCommand::undo()
{
    setText(QObject::tr("rétablir la Suppression de la note"));

    PluriNotes& manager = PluriNotes::getManager();
    manager.moveBackFromTrash(note);
}

void deleteNoteCommand::redo()
{
    setText(QObject::tr("Suppression de la note"));

    PluriNotes& manager = PluriNotes::getManager();
    manager.moveToTrash(note);
}
