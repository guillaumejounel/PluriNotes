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
#include "notecouple.h"

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

//! \todo add comment for this line ; I don't understant what it is ! :p
typedef map<QString,NoteElement*>::const_iterator MapIterator;

/**
\class Plurinotes
\brief Main class of the applicatin with the ui for the core application
**/
class PluriNotes : public QMainWindow {
    Q_OBJECT
private:
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // Basics, main attributes :
    // --------------------------------------------------------------------------

    //! \brief Pointer to the ui
    Ui::PluriNotes *ui;

    //! Implementation of the singleton design pattern, the destructor has to be private
    ~PluriNotes();

    //! Implementation of the singleton design pattern
    //! \brief Pointer to the unique class instanciation
    static PluriNotes* instanceUnique;

    //! Core
    //! Vector containing all the active notes in the application
    //! \brief Vector containing the active notes
    QVector<NoteEntity*> notes;

    //! Vector containing all the notes sent to the trash
    //! \brief Vector containing the trashed notes
    QVector<NoteEntity*> trash;

    //! Vector containing all Relations of the application
    QVector<Relation*> relations;

    //! \todo Add documentation !!!!
    bool autoDelete;

    //! \todo Add documentation !!!!
    bool isDisplayed;

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------




    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // UI related creation elements :
    // --------------------------------------------------------------------------

    //! \brief method to create the menu on the main window
    void createMenus();

    //! \brief method to create the actions on the main window
    void createActions();

    //! \brief method to create the undo window
    //! It is not shown after the creation.
    void createUndoView();

    //! \brief method to create the relations managment window
    //! It is not shown after the creation.
    void createRelationsView();

    //-------
    // Other Windows
    //! \brief history window
    QUndoView *undoView;

    //! \brief Relation window
    QWidget* relationsView;
    //-------

    //! Undostack for the undo/redo process in the app
    QUndoStack *undoStack;

    //-------
    // Menus
    //! \brief File menu
    QMenu *fileMenu;

    //! \brief edit menu
    QMenu *editMenu;

    //! \brief windows menu
    QMenu *windowsMenu;
    //-------

    //-------
    // Actions
    //! \brief QAction for undoing
    QAction *undoAction;

    //! \brief QAction for redoing
    QAction *redoAction;

    //! \brief QAction to exit the app
    QAction *exitAction;

    //! \brief QAction to save the content of the app
    QAction *saveAction;


    //! \brief QAction to open the relation window
    QAction *openRelations;

    //! \brief QAction to open the history window
    QAction *viewUndoHistory;
    //-------

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------





    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // Important methods for the app :
    // --------------------------------------------------------------------------
    //! Function to load the notes from the saved file
    //! \brief loading function
    void load();

    //! Function to save the notes to an xml
    //! \brief saving function
    void save();
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------





    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // Other stuff
    // --------------------------------------------------------------------------
    //! Boolean for the id autofill form if not already changed
    //! \brief Boolean for the id autofill form
    bool is_idChanged;

    //! \todo add documentation
    explicit PluriNotes(QWidget *parent = 0);

    //! \todo add documentation
    PluriNotes(const PluriNotes& m);

    //! \todo add documentation
    PluriNotes& operator=(const PluriNotes& m);

    //! \todo attributes to store whether there has been data modification or not
    bool dataChanged = false;

    //! \todo add documentation
    NoteEntity& getCurrentNote();
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------












public:

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // Basics and getters
    // --------------------------------------------------------------------------
    //! Implementation of the singleton design pattern : get the only instance
    static PluriNotes& getManager();

    //! \brief Accessor to the ui
    Ui::PluriNotes* getUi() { return ui; }

    //! \brief method to load data into interface
    void loadDataIntoUi();


    //! Getter for the max current nb (id) relations
    unsigned int getMaxRelationId();

    //! Method to get a pointer to the references relation
    Relation* getReferencesRelation();


    //! \todo add documentation
    void setAutoDelete(bool);


    //! Function to check if their has been modification to plurinotes
    bool hasDataChanged() const {return dataChanged;}

    //! Function to say if the data has changed.
    void setDataChanged(bool b);



    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------




    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // Interaction with the content of the class
    // --------------------------------------------------------------------------

    //! \brief Delete note based on its id
    void deleteNote(const QString& id);

    //! \brief Function to know if a note is inside the vector note
    bool isInsideApp(const NoteEntity *note);

    //! Function to move a note element from notes to trash
    void moveToTrash(NoteEntity* noteEl);

    //! Function to move a note element from trash to notes
    void moveBackFromTrash(NoteEntity* noteEl);

    //! \brief Empty trash
    void emptyTrash();

    //! \brief add relation to the vector of relations
    void addRelationToVector(Relation* r);


    //! \brief Function to remove a note
    //! \warning the memory is not fried
    void removeNote(NoteEntity* note);


    //! Method to get all successors of a note
    QSet<NoteEntity*> getAllSuccessorsOf(NoteEntity* note) const;

    //! Method to get all predecessors of a note
    QSet<NoteEntity*> getAllPredecessorsOf(NoteEntity* note) const;
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------



    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // Interaction content/ui
    // --------------------------------------------------------------------------
    //! Function to add a note in the system \n
    //! Returns an "listItemAndPointer*" the should be usefull in somme cases
    listItemAndPointer* addNote(NoteEntity* note);

    //! Function to add an listItemAndPointer* to the list of notes
    void addItemNoteToList(listItemAndPointer* item);



    //! Function to add a NoteEntity to the list of note \n
    //! With creation of a listItemAndPointer*
    listItemAndPointer* addNoteToList(NoteEntity* note);

    //! Function to remove a note from the list
    void removeNoteFromList(NoteEntity* note);

    //! Function to find an item in the list based on the note
    listItemAndPointer* findItemInList(NoteEntity* note);

    //! Function wich removes a listItemAndPointer* from the list\n
    //! it is returned so that it can be stored if we need it
    listItemAndPointer* removeItemNoteFromList(listItemAndPointer* item);

    //! Function to select an item in the list of notes
    void selectItemIntoList(listItemAndPointer* item);


    //--- treeView
    //! Function to add a NoteEntity to the list of note \n
    //! With creation of a listItemAndPointer*
    treeItemNoteAndPointer* addNoteToTree(NoteEntity* note, QTreeWidget* tree);

    //! Function to update trees based on the selected note.
    void updateTrees(NoteEntity* note);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // UI setters/getters
    // --------------------------------------------------------------------------

    //! \brief Set the note title in the UI
    void setNoteTitle(const QString& t);

    //! \brief Get the note title int the UI
    const QString getNoteTitleEdit();


    //! \brief set the date fiel in the UI
    void setNoteDate(const QDateTime& d);


    //-------
    // Article related
    // \todo move to an other class for better POO ?

    //! \brief set the article Content in the UI
    void setArticleContent(const QString& content);

    //! \brief get the article articleContent in the UI
    const QString getArticleContent();

    //! \brief get the article articleDisplayContent in the UI
    const QString getArticleContentEdit();
    //-------



    //-------
    // Task related
    //\todo move to an other class for better POO ?

    //! \todo add documentation
    void setTaskAction(const QString& action);

    //! \todo add documentation
    const QString getTaskAction();

    //! \todo add documentation
    const QString getTaskActionEdit();


    //! \brief Set the task status in the UI
    void setTaskStatus(unsigned int i);

    //! \brief get task status edit from the UI
    unsigned int getTaskStatusEdit();


    //! \brief set task priority in the UI
    void setTaskPriority(unsigned int i);

    //! \brief get Task Priority from thu ui
    unsigned int getTaskPriority();

    //! \brief get Task PriorityEdit from thu ui
    unsigned int getTaskPriorityEdit();


    //! \brief set task deadline in the UI
    void setTaskDeadline(const QDateTime& date);

    //! \brief get the task deadline from the UI
    const QDateTime getTaskDeadline();

    //! \brief get the task deadlineEdit from the UI
    const QDateTime getTaskDeadlineEdit();
    //-------


    //! Before closing we have to execut this
    void closeEvent ( QCloseEvent * event );


    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    void testFunction();


signals:
    public slots:
    //! \brief switch to the new note window.
    void toNewNoteForm();

    //! Method to change stackedWidget to the note display window and adapt fields
    void displayNote(unsigned int n = 0);

    //! \todo Add documentation !!!!
    void saveNote();

    //! \todo Add documentation !!!!
    void deleteNote();

    //! \todo Add documentation !!!!
    void cancelNote();

    //! \todo Add documentation !!!!
    void titleChanged();

    //! \todo Add documentation !!!!
    void idChanged();

    //! Method to change QT fields in the new note form (with type of note in mind)
    void typeChangedForm();

    //! \todo Add documentation !!!!
    void saveApplication();

    //! \todo Add documentation !!!!
    void openRelationsWindow();

    //! \todo Add documentation !!!!
    void noteTextChanged();

    //! \todo Add documentation !!!!
    void saveNewVersion();

    //! \todo Add documentation !!!!
    void noteVersionChanged();

    //! \todo Add documentation !!!!
    void showUndoHistoryWindows();

    //! \brief update selected note when selecting a note in the successors tree
    void updateSelectionFromTreeSuccessors();

    //! \brief update selected note when selecting a note in the predecessors tree
    void updateSelectionFromTreePredecessors();
};




#endif // APPLICATION_H
