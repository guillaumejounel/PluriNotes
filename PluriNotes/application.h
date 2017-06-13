/**
\file application.h
\date 14/06/2017
\author Florent Chehab, Guillaume Jounel and Félix Boisselier
\brief contains the core application
**/


#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QString>
#include <QScrollArea>
#include <QLineEdit>
#include <QMessageBox>
#include <QVector>

#include <QWidget>

#include <QCloseEvent>


#include "othertools.h"
#include "relation.h"
//#include "relationswindows.h"

class QAction;
class QToolBar;
class QMenu;
class QUndoStack;
class QUndoView;

using namespace std;

class NoteEntity;
class NoteElement;
class listItemAndPointer;
class treeItemNoteAndPointer;
class coupleAndRelation;
class Relation;

namespace Ui {
    class PluriNotes;
}

//! \todo add comment for this line ; I don't understant what it is ! :p
typedef map<QString,NoteElement*>::const_iterator MapIterator;

/**
\class Plurinotes
\brief Main class of the applicatin with the ui for the core application

All the beauty happens here !
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
    unsigned int isDisplayed;

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
    //  Windows
    //! \brief history window
    QUndoView *undoView;

    //! \brief Relation window
    QWidget* relationsView;
    //-------


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
    //! \brief QAction for undoing ctrl+Z
    QAction *undoAction;

    //! \brief QAction for redoing ctrl+maj+z ou ctrl Y
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

    //! \brief attributes to store whether there has been data modification or not
    bool dataChanged = false;


    //! Undostack for the undo/redo process in the app (not concerning relations view)
    QUndoStack *undoStack;

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------












public:
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
    // Basics and getters
    // --------------------------------------------------------------------------
    //! Implementation of the singleton design pattern : get the only instance
    static PluriNotes& getManager();

    //! \brief Accessor to the ui
    Ui::PluriNotes* getUi() { return ui; }

    //! \brief method to load data into interface
    void loadDataIntoUi();

    //! \brief method to load data into interface
    void loadNotesIntoUi();

    //! \brief method to load data into interface
    void loadRelationsIntoUi();

    //! Getter for the max current nb (id) relations
    unsigned int getMaxRelationId();

    //! Method to get a pointer to the references relation
    Relation* getReferencesRelation();

    //! Function to deleted relations that have been temporarly deleted in the relation managment window
    void onRelationsWindowsClose();

    //! \brief getter for the relation view
    QWidget* getRelationView() {return relationsView;}


    //! \todo add documentation
    void setAutoDelete(bool);


    //! Function to check if their has been modification to plurinotes
    bool hasDataChanged() const {return dataChanged;}

    //! Function to say if the data has changed.
    void setDataChanged(bool b);

    //! \todo add documentation
    NoteEntity* getCurrentNote();

    //! \brief Get the type of the current displayed note
    QString getCurrentNoteType();
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


    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // Interaction with the references
    // --------------------------------------------------------------------------
    //! Method to get all successors of a note
    QSet<NoteEntity*> getAllSuccessorsOf(NoteEntity* note) const;

    //! Method to get all predecessors of a note
    QSet<NoteEntity*> getAllPredecessorsOf(NoteEntity* note) const;

    //! Method to get all predecessors of a note
    //! \todo pas propre !
    QVector<NoteEntity*> getNotesVector() const {return notes;}

    //! Method to get all references of a List of notenote
    QSet<NoteEntity*> getAllPredecessorsOf(QList<NoteEntity*> noteList) const;

    //! Method to get all references of a note
    QSet<NoteEntity*> getAllReferencesOf(NoteEntity* note) const;


    //! List of active ID for referencing
    QStringList getActiveReferences()const ;


    //! References check when adding a note or a version
    bool refencesCheck(const NoteElement*noteEl, NoteEntity *note, QString id);

    //! \brief add References in the references vector
    void addReferences(NoteEntity* note, const QStringList& idList);

    //! \brief add References in the references vector
    void removeReferencesWithOrigin(NoteEntity* note);
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------



    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // Interaction content/ui
    // --------------------------------------------------------------------------

    //! \brief Check if an id is available
    bool isIdAvailable(const QString& id) const;

    //! \brief return the note having this id
    NoteEntity* getNoteById(const QString& id);

    //! Function to add a note in the system \n
    //! Returns an "listItemAndPointer*" the should be usefull in somme cases
    listItemAndPointer* addNote(NoteEntity& note, QListWidget *list);

    //! Function to add an listItemAndPointer* to the list of notes
    void addItemNoteToList(listItemAndPointer* item, QListWidget *list);



    //! Function to add a NoteEntity to the list of note \n
    //! With creation of a listItemAndPointer*
    listItemAndPointer* addNoteToList(NoteEntity* note, QListWidget* list);

    //! Function to remove a note from the list
    void removeNoteFromList(NoteEntity* note, QListWidget* list);

    //! Function to find an item in the list based on the note
    listItemAndPointer* findItemInList(NoteEntity* note, QListWidget* list);

    //! Function wich removes a listItemAndPointer* from the list\n
    //! it is returned so that it can be stored if we need it
    listItemAndPointer* removeItemNoteFromList(listItemAndPointer* item, QListWidget* list);

    //! Function to select an item in the list of notes
    void selectItemIntoList(listItemAndPointer* item, QListWidget* list);

    //! \brief Update the note count of each panel of the notBox
    void noteCountUpdate();

    //--- treeView
    //! Function to add a NoteEntity to the list of note \n
    //! With creation of a listItemAndPointer*
    treeItemNoteAndPointer* addNoteToTree(NoteEntity* note, QTreeWidget* tree);

    //! function to add the child elements
    void addNoteChildToTree(treeItemNoteAndPointer* item, QTreeWidget* tree);

    //! function to add the child of an item
    void addNoteChildrenToItem(QTreeWidgetItem* item, QTreeWidget* tree);

    //! Function to update trees based on the selected note.
    void updateTrees(NoteEntity* note);

    //! Function to redirect selection of a note
    void superRedirecteEasy(NoteEntity* note);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // UI setters/getters
    // --------------------------------------------------------------------------


    //! \brief Get the list of active notes in the UI
    QListWidget* getListActiveNotes() const;

    //! \brief Get the list of archived notes in the UI
    QListWidget* getListArchived() const;

    //! \brief Get the list of notes in trash in the UI
    QListWidget* getListTrash() const;

    //! \brief Get the list of tasks in the UI
    QListWidget* getListTasks() const;


    //! Method to block or activate element interaction
    void setInteractivity(bool b, unsigned int type = 0);

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
    void idChanged(bool fromTitle = false);

    //! Method to change QT fields in the new note form (with type of note in mind)
    void typeChangedForm();

    //! \todo Add documentation !!!!
    void saveApplication();

    //! \todo Add documentation !!!!
    void openRelationsWindow();

    //! \todo Add documentation !!!!
    void noteTextChanged();//issue is for some preventionwith restoring notes

    //! \todo Add documentation !!!!
    void saveNewVersion();

    //! \todo Add documentation !!!!
    void noteVersionChanged();

    //! \brief Let the user select a file on his computer so as to attached it to a document
    void selectDocumentFile();

    //! \brief Open the file folder of current viewed document
    void openDocumentFolder();

    //! \brief Open the file of current viewed document
    void openDocumentFile();

    //! \todo Add documentation !!!!
    void showUndoHistoryWindows();

    //! \brief update selected note when selecting a note in the successors tree
    void updateSelectionFromTreeSuccessors();

    //! \brief update selected note when selecting a note in the predecessors tree
    void updateSelectionFromTreePredecessors();

    //! \brief add child in Successors tree to the item
    void updateAddChildTreeSuccessors(QTreeWidgetItem* item);

    //! \brief add child in Predecessors tree to the item
    void updateAddChildTreePredecessors(QTreeWidgetItem* item);

    //! \brief animation of the retracable area
    void retracteOrUnretracteArborescence();

    //! \brief empty Trash slot
    void emptyTrashSlot(bool out = false);

    //! \brief empty restoreTrash slot
    void restoreTrashSlot();

    //! \brief empty restoreTrash slot
    void restoreArchiveSlot();

    //! \brief check archived slot
    void checkArchiveSlot();

    //! \brief displayTrashMessage
    void showTrashSlot(int n = -1);

    //! \brief method to filter notes into interface
    void filterDataIntoUi();

};




#endif // APPLICATION_H
