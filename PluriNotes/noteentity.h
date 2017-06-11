#ifndef NOTEENTITY_H
#define NOTEENTITY_H

#include "notes.h"
#include <vector>
#include "noteelement.h"


class NoteEntity {
private:
    QString id;
    bool archived;
    std::vector<const NoteElement*> versions;
public:
    NoteEntity(const QString& id, const bool& archived = false);
    virtual ~NoteEntity() { versions.clear(); }
    QString getId() const;
    QString getTitle() const;
    unsigned int getSize() const { return versions.size(); }
    const NoteElement& getLastVersion() const;
    const NoteElement& getVersion(unsigned int nb) const;
    bool isArchived() const;
    void addVersion(const NoteElement&);
    virtual void saveToXML(QXmlStreamWriter& stream) const;
    //! comparaison of note NoteEntity
    bool operator==(const NoteEntity& n)const;
    static void loadFromXML(QXmlStreamReader& stream);
};



inline QString NoteEntity::getId() const {return id;}
inline bool NoteEntity::isArchived() const {return archived;}

#endif // NOTEENTITY_H
