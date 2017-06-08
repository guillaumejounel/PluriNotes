#include "notecouple.h"

bool NoteCouple::isEqualX(const NoteEntity* note) const{
    if (note == x || note->getId() == x->getId()) return true;
    return false;
}

bool NoteCouple::isEqualY(const NoteEntity* note) const{
    if (note == y || note->getId() == y->getId()) return true;
    return false;
}


bool NoteCouple::operator==(const NoteCouple& c)const{
    if (isEqualX(c.getX()) && isEqualY(c.getY())) return true;

    if (c.isOriented() == false || oriented == false){
        if (isEqualY(c.getX()) && isEqualX(c.getY())) return true;
    }
    return false;
}


NoteEntity* NoteCouple::successor(NoteEntity* note) const{
    if (isEqualX(note)) return y;

    if (oriented == false && isEqualY(note)) return x;
    return nullptr;
}


NoteEntity* NoteCouple::predecessor(NoteEntity* note) const{
    if (isEqualY(note)) return x;

    if (oriented == false && isEqualX(note)) return y;
    return nullptr;
}
