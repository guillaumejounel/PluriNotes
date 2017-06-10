#ifndef NOTEENTITY_H
#define NOTEENTITY_H

#include "notes.h"
#include "noteelement.h"
#include <QVector>


class NoteEntity {
private:
    QString id;
    bool archived;
    QVector<const NoteElement*> versions;
public:
    NoteEntity(const QString& id);
    ~NoteEntity() { versions.clear(); }
    QString getId() const;
    QString getTitle() const;
    unsigned int getSize() const { return versions.size(); }
    const NoteElement& getLastVersion() const;
    const NoteElement& getVersion(unsigned int nb) const;
    bool isArchived() const;
    void addVersion(const NoteElement& newVersion);
    void deleteVersion(const NoteElement& version);

    //! Method to know if a version is inside the note entity
    bool isVersionInsideNote(const NoteElement& version) const;

    //! comparaison of note NoteEntity
    bool operator==(const NoteEntity& n)const;
};



inline QString NoteEntity::getId() const {return id;}
inline bool NoteEntity::isArchived() const {return archived;}

#endif // NOTEENTITY_H
