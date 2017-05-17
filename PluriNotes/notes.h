#ifndef PLURINOTES_H
#define PLURINOTES_H

#include <iostream>
#include <vector>
#include <QDate>
#include <QString>

using namespace std;

class NoteEntity;

namespace Ui {
    class PluriNotes;
}


class NoteElement;

class NoteEntity {
private:
    QString id;
    QDate creationDate;
    QDate modificationDate;
    bool archived;
    bool bin;
    vector<NoteElement> versions;
public:
    NoteEntity(const QString& id) { cout << "Note " << id.toUtf8().constData() << " en cours de création" << endl; }
    ~NoteEntity() {}
    QString getId() const;
    QDate getCreationDate() const;
    QDate getModificationDate() const;
    bool isArchived() const;

};

class NoteElement {
    QString title;
public:
    NoteElement(const QString& title);
    //virtual ~NoteElement();
    //virtual QString getTitle() const = 0;
    // Need to implement a function to open the specific edition window
};

#endif // PLURINOTES_H
