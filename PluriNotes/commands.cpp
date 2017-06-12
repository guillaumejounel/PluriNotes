#include "commands.h"
#include "application.h"
#include <qdebug.h>


// deleteNoteCommand
// ########################################
deleteNoteCommand::deleteNoteCommand(NoteEntity *note, unsigned int type, QUndoCommand *parent)
    : QUndoCommand(parent), note(note), type(type) {}


deleteNoteCommand::~deleteNoteCommand() {
    PluriNotes& manager = PluriNotes::getManager();
    // if we don't actually still have the pointer in the vector we should be able to delete it...
    if (! manager.isInsideApp(getNote())) {
        delete getNote();
    }

}


void deleteNoteCommand::undo()
{
    if (type == 0 || first != true){
        setText("Rétablir la Suppression de la note "+getNote()->getId());

        PluriNotes& manager = PluriNotes::getManager();
        manager.getUi()->toolBox->setCurrentIndex(0);
        manager.moveBackFromTrash(getNote());
        manager.removeNoteFromList(getNote(), manager.getListTrash());
        manager.addNoteToList(getNote(), manager.getListActiveNotes());
        //reset
        first = true;
    }else{
        first = false;
        redo();
    }

}

void deleteNoteCommand::redo()
{
    if (type == 0 || first != true){
        setText("Suppression de la note "+getNote()->getId());

        PluriNotes& manager = PluriNotes::getManager();
        manager.moveToTrash(getNote());
        manager.removeNoteFromList(getNote(), manager.getListActiveNotes());
        manager.addNoteToList(getNote(), manager.getListTrash());

        manager.setDataChanged(true);
        first = true;
    } else {
        first = false;
        undo();
    }
}
// ########################################




// addNoteEntityCommand
// ########################################
addNoteEntityCommand::addNoteEntityCommand(NoteEntity* note, QUndoCommand *parent )
    : QUndoCommand(parent), note(note) {}


addNoteEntityCommand::~addNoteEntityCommand() {
    PluriNotes& manager = PluriNotes::getManager();
    // if we don't actually still have the pointer in the vector we shoult be able to delete it...
    if (! manager.isInsideApp(getNote())) {
        delete getNote();
    }
}


void addNoteEntityCommand::undo()
{
    setText("Undo creation of the note : "+getNote()->getId());

    PluriNotes& manager = PluriNotes::getManager();
    manager.removeNoteFromList(getNote(), manager.getListActiveNotes());
    manager.getReferencesRelation()->removeCoupleWithNote(getNote());
    qWarning()<<QString("c'est passé");
    manager.removeNote(getNote());
}

void addNoteEntityCommand::redo()
{
    setText("Creation of the note :"+getNote()->getId());
    PluriNotes& manager = PluriNotes::getManager();
    manager.addNote(*note, manager.getListActiveNotes());
    QStringList listOfRefenreces = note->returnReferences();
    if (!listOfRefenreces.isEmpty()) manager.addReferences(getNote(),listOfRefenreces);
    manager.updateTrees(getNote());

    manager.setDataChanged(true);
}
// ########################################



// addVersionNoteCommand
// ########################################
addVersionNoteCommand::addVersionNoteCommand(NoteEntity* note, NoteElement* version, QUndoCommand *parent)
    : note(note), version(version) {}

void addVersionNoteCommand::undo()
{
    setText("Annulation de l'ajout d'une version à la note : "+getNote()->getId());

    // We remove the version from the noteentity
    getNote()->deleteVersion(*getVersion());

    PluriNotes& manager = PluriNotes::getManager();
    manager.selectItemIntoList(manager.findItemInList(getNote(), manager.getListActiveNotes()), manager.getListActiveNotes());
    manager.displayNote();

}

void addVersionNoteCommand::redo() {
    setText("Ajout d'une version à la note : "+getNote()->getId());

    getNote()->addVersion(*getVersion());

    PluriNotes& manager = PluriNotes::getManager();
    manager.displayNote();

    manager.setDataChanged(true);
}

addVersionNoteCommand::~addVersionNoteCommand() {
    if (! getNote()->isVersionInsideNote(*getVersion())) {
        delete getVersion();
    }
}

