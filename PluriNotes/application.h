#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <vector>
#include <QMainWindow>
#include <QDate>
#include <QString>
#include <QScrollArea>
#include <QListWidgetItem>


#include "notes.h"

using namespace std;

class NoteEntity;

namespace Ui {
    class PluriNotes;
}

typedef map<QString,NoteElement*>::const_iterator MapIterator;

class PluriNotes : public QMainWindow {
    Q_OBJECT
private:
    Ui::PluriNotes *ui;
    static PluriNotes* instanceUnique;
    vector<const NoteEntity*> notes;
    vector<const NoteEntity*> corbeille;
    bool autoDelete;
    bool is_idChanged;
    explicit PluriNotes(QWidget *parent = 0);
    ~PluriNotes();
    PluriNotes(const PluriNotes& m);
    PluriNotes& operator=(const PluriNotes& m);

public:
    static PluriNotes& getManager();
    Ui::PluriNotes* getUi() { return ui; }
    void load(); // load notes from file
    void save() const; // save notes in file
    void deleteNote(const QString& id);
    void emptyTrash();
    void setAutoDelete(bool);
    void setTextContentArticle(const QString& c);
    void setNoteTitle(const QString& t);
    void setNoteId(const QString& i);

signals:
    public slots:
    void toNewNoteForm();
    void displayNote();
    void saveNote();
    void deleteNote();
    void cancelNote();
    void titleChanged();
    void idChanged();
    void typeChanged();
};


class listItemAndPointer : public QListWidgetItem {
private :
    NoteEntity* notePointer;
public :
    listItemAndPointer(NoteEntity* ptr) : notePointer(ptr) {}
    NoteEntity* getNotePointer() const {return notePointer;}
};

#endif // APPLICATION_H
