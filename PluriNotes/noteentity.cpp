#include "noteentity.h"



NoteEntity::NoteEntity(const QString& id) : id(id){
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


bool NoteEntity::operator==(const NoteEntity& n)const{
    return (id==n.getId());
}


void NoteEntity::deleteVersion(const NoteElement &version){
    versions.removeAll(&version);
}


bool NoteEntity::isVersionInsideNote(const NoteElement& version) const{
    return versions.contains(&version);
}
