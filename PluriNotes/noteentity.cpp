#include "noteentity.h"



NoteEntity::NoteEntity(const QString& id) : id(id){
}


void NoteEntity::addVersion(const NoteElement& newVersion) {
    versions.push_back(&newVersion);
}

QString NoteEntity::getTitle() const{return versions.back()->getTitle();}


const NoteElement& NoteEntity::getLastVersion() const {
    return *versions.back();
}
