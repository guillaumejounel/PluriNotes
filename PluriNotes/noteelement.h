/**
\file noteelement.h
\date 14/06/2017
\author Florent Chehab, Guillaume Jounel and Félix Boisselier
\brief contains the note noteelement class
**/

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
\brief Parent class of the different note types
**/

class NoteElement {
private:
    //! \brief Title of the note
    const QString title;

    //! \brief Creation date of the note
    QDateTime creationDate;

protected:
    //! \brief Contains a map of different note type's names and pointers on it
    //! @param typeName name of the type of note
    //! @param ptNote pointer to the note
    static map<QString, NoteElement*> const& NoteTypeList (QString typeName, NoteElement* ptNote);

public:
    //! \brief Constructor of NoteElement without argument
    NoteElement() {}

    //! \brief Constructor of NoteElement
    //! @param title title of the note
    //! @param creaDate creationDate
    NoteElement(const QString& title, const QDateTime& creaDate) : title(title), creationDate(creaDate) { }

    //! \brief Accessor to the NoteTypeList
    static map<QString, NoteElement*> getTypesNotes();

    //! \brief Accessor to the title
    const QString& getTitle() const { return title; }

    //! \brief Accessor to the creation date
    const QDateTime& getCreationDate() const { return creationDate; }

    //! \brief Setter of the creation date
    void setCreationDate(const QDateTime& date) {creationDate =  date;}

    //! \brief Display note on the PluriNotes UI
    virtual void displayNote() const = 0;

    //! \brief Return index of the note creation form page
    virtual unsigned int indexPageCreation() const = 0;

    //! \brief Return a new note initialized by the note creation form UI inputs
    //! @param title title of the note
    virtual NoteElement* saveNote(QString title) = 0;

    //! \brief Return a new note initialized by the note creation form UI inputs
    virtual NoteElement* addVersion() const = 0;

    //! \brief Return true if the note edition form has UI inputs different from the note
    virtual bool textChanged() const = 0;

    //! \brief Save the note data in a file
    //! @param stream the xlm stream
    virtual void saveToXML(QXmlStreamWriter& stream) const = 0;

    //! \brief Load a note from a file and add it into a NoteEntity
    //! @param newNoteEntity the relative note entity
    //! @param stream the xlm stream
    virtual void loadFromXML(QXmlStreamReader& stream, NoteEntity& newNoteEntity) const = 0;

    //! \brief Return detected references from the note data
    virtual QStringList returnReferences() const = 0;

    //! \brief Return detected references from a QString
    //! @param text The text we have to parse to look for references
    QStringList getReferences(const QString& text) const;

    //! \brief Return the type name of the note
    virtual QString typeName() const = 0;

    //! \brief Destructor of NoteElement
    virtual ~NoteElement() = default;

    // UI

    //! \brief Set the note title in the UI
    //! @param t title of the note
    void setUiNoteTitle(const QString& t) const;

    //! \brief Get the note title int the UI
    const QString getUiNoteTitleEdit() const;

    //! \brief Set the date field in the UI
    //! @param d note date
    void setUiNoteDate(const QDateTime& d) const;

};
#endif // NOTEELEMENT_H
