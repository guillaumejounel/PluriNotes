#ifndef COMMANDS_H
#define COMMANDS_H


#include <QUndoCommand>
#include "noteelement.h"

/**
\class deleteNoteCommand
\brief Undo/redo delete note (move to trash)

This class enables the undo/redo process for deleting note (moving them to trash)
**/
class deleteNoteCommand : public QUndoCommand
{
private:
    NoteEntity* note;

public:
    unsigned int type;
    bool first = true;

    deleteNoteCommand(NoteEntity* note, unsigned int type, QUndoCommand *parent = 0);
    //! To prevent memory leaks, we have to redefine the destructor
    ~deleteNoteCommand();

    void undo() override;
    void redo() override;

    NoteEntity* getNote() {return note;}
};




/**
\class deleteNoteCommand
\brief Undo/redo restore note (from trash)

This class enables the undo/redo process for restoring note (moving back from trash)
**/
class restoreNoteCommand : public QUndoCommand
{
private:
    NoteEntity* note;

public:
    restoreNoteCommand(NoteEntity* note, QUndoCommand *parent = 0);
    //! To prevent memory leaks, we have to redefine the destructor
    ~restoreNoteCommand();

    void undo() override;
    void redo() override;

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
    NoteEntity* note;

public:
    addNoteEntityCommand(NoteEntity* note, QUndoCommand *parent = 0);

    //! To prevent memory leaks, we have to redefine the destructor
    ~addNoteEntityCommand();

    void undo() override;
    void redo() override;

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
    addVersionNoteCommand(NoteEntity* note, NoteElement* version, QUndoCommand *parent = 0);

    //! To prevent memory leaks, we have to redefine the destructor
    ~addVersionNoteCommand();

    //! Undo add version method
    void undo() override;

    //! Do/redo add version method
    void redo() override;

    //! \brief getter to the note pointer
    NoteEntity* getNote() {return note;}

    //! \brief getter to the version pointer
    NoteElement* getVersion() {return version;}
};



/**
\class restoreNoteVersionCommand
\brief Undo/redo adding version

This class enables the undo/redo process when creating a version of the note in the app
**/
class restoreNoteVersionCommand : public QUndoCommand
{
private:
    //! \brief pointer to the note parent
    NoteEntity* note;

    //! \brief pointer to the new version
    NoteElement* version;


public:
    restoreNoteVersionCommand(NoteEntity* note, NoteElement* version, QUndoCommand *parent = 0);

    //! To prevent memory leaks, we have to redefine the destructor
    ~restoreNoteVersionCommand();

    //! Undo add version method
    void undo() override;

    //! Do/redo add version method
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
    Relation* relation;

public:
    addRelationCommand(Relation* relation, QUndoCommand *parent = 0);
    // No issues with memory leaks !

    void undo() override;
    void redo() override;

    Relation* getRelation() {return relation;}
};

#endif // COMMANDS_H
