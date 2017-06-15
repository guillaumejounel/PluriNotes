/**
\file application.h
\date 14/06/2017
\author Florent Chehab, Guillaume Jounel and Félix Boisselier
\brief contains the core application
**/


#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QScrollArea>
#include <QLineEdit>
#include <QMessageBox>
#include <QWidget>
#include <QCloseEvent>

#include "othertools.h"
#include "relation.h"

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

    //!\brief Destructor of the class
    //! Implementation of the singleton design pattern, the destructor has to be private
    ~PluriNotes();

    //! Implementation of the singleton design pattern
    //! \brief Pointer to the unique class instanciation
    static PluriNotes* instanceUnique;

    //! Vector containing all the active notes in the application
    //! \brief Vector containing the active notes
    QVector<NoteEntity*> notes;

    //! Vector containing all the notes sent to the trash
    //! \brief Vector containing the trashed notes
    QVector<NoteEntity*> trash;

    //! \brief Vector containing all Relations of the application
    QVector<Relation*> relations;


    //! \brief tricky attributes to store state data
    //! if == 0 the note is note displayed
    //! if == 1 the note is displayed
    //! if == 2 the note is displayed after a restore
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

    //! \brief cf cute
    explicit PluriNotes(QWidget *parent = 0);

    //! \brief copy constructor
    //! not available
    PluriNotes(const PluriNotes& m);

    //! \brief Affectation
    //! Not available
    PluriNotes& operator=(const PluriNotes& m);

    //! \brief attributes to store whether there has been data modification or not
    bool dataChanged = false;


    //! \brief a simple undoStack
    //! Undostack for the undo/redo process in the app (not concerning relations view)
    QUndoStack *undoStack;

    //! \brief Boolean to automatically empty the trash at exit
    //! False by default
    bool autoEmptyTrash = false;

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
    //! \brief getter to the manager
    static PluriNotes& getManager();

    //! \brief Accessor to the ui
    Ui::PluriNotes* getUi() { return ui; }

    //! \brief method to load data into interface
    void loadDataIntoUi();

    //! \brief method to load data into interface
    void loadNotesIntoUi();

    //! \brief method to load data into interface
    void loadRelationsIntoUi();

    //! \brief Getter for the max current nb (id) relations
    unsigned int getMaxRelationId();

    //! \brief Method to get a pointer to the references relation
    Relation* getReferencesRelation();

    //! \brief What happens when we close the relation window
    //! Function to deleted relations that have been temporarly deleted in the relation managment window
    void onRelationsWindowsClose();

    //! \brief getter for the relation view
    QWidget* getRelationView() {return relationsView;}


    //! \brief Function to check if their has been modification to plurinotes
    bool hasDataChanged() const {return dataChanged;}

    //! \brief Function to say if the data has changed.
    //! @param b New status for dataChanged
    void setDataChanged(bool b);

    //! \brief get the current selected note in the app
    NoteEntity* getCurrentNote();

    //! \brief Get the type of the current displayed note
    QString getCurrentNoteType();


    //! \brief Getter for the value of autoEmptyTrash
    bool getAutoEmptyTrash() {return autoEmptyTrash;}

    //! \brief Setter for the value of auto empty trash
    //! @param b New Value
    void setAutoEmptyTrash(bool b){ autoEmptyTrash = b;}
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------




    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // Interaction with the content of the class
    // --------------------------------------------------------------------------

    //! \brief Delete note based on its id
    //! @param id The id of the note we want to delete
    void deleteNote(const QString& id);

    //! \brief Function to know if a note is inside the vector note
    //! @param note the note we ware looking for
    bool isInsideApp(const NoteEntity *note);

    //! \brief Function to move a note element from notes to trash
    //! @param noteEl the note we want to move
    void moveToTrash(NoteEntity* noteEl);

    //! \brief Function to move a note element from trash to notes
    //! @param noteEl the note we want to move
    void moveBackFromTrash(NoteEntity* noteEl);

    //! \brief add relation to the vector of relations
    //! @param r relation we want to add to the app
    void addRelationToVector(Relation* r);

    //! \brief Function to remove a note
    //! @param note the note we want to remove
    //! The memory is not freed, but it is fine
    void removeNote(NoteEntity* note);

    //! \brief Accessor to the vector of note
    const QVector<NoteEntity*>* getNotesVector() const {return &notes;}
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // Interaction with the references
    // --------------------------------------------------------------------------
    //! \brief Method to get all successors of a note
    //! @param note the note we are interested in
    QSet<NoteEntity*> getAllSuccessorsOf(NoteEntity* note) const;

    //! \brief Method to get all predecessors of a note
    //! @param note the note we are interested in
    QSet<NoteEntity*> getAllPredecessorsOf(NoteEntity* note) const;

    //! \brief Method to get all references of a List of note
    //! @param noteList the list of notes we are interested in
    QSet<NoteEntity*> getAllPredecessorsOf(QList<NoteEntity*> noteList) const;

    //! Method to get all references of a note
    //! @param note the note we are interested in
    QSet<NoteEntity*> getAllReferencesOf(NoteEntity* note) const;


    //! \brief getter to all the active ids in the app
    QStringList getActiveReferences()const ;


    //! \brief References check when adding a note or a version
    //! @param noteEl the noteElement we have to check (sometimes we need it)
    //! @param note related note to noteElement
    //! @param id of the note ; might be uselless
    bool refencesCheck(const NoteElement*noteEl, NoteEntity *note, QString id) const;

    //! \brief add References in the references relation
    //! @param note The note concerned (the source of references)
    //! @param idList the id contained in the new note
    //! Sommetimes we can't deduce the list of id from the note because it is not updated yet
    void addReferences(NoteEntity* note, const QStringList& idList);

    //! \brief remove References of a note in the references vector
    //! @param note The note concerned
    void removeReferencesWithOrigin(NoteEntity* note);
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------



    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // Interaction content/ui
    // --------------------------------------------------------------------------

    //! \brief Check if an id is available
    //! @param id the id we have to check
    bool isIdAvailable(const QString& id) const;

    //! \brief return the note having this id
    //! @param id id of the note
    NoteEntity* getNoteById(const QString& id) const;

    //! \brief Function to add a note in the system
    //! Returns an "listItemAndPointer*" the should be usefull in somme cases
    //! @param note The note concerned
    //! @param list Where have to add the note
    listItemAndPointer* addNote(NoteEntity& note, QListWidget *list);

    //! \brief Function to add an listItemAndPointer* to the list of notes
    //! @param item The list item with the note
    //! @param list Where we have to put the item
    void addItemNoteToList(listItemAndPointer* item, QListWidget *list);



    //! \brief Function to add a NoteEntity to the list of note
    //! With creation of a listItemAndPointer*
    //! @param note The note we want to add
    //! @param list Where we have to put the note
    listItemAndPointer* addNoteToList(NoteEntity* note, QListWidget* list);

    //! \brief Function to remove a note from the list
    //! @param note The note we want to remove
    //! @param list Where should be the note
    void removeNoteFromList(NoteEntity* note, QListWidget* list);

    //! \brief Function to find an item in the list based on the note
    //! @param note The note we want to find
    //! @param list Where should be the note
    listItemAndPointer* findItemInList(NoteEntity* note, QListWidget* list) const;

    //! \brief Function wich removes a listItemAndPointer* from the list
    //! it is returned so that it can be stored if we need it
    //! @param item the item we want to remove
    //! @param list the list where the item is
    listItemAndPointer* removeItemNoteFromList(listItemAndPointer* item, QListWidget* list);

    //! \brief Function to select an item in the list of notes
    //! @param item the item we want to select
    //! @param list the list where the item is
    void selectItemIntoList(listItemAndPointer* item, QListWidget* list) const;

    //! \brief Update the note count of each panel of the notBox
    void noteCountUpdate();



    //--- treeView
    //! \brief Function to add a NoteEntity to the tree of note
    //! With creation of a listItemAndPointer*
    //! @param note the note
    //! @param tree the tree we want to add the note
    treeItemNoteAndPointer* addNoteToTree(NoteEntity* note, QTreeWidget* tree);

    //! \brief function to add the child elements of an element in a tree
    //! @param item the item
    //! @param tree the tree concerned
    void addNoteChildToTree(treeItemNoteAndPointer* item, QTreeWidget* tree);

    //! \brief function to add the children of an item
    //! @param item the item
    //! @param tree the tree concerned
    void addNoteChildrenToItem(QTreeWidgetItem* item, QTreeWidget* tree);

    //! \brief Function to update trees based on the selected note.
    //! @param note the note we want to update the trees with
    void updateTrees(NoteEntity* note);

    //! \brief Function to redirect selection of a note
    //! it is to select a note in the right panel of the ui
    //! @param note the note we want to select
    void superRedirecteEasy(NoteEntity* note) const;

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


    //! \brief Method to block or activate element interaction
    //! @param b the new status of the widgets
    //! @param type optionnal parameter for activating/blocked other elements
    void setInteractivity(bool b, unsigned int type = 0);

    //! \brief Before closing we have to execute this
    //! @param event the event...
    void closeEvent ( QCloseEvent * event );

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------


signals:
    public slots:
    //! \brief switch to the new note window.
    void toNewNoteForm();

    //! \brief Method to change stackedWidget to the note display window and adapt fields
    //! @param n The version (-1) we want to visualize
    void displayNote(unsigned int n = 0);

    //! \brief Method called when clicking on the save button
    void saveNote();

    //! \brief Method called when clicking on the delete button
    void deleteNote();

    //! \brief Method called when clicking on the cancel button
    void cancelNote();

    //! \brief automatic Id generator
    void titleChanged();

    //! \brief Method to stop automatic modification of the id if has been manually changed
    //! @param fromTitle  Block the change of id if it is not from title generation
    void idChanged(bool fromTitle = false);

    //! \brief Method to change QT fields in the new note form
    //! (with type of note in mind)
    //! When adding a note type you have to modify this function
    void typeChangedForm();

    //! \brief Method called when saving the app (in the menu or via action)
    void saveApplication();

    //! \brief Method called when clicking on open relations menu
    void openRelationsWindow();

    //! \brief if fields are changed we enable some aspect of the ui
    void noteTextChanged();

    //! \brief Method called when clicking on save new version
    void saveNewVersion();

    //! \brief Method called when an other version is selected
    void noteVersionChanged();

    //! \brief Let the user select a file on his computer so as to attached it to a document
    void selectDocumentFile();

    //! \brief Open the file folder of current viewed document
    void openDocumentFolder();

    //! \brief Open the file of current viewed document
    void openDocumentFile();

    //! \brief Method called when clicking on open history menu
    void showUndoHistoryWindows();


    //! \brief update selected note when selecting a note in the successors tree
    void updateSelectionFromTreeSuccessors();

    //! \brief update selected note when selecting a note in the predecessors tree
    void updateSelectionFromTreePredecessors();


    //! \brief add child in Successors tree to the item
    //! @param item the expanded item
    void updateAddChildTreeSuccessors(QTreeWidgetItem* item);

    //! \brief add child in Predecessors tree to the item
    //! @param item the expanded item
    void updateAddChildTreePredecessors(QTreeWidgetItem* item);

    //! \brief animation of the retracable area
    void retracteOrUnretracteArborescence();

    //! \brief Method called when clicking on empty trash
    //! @param out by default it is false but when exiting the app we call this funciton with out = true \n
    //! so we don't have to show the message
    void emptyTrashSlot(bool out = false);


    //! \brief Method called when clicking on restore trash
    //! It is used to restore the selected element
    void restoreTrashSlot();

    //! \brief Method called when clicking on restore archives
    void restoreArchiveSlot();

    //! \brief Method called to check the element status in archives
    void checkArchiveSlot();

    //! \brief displayTrashMessage
    void showTrashSlot(int n = -1);

    //! \brief method to filter notes into interface
    void filterDataIntoUi();

    //! \brief slot for autoEmpty
    void setAutoEmptySlot();

};




#endif // APPLICATION_H
