#ifndef PLURINOTES_H
#define PLURINOTES_H

#include <iostream>
#include <vector>
#include <QMainWindow>
#include <QDate>
#include <QString>

using namespace std;

class NoteEntity;

namespace Ui {
    class PluriNotes;
}

class PluriNotes : public QMainWindow {
    Q_OBJECT
public:
    void load(); // load notes from file
    void save() const; // save notes in file
    static PluriNotes& getManager();
    void deleteNote(const QString& id);
    void emptyTrash();
    void setAutoDelete(bool);

private:
    Ui::PluriNotes *ui;
    static PluriNotes* instanceUnique;
    vector<NoteEntity> notes;
    vector<NoteEntity> corbeille;
    bool autoDelete;
    explicit PluriNotes(QWidget *parent = 0);
    ~PluriNotes();
    PluriNotes(const PluriNotes& m);
    PluriNotes& operator=(const PluriNotes& m);
signals:
public slots:
    void createNote();
};

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
