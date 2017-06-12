#ifndef NOTEELEMENT_H
#define NOTEELEMENT_H


#include <map>
#include <QDateTime>
#include <QString>
#include <QtGui>
#include "ui_plurinotes.h"
#include "application.h"

using namespace std;

class NoteEntity;
class PluriNotes;

class NoteElement {
private:
    const QString title;
    QDateTime creationDate;
protected:
    static map<QString, NoteElement*> const& NoteTypeList (QString typeName, NoteElement* ptNote);
public:
    NoteElement() {}
    NoteElement(const QString& title, const QDateTime& creaDate) : title(title), creationDate(creaDate) {
       // creationDate = QDateTime::currentDateTime();
    }
    static map<QString, NoteElement*> getTypesNotes();
    const QString& getTitle() const;
    const QDateTime& getCreationDate() const;
    void setCreationDate(const QDateTime& date);
    virtual unsigned int indexPageCreation() const = 0;
    virtual void displayNote() const = 0;
    virtual NoteElement* saveNote(QString title) = 0;
    virtual NoteElement* addVersion() const = 0;
    virtual bool textChanged() const = 0;
    virtual void saveToXML(QXmlStreamWriter& stream) const = 0;
    virtual QString typeName() const = 0;
    virtual void loadFromXML(QXmlStreamReader& stream, NoteEntity& newNoteEntity) const = 0;
    virtual ~NoteElement() = default;

    // UI

    //! \brief Set the note title in the UI
    void setUiNoteTitle(const QString& t) const;

    //! \brief Get the note title int the UI
    const QString getUiNoteTitleEdit() const;


    //! \brief set the date fiel in the UI
    void setUiNoteDate(const QDateTime& d) const;

    //! method to get the references in a text
    QStringList getReferences(const QString& text) const;

    //! method to get the references inside a specific type of note
    virtual QStringList returnReferences() const = 0;
};



inline const QString& NoteElement::getTitle() const { return title; }
inline const QDateTime& NoteElement::getCreationDate() const { return creationDate; }
inline void NoteElement::setCreationDate(const QDateTime& date) {creationDate =  date;}

#endif // NOTEELEMENT_H
