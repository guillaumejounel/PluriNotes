#include "commands.h"
#include "application.h"
#include <qdebug.h>


deleteNoteCommand::deleteNoteCommand(listItemAndPointer* item, QUndoCommand *parent)
    : QUndoCommand(parent), item(item){}


void deleteNoteCommand::undo()
{
    setText("rétablir la Suppression de la note "+item->getNotePointer()->getId());

    PluriNotes& manager = PluriNotes::getManager();
    manager.moveBackFromTrash(item->getNotePointer());
    manager.addItemToList(item);
}

void deleteNoteCommand::redo()
{
    setText("Suppression de la note "+item->getNotePointer()->getId());

    PluriNotes& manager = PluriNotes::getManager();
    manager.moveToTrash(item->getNotePointer());
    manager.removeItemNoteFromList(item);
}
