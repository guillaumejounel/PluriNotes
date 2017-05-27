#include "noteelement.h"


const map<QString, NoteElement*>& NoteElement::NoteTypeList(QString typeName, NoteElement* ptNote) {
    static map<QString, NoteElement*> ensTypeNote; //L'ensemble des noms des classes dérivées
    if (ptNote) ensTypeNote.insert(make_pair(typeName, ptNote));
    return ensTypeNote;
}

map<QString, NoteElement*> NoteElement::getTypesNotes() {
    return NoteTypeList("", nullptr);
}
