#include "notes.h"

NoteEntity::NoteEntity(const QString& id) {
    cout << "Note \"" << id.toUtf8().constData() << "\" is being created." << endl;
}
