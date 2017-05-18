#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <vector>
#include <QMainWindow>
#include <QDate>
#include <QString>

#include "notes.h"

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
    vector<NoteEntity*> notes;
    vector<NoteEntity*> corbeille;
    bool autoDelete;
    bool is_idChanged;
    explicit PluriNotes(QWidget *parent = 0);
    ~PluriNotes();
    PluriNotes(const PluriNotes& m);
    PluriNotes& operator=(const PluriNotes& m);
signals:
public slots:
    void formNote();
    void saveNote();
    void cancelNote();
    void titleChanged();
    void idChanged();
    void typeChanged();
};

#endif // APPLICATION_H
