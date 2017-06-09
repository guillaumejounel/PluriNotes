#include "commands.h"
#include "application.h"
#include <qdebug.h>


deleteNoteCommand::deleteNoteCommand(listItemAndPointer* item, QUndoCommand *parent)
    : QUndoCommand(parent), item(item){}


void deleteNoteCommand::undo()
{
    setText("Rétablir la Suppression de la note "+item->getNotePointer()->getId());

    PluriNotes& manager = PluriNotes::getManager();
    manager.moveBackFromTrash(item->getNotePointer());
    manager.addItemNoteToList(item);

}

void deleteNoteCommand::redo()
{
    setText("Suppression de la note "+item->getNotePointer()->getId());

    PluriNotes& manager = PluriNotes::getManager();
    manager.moveToTrash(item->getNotePointer());
    manager.removeItemNoteFromList(item);

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
