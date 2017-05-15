#ifndef NOTES_H
#define NOTES_H

#include <iostream>
#include <vector>
using namespace std;

class NoteEntity;

class NotesManager {
private:
    static NotesManager instanceUnique;
    vector<NoteEntity> notes;
    vector<NoteEntity> corbeille;
    bool autoDelete;
    NotesManager();
    ~NotesManager();
    NotesManager(const NotesManager& m);
    NotesManager& operator=(const NotesManager& m);
public:
    void load(); // load notes from file
    void save() const; // save notes in file
    static NotesManager& getManager();
    void createNote(const string& id);
    void deleteNote(const string& id);
    void emptyTrash();
    void setAutoDelete(bool);
};

class NoteEntity {
    bool test;

};

#endif // NOTES_H
