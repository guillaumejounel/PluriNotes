#include "notes.h"

NoteEntity::NoteEntity(const QString& id) : id(id){
    cout << "Note \"" << id.toUtf8().constData() << "\" is being created." << endl;
}

QString NoteEntity::getId() const {return id;}


void NoteEntity::addVersion(const NoteElement& newVersion){
    versions.push_back(&newVersion);
}
