#include "commands.h"
#include "application.h"
#include <qdebug.h>


deleteNoteCommand::deleteNoteCommand(NoteEntity *note, QUndoCommand *parent)
    : QUndoCommand(parent), note(note){}


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


addNoteEntityCommand::addNoteEntityCommand(NoteEntity* noteEn, listItemAndPointer* item, QUndoCommand *parent )
    : QUndoCommand(parent), noteEn(noteEn), item(item){}


void addNoteEntityCommand::undo()
{
    setText("Annulation de la création de la note :"+noteEn->getId());

    PluriNotes& manager = PluriNotes::getManager();
    manager.removeItemNoteFromList(item);
    //! \todo ajouter contrainte non nullité de item
    //! \todo vérifier fuite mémoire !!!
}

void addNoteEntityCommand::redo()
{
    setText("Création de la note :"+noteEn->getId());
    PluriNotes& manager = PluriNotes::getManager();
    listItemAndPointer* item = manager.addNote(noteEn);
    this->setItem(item);

    manager.setDataChanged(true);
}
