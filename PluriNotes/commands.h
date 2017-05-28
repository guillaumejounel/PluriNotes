#ifndef COMMANDS_H
#define COMMANDS_H


#include <QUndoCommand>
#include "othertools.h"

class deleteNoteCommand : public QUndoCommand
{
private:
    listItemAndPointer* item;

public:
    deleteNoteCommand(listItemAndPointer* item, QUndoCommand *parent = 0);

    void undo() override;
    void redo() override;
};

#endif // COMMANDS_H
