/**
\file application.h
\date 28/05/2017
\author Florent Chehab, Guillaume Jounel and Félix Boisselier
\brief contains the core application
**/


#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <vector>
#include <QMainWindow>
#include <QString>
#include <QScrollArea>
#include <QLineEdit>
#include <QMessageBox>
#include <QVector>

#include <QWidget>

#include <QCloseEvent>


#include "notes.h"
#include "othertools.h"
#include "relation.h"
#include "relationswindows.h"

class QAction;
class QToolBar;
class QMenu;
class QUndoStack;
class QUndoView;

using namespace std;

class NoteEntity;

namespace Ui {
    class PluriNotes;
}

//! What is this for ???
//! ??
typedef map<QString,NoteElement*>::const_iterator MapIterator;

/**
\class Plurinotes
\brief Main class of the applicatin with the ui

Write description here

\todo Many Things
**/
class PluriNotes : public QMainWindow {
    Q_OBJECT
private:
    //! \brief Pointer to the ui
    Ui::PluriNotes *ui;

    //! Implementation of the singleton design pattern
    //! \brief Pointer to the unique class instanciation
    static PluriNotes* instanceUnique;

    //! Vector containing all the active notes in the application
    //! \brief Vector containing the active notes
    QVector<const NoteEntity*> notes;

    //! Vector containing all the notes sent to the trash
    //! \brief Vector containing the trashed notes
    QVector<const NoteEntity*> trash;

    //! Vector containing all Relations of the application
    QVector<const Relation*> relations;

    //! \todo WHAT IS THIS ??
    bool autoDelete;

    //! Boolean for the id autofill form if not already changed
    //! \brief Boolean for the id autofill form
    bool is_idChanged;

    bool isDisplayed;

    //! \todo WHAT IS THIS ??
    explicit PluriNotes(QWidget *parent = 0);

    //! Implementation of the singleton design pattern, the destructor has to be private
    ~PluriNotes();

    //! \todo Details ??
    PluriNotes(const PluriNotes& m);

    //! \todo Details ??
    PluriNotes& operator=(const PluriNotes& m);

    //! Function to load the notes from the saved file
    //! \brief loading function
    void load();

    //! Function to save the notes to an xml
    //! \brief saving function
    void save();

    bool dataChanged = false;

    void createActions();
    void createMenus();
    void createUndoView();
    void createRelationsView();

    QAction *deleteAction;
    QAction *undoAction;
    QAction *redoAction;
    QAction *exitAction;
    QAction *saveAction;
    QAction *aboutAction;
    QAction *openRelations;

    // QActions for windows
    QAction *viewUndoHistory;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *relationsMenu;
    QMenu *windowsMenu;
    QMenu *helpMenu;

    QUndoStack *undoStack;

    //! \brief history window
    QUndoView *undoView;

    //! \brief Relation window
    QWidget* relationsView;

    NoteEntity& getCurrentNote();


public:
    //! Implementation of the singleton design pattern : get the only instance
    static PluriNotes& getManager();

    //! \brief Accessor to the ui
    Ui::PluriNotes* getUi() { return ui; }

    //! Delete note based on its id
    void deleteNote(const QString& id);

    //! \brief Function to know if a note can be deleted
    bool isInsideApp(const NoteEntity *note);

    //! Function to move a note element from notes to trash
    void moveToTrash(NoteEntity* noteEl);

    //! Function to move a note element from trash to notes
    void moveBackFromTrash(NoteEntity* noteEl);

    //! \brief Empty trash
    void emptyTrash();

    //! \todo What is this ?
    void setAutoDelete(bool);

    //! Setter for the ui :\n
    //! This is for note titles
    //! \brief Setter UI, note titles
    void setNoteTitle(const QString& t);

    //! Loading data into interface function
    void loadDataIntoUi();

//    //! Setter for the ui :\n
//    //! This is for note id
//    //! \brief Setter UI, note id
//    void setNoteId(const QString& i);




    //! Setter for the ui :\n
    //! This is for note date
    //! \brief Setter UI, note date
    void setNoteDate(const QDateTime& d);

    const QString getNoteTitleEdit();

    void setArticleContent(const QString& content);
    const QString getArticleContent();
    const QString getArticleContentEdit();


    void setTaskAction(const QString& action);
    void setTaskStatus(unsigned int i);
    void setTaskPriority(unsigned int i);
    void setTaskDeadline(const QDateTime& date);

    unsigned int getTaskPriority();
    const QString getTaskAction();
    const QDateTime getTaskDeadline();

    unsigned int getTaskPriorityEdit();
    unsigned int getTaskStatusEdit();
    const QString getTaskActionEdit();
    const QDateTime getTaskDeadlineEdit();

    //! Function to add a note in the system \n
    //! Returns an "listItemAndPointer*" the should be usefull in somme cases
    listItemAndPointer* addNote(NoteEntity* note);

    //! \brief Function to remove a note
    //! \warning the memory is not fried
    void removeNote(NoteEntity* note);


    //! Function to add an listItemAndPointer* to the list of notes
    void addItemNoteToList(listItemAndPointer* item);

    //! Function to add a NoteEntity to the list of note \n
    //! With creation of a listItemAndPointer*
    listItemAndPointer* addNoteToList(NoteEntity* note);

    //! Function wich removes a listItemAndPointer* from the list\n
    //! it is returned so that it can be stored if we need it
    listItemAndPointer* removeItemNoteFromList(listItemAndPointer* item);


    //! ######################################################
    //! ######################################################
    //! New methods for better undo redo command handling
    //!

    void removeNoteFromList(NoteEntity* note);


    //!
    //!
    //! #######################################################
    //! #######################################################

    //! Function to check if their has been modification to plurinotes
    bool hasDataChanged() const {return dataChanged;}

    void setDataChanged(bool b);

    //! Before closing
    void closeEvent ( QCloseEvent * event );


    //! Getter for the max current nb (id) relations
    unsigned int getMaxRelationId();

    //! Method to get a pointer to the references relation
    Relation* getReferencesRelation();

    //! Method to get all successors of a note
    QSet<NoteEntity*> allSuccessorsOf(NoteEntity* note) const;

    //! Method to get all predecessors of a note
    QSet<NoteEntity*> allPredecessorsOf(NoteEntity* note) const;






signals:
    public slots:
    //! Method to change stackedWidget to make new notes
    void toNewNoteForm();

    //! Method to change stackedWidget to the note display window and adapt fields
    void displayNote(unsigned int n = 0);

    //! \todo What is this ?
    void saveNote();

    //! \todo What is this ?
    void deleteNote();

    //! \todo What is this ?
    void cancelNote();

    //! \todo What is this ?
    void titleChanged();

    //! \todo What is this ?
    void idChanged();

    //! Method to change QT fields in the new note form (with type of note in mind)
    void typeChangedForm();

    //! savefunction
    void saveApplication();

    //! open relationsWidnows
    void openRelationsWindow();

    void noteTextChanged();
    void saveNewVersion();
    void noteVersionChanged();

    /// Windows managment :
    void showUndoHistoryWindows();
};




#endif // APPLICATION_H
