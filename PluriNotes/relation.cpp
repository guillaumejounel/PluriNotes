#include "relation.h"
#include "notecouple.h"
#include "application.h"

Relation::Relation(QString &t, QString &d, bool isOriented, bool isReferences) : title(t), description(d), oriented(isOriented), references(isReferences), number(0)
{}

Relation::Relation(QString &t, QString &d, bool isOriented) : title(t), description(d), oriented(isOriented), references(false)
{
    PluriNotes& manager = PluriNotes::getManager();
    number = manager.getMaxRelationId();
    if (number != 0) number++;
}

Relation::~Relation(){
    for (auto couple : content){
        delete couple;
    }

    for (auto couple : deletedTMP){
        delete couple;
    }
}

bool Relation::isInside(const NoteCouple* c) const {
    return isInside(c->getX(),c->getY());
}

bool Relation::isInside(NoteEntity* note1, NoteEntity* note2) const {
    QString tmp = "tmp";
    NoteCouple nCouple1 = NoteCouple(tmp,note1,note2);
    NoteCouple nCouple2 = NoteCouple(tmp,note2,note1);

    unsigned int size = content.size();

    for (unsigned int i = 0;i<size;i++) {
        if ( *content[i]==nCouple1 ) return true;
    }

    if (this->isOriented() == false) {
        for (unsigned int i = 0;i<size;i++) {
            if ( *content[i]==nCouple2 ) return true;
        }
    }

    return false;
}

bool Relation::isInside(NoteEntity* note) const{
    for (auto couple : content){
        if (couple->contains(note)) return true;
    }
    return false;
}


bool Relation::addCouple(const NoteCouple* c) {
    //Check if the couple isn't already inside
    if ( isInside(c) ) return false;
    content.push_front(const_cast<NoteCouple*>(c));
    return true;
}

void Relation::removeCouple(const NoteCouple*c) {
     for (auto couple : content){
        if (couple == c){
            // We duplicate the couple
            //NoteCouple* tmp = new NoteCouple(*couple);
            //coupleAndRelation output = coupleAndRelation(tmp,this);

            content.removeAll(const_cast<NoteCouple*>(c));
            //delete c;
            break;
        }
    }
}

void Relation::removeCouple(const QList<NoteCouple*> coupleList){

    for (auto couple : coupleList){
        removeCouple(couple);
    }
}


void Relation::removeCoupleWithNote(const NoteEntity* note){
     for (auto couple : content){
        if (couple->contains(note)) {
            //output.append(coupleAndRelation(new NoteCouple(*couple),this));
            content.removeAll(couple);
            delete couple;
        }
    }
    //return output;
}

void Relation::removeCoupleWithNotePredecessor(const NoteEntity* note){
    //only for oriented !
    for (auto couple : content){
       if (couple->isEqualX(note)) {
           //output.append(coupleAndRelation(new NoteCouple(*couple),this));
           content.removeAll(couple);
           delete couple;
       }
   }
}



void Relation::removeCoupleWithNote(const QList<NoteEntity*> noteList){
    //QList<coupleAndRelation> output;
    for (auto note : noteList){
        removeCoupleWithNote(note);
    }

    //return output;
}



QSet<NoteEntity*> Relation::successorsOf(const NoteEntity *note) const{
    QSet<NoteEntity*> result;
    unsigned int size = content.size();
    NoteEntity* successor;
    for (unsigned int i = 0;i<size;i++) {
        successor = content[i]->successor(note,oriented);
        if ( successor != nullptr) result.insert(successor);
    }

    return result;
}


QSet<NoteEntity*> Relation::predecessorsOf(const NoteEntity* note) const{
    QSet<NoteEntity*> result;
    unsigned int size = content.size();
    NoteEntity* predecessor;

    for (unsigned int i = 0;i<size;i++) {
        predecessor = content[i]->predecessor(note,oriented);
        if ( predecessor != nullptr) result.insert(predecessor);
    }

    return result;
}


bool Relation::hasPredecessors(const NoteEntity *note) const{
    return predecessorsOf(note).size() != 0;
}
