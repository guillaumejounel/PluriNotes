#ifndef COMMANDS_H
#define COMMANDS_H


#include <QUndoCommand>
#include <noteentity.h>


class deleteNoteCommand : public QUndoCommand
{
private:
    NoteEntity* note;

public:
    deleteNoteCommand(NoteEntity* note, QUndoCommand *parent = 0);

    void undo() override;
    void redo() override;
};

#endif // COMMANDS_H
