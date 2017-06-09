#include "commands.h"
#include "application.h"
#include <qdebug.h>


// deleteNoteCommand
// ########################################
deleteNoteCommand::deleteNoteCommand(NoteEntity *note, QUndoCommand *parent)
    : QUndoCommand(parent), note(note){}

/*
deleteNoteCommand::~deleteNoteCommand(){
    delete getNote();
}
*/

void deleteNoteCommand::undo()
{
    setText("Rétablir la Suppression de la note "+getNote()->getId());

    PluriNotes& manager = PluriNotes::getManager();
    manager.moveBackFromTrash(getNote());
    manager.addNoteToList(getNote());
}

void deleteNoteCommand::redo()
{
    setText("Suppression de la note "+getNote()->getId());

    PluriNotes& manager = PluriNotes::getManager();
    manager.moveToTrash(getNote());
    manager.removeNoteFromList(getNote());

    manager.setDataChanged(true);
}
// ########################################



// addNoteEntityCommand
// ########################################
addNoteEntityCommand::addNoteEntityCommand(NoteEntity* note, QUndoCommand *parent )
    : QUndoCommand(parent), note(note) {}

/*
addNoteEntityCommand::~addNoteEntityCommand(){
    delete getNote();
}
*/

void addNoteEntityCommand::undo()
{
    setText("Annulation de la création de la note :"+getNote()->getId());

    PluriNotes& manager = PluriNotes::getManager();
    qWarning()<<QString("je suis dans le undo de add note");
    manager.removeNoteFromList(getNote());
    manager.removeNote(getNote());
}

void addNoteEntityCommand::redo()
{
    setText("Création de la note :"+getNote()->getId());
    PluriNotes& manager = PluriNotes::getManager();
    manager.addNote(note);
    qWarning()<<QString("je suis dans le redo de add note");

    manager.setDataChanged(true);
}
