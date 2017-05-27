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
    const QString& getTitle() const { return title; }
    const QDateTime& getCreationDate() const { return creationDate; }
    virtual QList<QWidget*> champsForm() = 0;
    virtual void displayNote() const = 0;
    virtual NoteElement* saveNote(QString title) = 0;
    virtual ~NoteElement() = default;
};




#endif // NOTEELEMENT_H
