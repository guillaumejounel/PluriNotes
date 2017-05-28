#include "commands.h"
#include "application.h"
#include <qdebug.h>


deleteNoteCommand::deleteNoteCommand(listItemAndPointer* item, QUndoCommand *parent)
    : QUndoCommand(parent), item(item){}


void deleteNoteCommand::undo()
{
    setText(QObject::tr("rétablir la Suppression de la note"));

    PluriNotes& manager = PluriNotes::getManager();
    manager.moveBackFromTrash(item->getNotePointer());
    manager.addItemToList(item);
}

void deleteNoteCommand::redo()
{
    setText(QObject::tr("Suppression de la note"));

    PluriNotes& manager = PluriNotes::getManager();
    manager.moveToTrash(item->getNotePointer());
    manager.removeItemNoteFromList(item);
}
