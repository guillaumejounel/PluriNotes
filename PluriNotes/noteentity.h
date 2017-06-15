/**
\file noteentity.h
\date 14/06/2017
\author Florent Chehab, Guillaume Jounel and Félix Boisselier
\brief contains the note Entity class
**/


#ifndef NOTEENTITY_H
#define NOTEENTITY_H

#include "noteelement.h"
#include <QVector>

class NoteElement;


/**
\class NoteEntity
\brief Class to store the note entity

One note is a note entity ; a note entity can have multiple version
**/
class NoteEntity {
private:
    //! \brief if of the note
    QString id;

    //! \brief is the note archived
    bool archived;

    //! \brief is the note in the trash ?
    //! a small variable to store if the element has been trashed : it is redundant bus usefull!!
    bool trashed = false;

    //! \brief issues with referencing ?
    //! for preventing issues when restoring a note with references
    bool Issues = false;

    //! \brief vector consisting of the versions of the note
    QVector<const NoteElement*> versions;

public:
    //! \brief Constructor of NoteEntity
    //! @param id id of the note
    //! @param archived default false : is the note archived
    NoteEntity(const QString& id, const bool& archived = false);

    //! \brief Destructor of the class
    virtual ~NoteEntity() { for(const NoteElement* version: versions) if (version) delete version; versions.clear(); }

    //! \brief getter to the id of the note
    QString getId() const {return id;}

    //! \brief getter to the title of the note
    QString getTitle() const;

    //! \brief getter to the number of versions
    unsigned int getSize() const { return versions.size(); }

    //! \brief getter to the last version of the note
    const NoteElement* getLastVersion() const;

    //! \brief getter to a specific version of a note
    const NoteElement& getVersion(unsigned int nb) const;

    //! \brief getter to if the note is archived or not
    bool isArchived() const {return archived;}

    //! \brief setter for the archive status
    //! @param b new archive status
    void setArchived(bool b) {archived = b;}

    //! \brief getter to the trash status
    bool isTrashed() const {return trashed;}

    //! \brief Set the trash status
    //! @param b new trash status
    void setTrashed(bool b) {trashed = b;}

    //! \brief Has the note issues with references ?
    bool hasIssues() const {return Issues;}

    //! \brief setter to the references issues status
    //! @param b new status
    void setHasIssues(bool b) {Issues = b;}

    //! \brief is the tote referenced
    //! @param outOfArchives If we have to ignore trashed and archived note
    //! Is a note being referenced by an other note (in notes, not trash)
    bool isReferenced(bool outOfArchives = false) const;

    //! \brief add a version to the note
    //! @param newVersion new version of the note
    void addVersion(const NoteElement& newVersion);

    //! \brief delete a version of the note
    //! @param version the version we want to delete
    void deleteVersion(const NoteElement& version);

    //! \brief Save the note entity to xml file
    //! @param stream the xlm stream
    virtual void saveToXML(QXmlStreamWriter& stream) const;

    //! \brief load a note entity from xml
    //! @param stream the xlm stream
    static NoteEntity* loadFromXML(QXmlStreamReader& stream);

    //! \brief Method to know if a version is inside the note entity
    bool isVersionInsideNote(const NoteElement& version) const;

    //! \brief definition of the comparaison operation
    //! comparaison of note NoteEntity
    bool operator==(const NoteEntity& n)const;

    //! \brief get the references in the last version
    QStringList returnReferences() const;
};

#endif // NOTEENTITY_H
