#include "noteentity.h"
#include "application.h"


NoteEntity::NoteEntity(const QString& id, const bool& archived) : id(id), archived(archived) {
}


void NoteEntity::addVersion(const NoteElement& newVersion) {
    versions.push_back(&newVersion);
}

QString NoteEntity::getTitle() const {
    return versions.back()->getTitle();
}


const NoteElement& NoteEntity::getLastVersion() const {
    return *versions.back();
}


const NoteElement& NoteEntity::getVersion(unsigned int nb) const {
    return *versions[nb];
}


bool NoteEntity::operator==(const NoteEntity& n)const {
    return (id==n.getId());
}

void NoteEntity::saveToXML(QXmlStreamWriter& stream) const {
    stream.writeStartElement("note");
    stream.writeTextElement("type",getLastVersion().typeName());
    stream.writeTextElement("id",getId());
    stream.writeTextElement("archived",archived?"true":"false");
    stream.writeStartElement("versions");
    for(unsigned int i = 0; i < getSize(); ++i) {
        getVersion(i).saveToXML(stream);
    }
    stream.writeEndElement();
    stream.writeEndElement();
}

void NoteEntity::loadFromXML(QXmlStreamReader& stream) {
    QString type, id;
    bool archived;
    map<QString,NoteElement*> myMap = NoteElement::getTypesNotes();

    while(!(stream.tokenType() == QXmlStreamReader::EndElement && stream.name() == "note")) {
        if(stream.tokenType() == QXmlStreamReader::StartElement) {
            if(stream.name() == "type") {
                stream.readNext(); type=stream.text().toString();
                qDebug()<<"type="<<type;
            }
            if(stream.name() == "id") {
                stream.readNext(); id=stream.text().toString();
                qDebug()<<"id="<<id;
            }
            if(stream.name() == "archived") {
                stream.readNext(); archived=(stream.text().toString()==QString("true")?true:false);
                qDebug()<<"archived="<<(archived?"true":"false");
            }
            if(stream.name() == "versions") {
                NoteEntity *newNoteEntity = new NoteEntity(QString(id));
                while (!(stream.tokenType() == QXmlStreamReader::EndElement && stream.name() == "versions")) {
                    //if(stream.tokenType() == QXmlStreamReader::StartElement && stream.name() == "version")
                        //myMap[type.toUtf8().constData()]->loadFromXML(stream, *newNoteEntity);
                    stream.readNext();
                }
                PluriNotes& manager = PluriNotes::getManager();
                //manager.addNote(newNoteEntity);
            }
        }
        stream.readNext();
    }
}

void NoteEntity::deleteVersion(const NoteElement &version){
    versions.removeAll(&version);
}


bool NoteEntity::isVersionInsideNote(const NoteElement& version) const{
    return versions.contains(&version);
}
