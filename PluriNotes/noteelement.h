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
    NoteElement(const QString& title) : title(title) {
        creationDate = QDateTime::currentDateTime();
    }
    static map<QString, NoteElement*> getTypesNotes();
    const QString& getTitle() const;
    const QDateTime& getCreationDate() const;
    virtual QList<QWidget*> champsForm() = 0;
    virtual void displayNote() const = 0;
    virtual NoteElement* saveNote(QString title) = 0;
    virtual ~NoteElement() = default;
};



inline const QString& NoteElement::getTitle() const { return title; }
inline const QDateTime& NoteElement::getCreationDate() const { return creationDate; }

#endif // NOTEELEMENT_H
