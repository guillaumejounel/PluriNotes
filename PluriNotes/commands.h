/**
\file application.h
\date 14/06/2017
\author Florent Chehab, Guillaume Jounel and Félix Boisselier
\brief contains the different classes related to the undo/redo process
**/


#ifndef COMMANDS_H
#define COMMANDS_H


#include <QUndoCommand>
#include "noteelement.h"

/**
\class deleteNoteCommand
\brief Undo/redo delete note (move to trash or archived)

This class enables the undo/redo process for deleting note (moving them to the trash or the archives)
**/
class deleteNoteCommand : public QUndoCommand
{
private:
    //! \brief Pointer to the note we are dealing with
    NoteEntity* note;

    //! This class is used for different types of delete...
    //! if type == 0 it is the classic behaviour when we want to delete an active note
    //! if type == 1 then we are dealing with redo command equivalent to restoring
    //!     a note from the trash of archives
    //! if type == 2  it is when we want to move an element from the archive section to the trash (if we can)
    //! \brief type of deletion
    unsigned int type;

    //! A simple boolean for when type == 1 and we want to "invert" the command (only once)
    //! \brief boolean to store the number of iteration inside the class
    bool first = true;

public:
    //! \brief Classic constructor for the command
    //! @param note the note
    //! @param type the type of command
    //! @param parent Parent command
    deleteNoteCommand(NoteEntity* note, unsigned int type, QUndoCommand *parent = 0);

    //! \brief destructor of the class
    //! To prevent memory leaks, we have to redefine the destructor
    ~deleteNoteCommand();

    //! This is the standard method of the class QUndoCommand
    //! It is executed when undoing a command
    //! \brief undo method
    void undo() override;

    //! This is the standard method of the class QUndoCommand
    //! It is executed when creating pushing the command in the stack or redoing after an undo
    //! \brief redo method
    void redo() override;

    //! \brief Accessor to the note
    NoteEntity* getNote() {return note;}

    //! \brief Accessor to the type of command
    unsigned int getType() const {return type;}

    //! \brief Getter to the "first" attributes
    bool getFirst() const {return first;}

    //! \brief Setter for the first attribute
    void setFirst(bool b) {first = b;}
};




/**
\class restoreNoteCommand
\brief Undo/redo restore note (from trash)

This class enables the undo/redo process for restoring note (moving back from trash)
**/
class restoreNoteCommand : public QUndoCommand
{
private:
    //! \brief Pointer to the note we are dealing with
    NoteEntity* note;

public:
    //! Classic constructor for the command
    //! @param note the note
    //! @param parent Parent command
    restoreNoteCommand(NoteEntity* note, QUndoCommand *parent = 0);

    //! To prevent memory leaks, we have to redefine the destructor
    //! \brief destructor of the class
    ~restoreNoteCommand();

    //! This is the standard method of the class QUndoCommand
    //! It is executed when creating pushing the command in the stack or redoing after an undo
    //! \brief undo method
    void undo() override;

    //! This is the standard method of the class QUndoCommand
    //! It is executed when creating pushing the command in the stack or redoing after an undo
    //! \brief redo method
    void redo() override;

    //! \brief Accessor to the note
    NoteEntity* getNote() {return note;}
};


/**
\class addNoteEntityCommand
\brief Undo/redo adding note

This class enables the undo/redo process for adding a note in the app
**/
class addNoteEntityCommand : public QUndoCommand
{
private:
    //! \brief Pointer to the note we are dealing with
    NoteEntity* note;

public:
    //! \brief Classic constructor for the command
    //! @param note the note
    //! @param parent Parent command
    addNoteEntityCommand(NoteEntity* note, QUndoCommand *parent = 0);

    //! \brief destructor for the class
    //! To prevent memory leaks, we have to redefine the destructor
    ~addNoteEntityCommand();

    //! This is the standard method of the class QUndoCommand
    //! It is executed when creating pushing the command in the stack or redoing after an undo
    //! \brief undo method
    void undo() override;

    //! This is the standard method of the class QUndoCommand
    //! It is executed when creating pushing the command in the stack or redoing after an undo
    //! \brief redo method
    void redo() override;

    //! \brief Accessor to the note
    NoteEntity* getNote() {return note;}
};



/**
\class addVersionNoteCommand
\brief Undo/redo adding version

This class enables the undo/redo process when creating a version of the note in the app
**/
class addVersionNoteCommand : public QUndoCommand
{
private:
    //! \brief pointer to the note parent
    NoteEntity* note;

    //! \brief pointer to the new version
    NoteElement* version;

public:
    //! \brief Classic constructor of the class
    //! @param note the note
    //! @param version the version
    //! @param parent Parent command
    addVersionNoteCommand(NoteEntity* note, NoteElement* version, QUndoCommand *parent = 0);

    //! To prevent memory leaks, we have to redefine the destructor
    //! \brief destructor of the class
    ~addVersionNoteCommand();

    //! This is the standard method of the class QUndoCommand
    //! It is executed when creating pushing the command in the stack or redoing after an undo
    //! \brief undo method
    void undo() override;

    //! This is the standard method of the class QUndoCommand
    //! It is executed when creating pushing the command in the stack or redoing after an undo
    //! \brief redo method
    void redo() override;

    //! \brief getter to the note pointer
    NoteEntity* getNote() {return note;}

    //! \brief getter to the version pointer
    NoteElement* getVersion() {return version;}
};



/**
\class restoreNoteVersionCommand
\brief Undo/redo restoring a version in the app

This class enables the undo/redo process when restoring a version of the note in the app
**/
class restoreNoteVersionCommand : public QUndoCommand
{
private:
    //! \brief pointer to the note parent
    NoteEntity* note;

    //! \brief pointer to the new version
    NoteElement* version;


public:
    //! \brief Classic constructor of the class
    //! @param note the note
    //! @param version the version
    //! @param parent Parent command
    restoreNoteVersionCommand(NoteEntity* note, NoteElement* version, QUndoCommand *parent = 0);

    //! To prevent memory leaks, we have to redefine the destructor
    //! \brief destructor of the class
    ~restoreNoteVersionCommand();

    //! This is the standard method of the class QUndoCommand
    //! It is executed when creating pushing the command in the stack or redoing after an undo
    //! \brief undo method
    void undo() override;

    //! This is the standard method of the class QUndoCommand
    //! It is executed when creating pushing the command in the stack or redoing after an undo
    //! \brief redo method
    void redo() override;

    //! \brief getter to the note pointer
    NoteEntity* getNote() {return note;}

    //! \brief getter to the version pointer
    NoteElement* getVersion() {return version;}
};



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////////////////////
/// RElations undo/redo stuff

/**
\class addRelationCommand
\brief Undo/redo adding relation

This class enables the undo/redo process for adding a relation in the app
**/
class addRelationCommand : public QUndoCommand
{
private:
    //! \brief pointer to the relation concerned by the process
    Relation* relation;

public:
    //! Classic constructor for the command
    //! \brief constructor of the class
    //! @param relation the relation
    //! @param parent the parent command
    addRelationCommand(Relation* relation, QUndoCommand *parent = 0);
    // No issues with memory leaks !

    //! This is the standard method of the class QUndoCommand
    //! It is executed when creating pushing the command in the stack or redoing after an undo
    //! \brief undo method
    void undo() override;

    //! This is the standard method of the class QUndoCommand
    //! It is executed when creating pushing the command in the stack or redoing after an undo
    //! \brief redo method
    void redo() override;

    //! \brief getter for the relation stored
    Relation* getRelation() {return relation;}
};



/**
\class removeRelationCommand
\brief Undo/redo removing relation

This class enables the undo/redo process for removing a relation in the app
**/
class removeRelationCommand : public QUndoCommand
{
private:
    //! \brief pointer to the relation concerned by the process
    Relation* relation;

public:
    //! \brief Classic constructor for the command
    //! @param relation the relation
    //! @param parent the parent command
    removeRelationCommand(Relation* relation, QUndoCommand *parent = 0);
    // No issues with memory leaks ! no need for a specific destructor

    //! This is the standard method of the class QUndoCommand
    //! It is executed when creating pushing the command in the stack or redoing after an undo
    //! \brief undo method
    void undo() override;

    //! This is the standard method of the class QUndoCommand
    //! It is executed when creating pushing the command in the stack or redoing after an undo
    //! \brief redo method
    void redo() override;

    //! \brief getter for the relation stored
    Relation* getRelation() {return relation;}
};


/**
\class addCoupleCommand
\brief Undo/redo adding couple in relation

This class enables the undo/redo process for adding a couple in a relation
**/
class addCoupleCommand : public QUndoCommand
{
private:
    //! \brief pointer to the relation concerned by the process
    Relation* relation;

    //! \brief pointer to the couple concerned by the process
    NoteCouple* couple;

public:
    //! \brief Classic constructor for the command
    //! @param relation the relation
    //! @param couple the note couple
    //! @param parent the parent command
    addCoupleCommand(Relation* relation, NoteCouple* couple, QUndoCommand *parent = 0);

    //! \brief Destructor for the class
    //! For managinf memory leaks
    ~addCoupleCommand();

    //! This is the standard method of the class QUndoCommand
    //! It is executed when creating pushing the command in the stack or redoing after an undo
    //! \brief undo method
    void undo() override;

    //! This is the standard method of the class QUndoCommand
    //! It is executed when creating pushing the command in the stack or redoing after an undo
    //! \brief redo method
    void redo() override;

    //! \brief pointer to the relation concerned by the process
    Relation* getRelation() {return relation;}

    //! \brief pointer to the couple concerned by the process
    NoteCouple* getCouple() {return couple;}
};


#endif // COMMANDS_H
