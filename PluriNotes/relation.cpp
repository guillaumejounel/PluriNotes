#include "relation.h"

void Relation::addCouple(const NoteCouple &c){
    content.push_front(c);
}

void Relation::removeCouple(const NoteCouple &c){
    content.removeAll(c);
}
