#ifndef COMMANDS_H
#define COMMANDS_H


#include <QUndoCommand>
#include "othertools.h"
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
    deleteNoteCommand(NoteEntity* note, QUndoCommand *parent = 0);
    //! To prevent memory leaks, we have to redefine the destructor
    ~deleteNoteCommand();

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
\class addNoteEntityCommand
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
#endif // COMMANDS_H
