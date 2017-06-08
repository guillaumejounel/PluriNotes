#include "relation.h"
#include "notecouple.h"

bool Relation::isInside(NoteEntity* note1, NoteEntity* note2){
    QString tmp = "tmp";
    NoteCouple nCouple1 = NoteCouple(tmp,note1,note2);
    NoteCouple nCouple2 = NoteCouple(tmp,note2,note1);

    unsigned int size = content.size();

    for (unsigned int i = 0;i<size;i++){
        if ( content[i]==nCouple1 ) return true;
    }

    if (this->isOriented() == false){
        for (unsigned int i = 0;i<size;i++){
            if ( content[i]==nCouple2 ) return true;
        }
    }

    return false;
}


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
