#ifndef NOTEELEMENT_H
#define NOTEELEMENT_H


#include <map>
#include <QDateTime>
#include <QString>
#include <QtGui>

using namespace std;

class NoteElement {
private:
    const QString title;
    QDateTime creationDate;
protected:
    static map<QString, NoteElement*> const& NoteTypeList (QString typeName, NoteElement* ptNote);
public:
    NoteElement() {}
    NoteElement(const QString& title, const QDateTime& creaDate) : title(title), creationDate(creaDate){
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
    virtual ~NoteElement() = default;
};



inline const QString& NoteElement::getTitle() const { return title; }
inline const QDateTime& NoteElement::getCreationDate() const { return creationDate; }
inline void NoteElement::setCreationDate(const QDateTime& date) {creationDate =  date;}

#endif // NOTEELEMENT_H
