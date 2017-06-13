#include "notecouple.h"

bool NoteCouple::isEqualX(const NoteEntity* note) const {
    if (note == x || note->getId() == x->getId()) return true;
    return false;
}

bool NoteCouple::isEqualY(const NoteEntity* note) const {
    if (note == y || note->getId() == y->getId()) return true;
    return false;
}

bool NoteCouple::contains(const NoteEntity* note) const {
    return (isEqualX(note)||isEqualY(note));
}

bool NoteCouple::operator==(const NoteCouple& c) const {
    if (isEqualX(c.getX()) && isEqualY(c.getY())) return true;
    return false;
}

NoteEntity* NoteCouple::successor(const NoteEntity *note, bool oriented) const {
    if (isEqualX(note)) return y;

    if (oriented == false && isEqualY(note)) return x;
    return nullptr;
}

NoteEntity* NoteCouple::predecessor(const NoteEntity* note, bool oriented, bool outOfArchives) const {
    if (outOfArchives==true && (getX()->isArchived()) || getX()->isTrashed()){//usefull for is referenced function
        return nullptr;
    }
    if (isEqualY(note)) return x;
    if (oriented == false && isEqualX(note)) return y;
    return nullptr;
}

QString NoteCouple::print() const {
    QString result;
    if (this->getLabel() != "")
        result = this->getLabel() + QString(" : (") + this->getX()->getId() + QString(" , ") + this->getY()->getId() + QString(")");
    else
        result =  QString("(") + this->getX()->getId() + QString(" , ") + this->getY()->getId() + QString(")");
    return result;
}

void NoteCouple::saveToXML(QXmlStreamWriter& stream) const {
    stream.writeStartElement("couple");
    stream.writeTextElement("label", label);
    stream.writeTextElement("x", x->getId());
    stream.writeTextElement("y", y->getId());
    stream.writeEndElement();
}

NoteCouple* NoteCouple::loadFromXML(QXmlStreamReader& stream) {
    QString label;
    NoteEntity *x, *y;
    NoteCouple* newNoteCouple;
    PluriNotes& manager = PluriNotes::getManager();

    while(!(stream.tokenType() == QXmlStreamReader::EndElement && stream.name() == "couple")) {
        if(stream.tokenType() == QXmlStreamReader::StartElement) {
            if(stream.name() == "label") {
                stream.readNext(); label=stream.text().toString();
            }
            if(stream.name() == "x") {
                stream.readNext(); x=manager.getNoteById(stream.text().toString());
            }
            if(stream.name() == "y") {
                stream.readNext(); y=manager.getNoteById(stream.text().toString());
                newNoteCouple = new NoteCouple(label, x, y);
                return newNoteCouple;
            }
        }
        stream.readNext();
    }
    return nullptr;
}
