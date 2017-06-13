#include "relation.h"
#include "notecouple.h"
#include "application.h"

Relation::Relation(QString& title, QString& description, bool isOriented, bool isReferences, bool deleted, unsigned int number) : title(title), description(description), oriented(isOriented), references(isReferences), deleted(deleted), number(number) {}

Relation::Relation(QString &t, QString &d, bool isOriented) : title(t), description(d), oriented(isOriented), references(false) {
    PluriNotes& manager = PluriNotes::getManager();
    number = manager.getMaxRelationId();
    if (number != 0) number++;
}

Relation::~Relation() {
    for (auto couple : content)
        delete couple;
    for (auto couple : deletedTMP)
        delete couple;
}

bool Relation::isInside(const NoteCouple* c) const {
    return isInside(c->getX(),c->getY());
}

bool Relation::isInside(NoteEntity* note1, NoteEntity* note2) const {
    QString tmp = "tmp";
    NoteCouple nCouple1 = NoteCouple(tmp,note1,note2);
    NoteCouple nCouple2 = NoteCouple(tmp,note2,note1);

    unsigned int size = content.size();

    for (unsigned int i = 0;i<size;i++)
        if (*content[i] == nCouple1)
            return true;

    if (this->isOriented() == false)
        for (unsigned int i = 0;i<size;i++)
            if ( *content[i] == nCouple2 )
                return true;
    return false;
}

bool Relation::isInside(NoteEntity* note) const {
    for (auto couple : content) {
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
     for (auto couple : content) {
        if (couple == c) {
            // We duplicate the couple
            //NoteCouple* tmp = new NoteCouple(*couple);
            //coupleAndRelation output = coupleAndRelation(tmp,this);
            content.removeAll(const_cast<NoteCouple*>(c));
            //delete c;
            break;
        }
    }
}

void Relation::removeCouple(const QList<NoteCouple*> coupleList) {
    for (auto couple : coupleList) {
        removeCouple(couple);
    }
}

void Relation::removeCoupleWithNote(const NoteEntity* note) {
     for (auto couple : content) {
        if (couple->contains(note)) {
            //output.append(coupleAndRelation(new NoteCouple(*couple),this));
            content.removeAll(couple);
            delete couple;
        }
    }
    //return output;
}

void Relation::removeCoupleWithNotePredecessor(const NoteEntity* note) {
    //only for oriented !
    for (auto couple : content) {
       if (couple->isEqualX(note)) {
           //output.append(coupleAndRelation(new NoteCouple(*couple),this));
           content.removeAll(couple);
           delete couple;
       }
   }
}

void Relation::removeCoupleWithNote(const QList<NoteEntity*> noteList) {
    //QList<coupleAndRelation> output;
    for (auto note : noteList) {
        removeCoupleWithNote(note);
    }
    //return output;
}

QSet<NoteEntity*> Relation::successorsOf(const NoteEntity *note) const {
    QSet<NoteEntity*> result;
    unsigned int size = content.size();
    NoteEntity* successor;
    for (unsigned int i = 0;i<size;i++) {
        successor = content[i]->successor(note,oriented);
        if ( successor != nullptr) result.insert(successor);
    }
    return result;
}

QSet<NoteEntity*> Relation::predecessorsOf(const NoteEntity* note, bool outOfArchives) const {
    QSet<NoteEntity*> result;
    unsigned int size = content.size();
    NoteEntity* predecessor;
    for (unsigned int i = 0;i<size;i++) {
        predecessor = content[i]->predecessor(note,oriented,outOfArchives);
        if ( predecessor != nullptr) result.insert(predecessor);
    }
    return result;
}

bool Relation::hasPredecessors(const NoteEntity *note, bool outOfArchives) const {
    return predecessorsOf(note, outOfArchives).size() != 0;
}

void Relation::saveToXML(QXmlStreamWriter& stream) const {
    stream.writeStartElement("relation");
    stream.writeTextElement("title", title);
    stream.writeTextElement("description", description);
    stream.writeTextElement("deleted",deleted?"true":"false");
    stream.writeTextElement("oriented",oriented?"true":"false");
    stream.writeTextElement("references",references?"true":"false");
    stream.writeTextElement("number", QString::number(number));
    stream.writeStartElement("content");
    for(NoteCouple* couple: content)
        couple->saveToXML(stream);
    stream.writeEndElement();
    stream.writeEndElement();
}

Relation* Relation::loadFromXML(QXmlStreamReader& stream) {
    QString title, description;
    bool deleted, oriented, references;
    unsigned int number;
    Relation* newRelation;
    NoteCouple* newCouple;

    while(!(stream.tokenType() == QXmlStreamReader::EndElement && stream.name() == "relation")) {
        if(stream.tokenType() == QXmlStreamReader::StartElement) {
            if(stream.name() == "title") {
                stream.readNext(); title=stream.text().toString();
            }
            if(stream.name() == "description") {
                stream.readNext(); description=stream.text().toString();
            }
            if(stream.name() == "deleted") {
                stream.readNext(); deleted=(stream.text().toString()==QString("true")?true:false);
            }
            if(stream.name() == "oriented") {
                stream.readNext(); oriented=(stream.text().toString()==QString("true")?true:false);
            }
            if(stream.name() == "references") {
                stream.readNext(); references=(stream.text().toString()==QString("true")?true:false);
            }
            if(stream.name() == "number") {
                stream.readNext(); number=(stream.text().toInt());
            }
            if(stream.name() == "content") {
                PluriNotes& manager = PluriNotes::getManager();
                if(!number) newRelation = manager.getReferencesRelation();
                else newRelation = new Relation(title, description, oriented, references, deleted, number);
                while (!(stream.tokenType() == QXmlStreamReader::EndElement && stream.name() == "content")) {
                    stream.readNext();
                    if(stream.tokenType() == QXmlStreamReader::StartElement && stream.name() == "couple") {
                        newCouple = NoteCouple::loadFromXML(stream);
                        newRelation->addCouple(newCouple);
                    }
                }
                return newRelation;
            }
        }
        stream.readNext();
    }
    return nullptr;
}
