#ifndef PLURINOTES_H
#define PLURINOTES_H

#include <iostream>
#include <vector>
#include <QMainWindow>

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
    void deleteNote(const string& id);
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


class NoteEntity {
    bool test;

};

#endif // PLURINOTES_H
