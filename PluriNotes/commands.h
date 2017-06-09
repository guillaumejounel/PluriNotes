#ifndef COMMANDS_H
#define COMMANDS_H


#include <QUndoCommand>
#include "othertools.h"

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
    //~deleteNoteCommand();

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
    //~addNoteEntityCommand();

    void undo() override;
    void redo() override;

    NoteEntity* getNote() {return note;}
};
#endif // COMMANDS_H
