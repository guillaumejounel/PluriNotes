#ifndef NOTEENTITY_H
#define NOTEENTITY_H

#include "noteelement.h"
#include <QVector>
class NoteElement;

class NoteEntity {
private:
    QString id;
    bool archived;

    //! a small variable to store if the element has been trashed : it is redundant bus usefull!!
    bool trashed = false;

    //! for preventing issues when restoring a note with references
    bool Issues = false;

    QVector<const NoteElement*> versions;
public:
    NoteEntity(const QString& id, const bool& archived = false);
    virtual ~NoteEntity() { for(auto version : versions) delete version; versions.clear(); }
    QString getId() const {return id;}
    QString getTitle() const;
    unsigned int getSize() const { return versions.size(); }
    const NoteElement& getLastVersion() const;
    const NoteElement& getVersion(unsigned int nb) const;

    bool isArchived() const {return archived;}
    void setArchived(bool b) {archived = b;}

    bool isTrashed() const {return trashed;}
    void setTrashed(bool b) {trashed = b;}

    bool hasIssues() const {return Issues;}
    void setHasIssues(bool b) {Issues = b;}

    //! Is a note being referenced by an other note (in notes, not trash)
    bool isReferenced(bool outOfArchives = false) const;

    void addVersion(const NoteElement& newVersion);
    void deleteVersion(const NoteElement& version);

    virtual void saveToXML(QXmlStreamWriter& stream) const;
    static NoteEntity* loadFromXML(QXmlStreamReader& stream);

    //! Method to know if a version is inside the note entity
    bool isVersionInsideNote(const NoteElement& version) const;

    //! comparaison of note NoteEntity
    bool operator==(const NoteEntity& n)const;

    //! get the references in the last version
    QStringList returnReferences() const;
};

#endif // NOTEENTITY_H
