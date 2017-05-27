#include "noteentity.h"



NoteEntity::NoteEntity(const QString& id) : id(id){
}

QString NoteEntity::getId() const {return id;}

QString NoteEntity::getTitle() const{return versions.back()->getTitle();}


void NoteEntity::addVersion(const NoteElement& newVersion) {
    versions.push_back(&newVersion);
}



const NoteElement& NoteEntity::getLastVersion() const {
    return *versions.back();
}
