#include "commands.h"
#include "application.h"
#include <qdebug.h>


// deleteNoteCommand
// ########################################
deleteNoteCommand::deleteNoteCommand(NoteEntity *note, QUndoCommand *parent)
    : QUndoCommand(parent), note(note){}


deleteNoteCommand::~deleteNoteCommand(){
    PluriNotes& manager = PluriNotes::getManager();
    // if we don't actually still have the pointer in the vector we shoult be able to delete it...
    if (! manager.isInsideApp(getNote())) {
        qWarning()<<QString("je suis dans le destructeur et je ne fais rien !");
        delete getNote();
    }
    qWarning()<<QString("je sors du destructeur");

}


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


addNoteEntityCommand::~addNoteEntityCommand(){
    PluriNotes& manager = PluriNotes::getManager();
    // if we don't actually still have the pointer in the vector we shoult be able to delete it...
    if (! manager.isInsideApp(getNote())) {
        delete getNote();
    }
}


void addNoteEntityCommand::undo()
{
    setText("Annulation de la création de la note :"+getNote()->getId());

    PluriNotes& manager = PluriNotes::getManager();
    manager.removeNoteFromList(getNote());
    manager.removeNote(getNote());
}

void addNoteEntityCommand::redo()
{
    setText("Création de la note :"+getNote()->getId());
    PluriNotes& manager = PluriNotes::getManager();
    manager.addNote(note);

    manager.setDataChanged(true);
}
// ########################################



// addNoteEntityCommand
// ########################################
addVersionNoteCommand::addVersionNoteCommand(NoteEntity* note, NoteElement* version, QUndoCommand *parent)
    : note(note), version(version) {}

void addVersionNoteCommand::undo()
{
    setText("Annulation de l'ajout d'une version à la note : "+getNote()->getId());

    // We remove the version from the noteentity
    getNote()->deleteVersion(*getVersion());

    PluriNotes& manager = PluriNotes::getManager();
    manager.displayNote();

}

void addVersionNoteCommand::redo(){
    setText("Ajout d'une version à la note : "+getNote()->getId());

    getNote()->addVersion(*getVersion());

    PluriNotes& manager = PluriNotes::getManager();

    //! \todo setter !
    //manager.ui->idDisplayLineEdit->setText(currentSelectedNote.getId());
    manager.displayNote();

    manager.setDataChanged(true);
}

addVersionNoteCommand::~addVersionNoteCommand(){
    if (! getNote()->isVersionInsideNote(*getVersion())) {
        delete getVersion();
    }
}
