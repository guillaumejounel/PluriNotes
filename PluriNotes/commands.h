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


class addNoteEntityCommand : public QUndoCommand
{
private:
    NoteEntity* noteEn;
    listItemAndPointer* item;
public:
    addNoteEntityCommand(NoteEntity* noteEn, listItemAndPointer* item = nullptr, QUndoCommand *parent = 0);

    void undo() override;
    void redo() override;

    void setItem(listItemAndPointer* it) {item=it;}
};
#endif // COMMANDS_H
