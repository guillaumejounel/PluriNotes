#ifndef NOTETEMPLATE_H
#define NOTETEMPLATE_H

#include "noteelement.h"

class NoteElement;

template <class Note>
class BaseNoteType : public NoteElement {
public:
    BaseNoteType() {}
    BaseNoteType(const QString& title, const QDateTime& creaDate) : NoteElement(title,creaDate)  {}
    virtual QString typeName() const override {
        return Note::name();
    }
    static int setTypeInList() {
        return NoteTypeList(Note::name(), Note::newType()).size();
    }
    static int id;
};

template <class Note>
int BaseNoteType<Note>::id = setTypeInList();

#define setNoteType(TypeNote) \
class TypeNote : public BaseNoteType<TypeNote> { \
public:\
int idc { id }; \
static TypeNote* newType() { return new TypeNote; } \
static QString name() { return QString::fromUtf8(#TypeNote); }
#endif // NOTETEMPLATE_H
