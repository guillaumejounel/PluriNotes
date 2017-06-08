#include "relation.h"

void Relation::addCouple(const NoteCouple &c){
    content.push_front(c);
}

void Relation::removeCouple(const NoteCouple &c){
    content.removeAll(c);
}


QSet<NoteEntity*> Relation::successorsOf(NoteEntity* note) const{
    QSet<NoteEntity*> result;
    unsigned int size = content.size();
    NoteEntity* successor;

    for (unsigned int i = 0;i<size;i++){
        successor = content[i].successor(note);
        if ( successor != nullptr) result.insert(successor);
    }

    return result;
}


QSet<NoteEntity*> Relation::predecessorsOf(NoteEntity* note) const{
    QSet<NoteEntity*> result;
    unsigned int size = content.size();
    NoteEntity* predecessor;

    for (unsigned int i = 0;i<size;i++){
        predecessor = content[i].predecessor(note);
        if ( predecessor != nullptr) result.insert(predecessor);
    }

    return result;
}
