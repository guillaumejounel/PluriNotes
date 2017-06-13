#include "commands.h"
#include "application.h"
#include "relationswindows.h"
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
    if (type == 0 || type == 2 || first != true){
        setText("Rétablir la Suppression de la note "+getNote()->getId());

        PluriNotes& manager = PluriNotes::getManager();


        manager.getUi()->noteBox->setCurrentIndex(0);
        manager.moveBackFromTrash(getNote());
        if(getNote()->isArchived() && type!=2){
            getNote()->setArchived(false);
            getNote()->setTrashed(false);
            manager.removeNoteFromList(getNote(), manager.getListArchived() );
        }else{//The note is in the trash
            manager.removeNoteFromList(getNote(), manager.getListTrash());
            getNote()->setTrashed(false);
        }
        //now we have to put the element in the right list (where he was comming from)
        if(type==2){
            manager.addNoteToList(getNote(), manager.getListArchived());
            manager.getUi()->noteBox->setCurrentIndex(2);
            manager.getUi()->mainStackedWidget->setCurrentIndex(4);
            getNote()->setArchived(true);
        }else{
            manager.addNoteToList(getNote(), manager.getListActiveNotes());
            getNote()->setTrashed(false);

            //We have to check if the references are still valid !
            const NoteElement& currentVersion = getNote()->getLastVersion();
            const NoteElement& newVersion = *currentVersion.addVersion();
            bool references = manager.refencesCheck(newVersion.returnReferences(),getNote()->getId());

            if (references == false) {
                manager.saveNewVersion();
                manager.setInteractivity(false);
            }

        }
        //reset
        first = true;
        manager.noteCountUpdate();
    }else{
        first = false;
        redo();
    }

}

void deleteNoteCommand::redo()
{
    if (type == 0 || type == 2 || first != true){
        setText("Suppression de la note "+getNote()->getId());
        PluriNotes& manager = PluriNotes::getManager();
        if (getNote()->isArchived()){
            manager.removeNoteFromList(getNote(), manager.getListArchived());
        }else{
            manager.removeNoteFromList(getNote(), manager.getListActiveNotes());
        }
        if(getNote()->isReferenced() && type!=2 ){
            getNote()->setArchived(true);
            manager.addNoteToList(getNote(), manager.getListArchived());
        }else{
            if (type==2){
                manager.getUi()->noteBox->setCurrentIndex(2);
                manager.getUi()->mainStackedWidget->setCurrentIndex(0);
                getNote()->setArchived(false);
            }
            manager.moveToTrash(getNote());
            manager.addNoteToList(getNote(), manager.getListTrash());
            getNote()->setTrashed(true);

        }
        manager.setDataChanged(true);
        first = true;
        manager.noteCountUpdate();

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
    PluriNotes& manager = PluriNotes::getManager();
    manager.removeReferencesWithOrigin(getNote());
    getNote()->deleteVersion(*getVersion());
    manager.addReferences(getNote(),getNote()->returnReferences());


    manager.selectItemIntoList(manager.findItemInList(getNote(), manager.getListActiveNotes()), manager.getListActiveNotes());
    manager.displayNote();

}

void addVersionNoteCommand::redo() {
    setText("Ajout d'une version à la note : "+getNote()->getId());
    PluriNotes& manager = PluriNotes::getManager();

    manager.removeReferencesWithOrigin(getNote());
    getNote()->addVersion(*getVersion());
    manager.addReferences(getNote(),getNote()->returnReferences());

    manager.displayNote();

    manager.setDataChanged(true);
}

addVersionNoteCommand::~addVersionNoteCommand() {
    if (! getNote()->isVersionInsideNote(*getVersion())) {
        delete getVersion();
    }
}





/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// RElation undo/redo
/////////////////////////////////////////////////////////////////////

// addRelationCommand
// ########################################
addRelationCommand::addRelationCommand(Relation* relation, QUndoCommand *parent )
    : QUndoCommand(parent), relation(relation) {}


void addRelationCommand::undo()
{
    setText("Undo creation of the relation : "+getRelation()->getTitle());
    getRelation()->setDeleted(true);

    PluriNotes& manager = PluriNotes::getManager();
    static_cast<relationsWindows*>(manager.getRelationView())->removeRelationFromList(getRelation());
    static_cast<relationsWindows*>(manager.getRelationView())->displayRelation();
    manager.setDataChanged(true);
}

void addRelationCommand::redo()
{
    setText("Creation of the relation : "+getRelation()->getTitle());
    getRelation()->setDeleted(false);

    PluriNotes& manager = PluriNotes::getManager();
    static_cast<relationsWindows*>(manager.getRelationView())->addRelationToList(getRelation());
    static_cast<relationsWindows*>(manager.getRelationView())->displayRelation();
    manager.setDataChanged(true);
}
// ########################################



// removeRelationCommand
// ########################################
removeRelationCommand::removeRelationCommand(Relation* relation, QUndoCommand *parent )
    : QUndoCommand(parent), relation(relation) {}


void removeRelationCommand::undo()
{
    setText("Undo the delete of the relation : "+getRelation()->getTitle());
    getRelation()->setDeleted(false);

    PluriNotes& manager = PluriNotes::getManager();
    static_cast<relationsWindows*>(manager.getRelationView())->addRelationToList(getRelation());
    static_cast<relationsWindows*>(manager.getRelationView())->displayRelation();
    manager.setDataChanged(true);
}

void removeRelationCommand::redo()
{
    setText("Delete the relation : "+getRelation()->getTitle());
    getRelation()->setDeleted(true);

    PluriNotes& manager = PluriNotes::getManager();
    static_cast<relationsWindows*>(manager.getRelationView())->removeRelationFromList(getRelation());
    static_cast<relationsWindows*>(manager.getRelationView())->displayRelation();
    manager.setDataChanged(true);
}
// ########################################





// addCoupleCommand
// ########################################
addCoupleCommand::addCoupleCommand(Relation* relation, NoteCouple* couple, QUndoCommand *parent )
    : QUndoCommand(parent), relation(relation), couple(couple) {}


addCoupleCommand::~addCoupleCommand() {
    bool canDelete = true;
    for(auto coupleInRel : getRelation()->getContent()){
        if (coupleInRel == getCouple()){
            canDelete = false;
            break;
        }
    }
    if (canDelete) delete getCouple();
}


void addCoupleCommand::undo()
{
    PluriNotes& manager = PluriNotes::getManager();
    relationsWindows* relView = static_cast<relationsWindows*>(manager.getRelationView());
    relView->displayRelation(getRelation());
    setText("Undo adding a couple in the relation : "+getRelation()->getTitle());
    getRelation()->removeCouple(getCouple());
    relView->displayRelation();
}

void addCoupleCommand::redo()
{
    PluriNotes& manager = PluriNotes::getManager();
    relationsWindows* relView = static_cast<relationsWindows*>(manager.getRelationView());
    relView->displayRelation(getRelation());
    setText("Adding a couple in the relation : "+getRelation()->getTitle());
    if (getRelation()->addCouple(getCouple())) {
        relView->addCoupleToList(getCouple());
    }

}
// ########################################
