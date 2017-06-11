#ifndef NOTEENTITY_H
#define NOTEENTITY_H

#include "noteelement.h"
#include <QVector>
class NoteElement;

class NoteEntity {
private:
    QString id;
    bool archived;
    QVector<const NoteElement*> versions;
public:
    NoteEntity(const QString& id, const bool& archived = false);
    virtual ~NoteEntity() { versions.clear(); }
    QString getId() const;
    QString getTitle() const;
    unsigned int getSize() const { return versions.size(); }
    const NoteElement& getLastVersion() const;
    const NoteElement& getVersion(unsigned int nb) const;
    bool isArchived() const;

    void addVersion(const NoteElement& newVersion);
    void deleteVersion(const NoteElement& version);
    virtual void saveToXML(QXmlStreamWriter& stream) const;

    //! Method to know if a version is inside the note entity
    bool isVersionInsideNote(const NoteElement& version) const;

    //! comparaison of note NoteEntity
    bool operator==(const NoteEntity& n)const;
    static NoteEntity* loadFromXML(QXmlStreamReader& stream);
};

#endif // NOTEENTITY_H
