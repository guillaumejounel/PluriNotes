#ifndef NOTEELEMENT_H
#define NOTEELEMENT_H

#include <map>
#include <QDateTime>
#include <QtGui>
#include "ui_plurinotes.h"
#include "application.h"

using namespace std;

class NoteEntity;
class PluriNotes;

/**
\class NoteElement
\brief Parent class of different note types
**/

class NoteElement {
private:
    //! \brief Title of the note
    const QString title;

    //! \brief Creation date of the note
    QDateTime creationDate;

protected:
    //! \brief Contains a map of different note type's names and pointers on it
    static map<QString, NoteElement*> const& NoteTypeList (QString typeName, NoteElement* ptNote);

public:
    //! \brief Constructor of NoteElement without argument
    NoteElement() {}

    //! \brief Constructor of NoteElement
    NoteElement(const QString& title, const QDateTime& creaDate) : title(title), creationDate(creaDate) { }

    //! \brief Accessor to the NoteTypeList
    static map<QString, NoteElement*> getTypesNotes();

    //! \brief Accessor to the title
    const QString& getTitle() const;

    //! \brief Accessor to the creation date
    const QDateTime& getCreationDate() const;

    //! \brief Setter of the creation date
    void setCreationDate(const QDateTime& date);

    //! \brief Display note on the PluriNotes UI
    virtual void displayNote() const = 0;

    //! \brief Return index of the note creation form page
    virtual unsigned int indexPageCreation() const = 0;

    //! \brief Return a new note initialized by the note creation form UI inputs
    virtual NoteElement* saveNote(QString title) = 0;

    //! \brief Return a new note initialized by the note creation form UI inputs
    virtual NoteElement* addVersion() const = 0;

    //! \brief Return true if the note edition form has UI inputs different from the note
    virtual bool textChanged() const = 0;

    //! \brief Save the note data in a file
    virtual void saveToXML(QXmlStreamWriter& stream) const = 0;

    //! \brief Load a note from a file and add it into a NoteEntity
    virtual void loadFromXML(QXmlStreamReader& stream, NoteEntity& newNoteEntity) const = 0;

    //! \brief Return detected references from the note data
    virtual QStringList returnReferences() const = 0;

    //! \brief Return detected references from a QString
    QStringList getReferences(const QString& text) const;

    //! \brief Return the type name of the note
    virtual QString typeName() const = 0;

    //! \brief Destructor of NoteElement
    virtual ~NoteElement() = default;

    // UI

    //! \brief Set the note title in the UI
    void setUiNoteTitle(const QString& t) const;

    //! \brief Get the note title int the UI
    const QString getUiNoteTitleEdit() const;

    //! \brief Set the date field in the UI
    void setUiNoteDate(const QDateTime& d) const;

};

inline const QString& NoteElement::getTitle() const { return title; }
inline const QDateTime& NoteElement::getCreationDate() const { return creationDate; }
inline void NoteElement::setCreationDate(const QDateTime& date) {creationDate =  date;}

#endif // NOTEELEMENT_H
