#ifndef RELATIONSWINDOWS_H
#define RELATIONSWINDOWS_H

#include <QMainWindow>
#include <QInputDialog>
#include "othertools.h"


#include <QUndoStack>
#include <QUndoView>

class QUndoView;
class QUndoStack;


namespace Ui {
class relationsWindows;
}

class Relation;

class relationsWindows : public QMainWindow
{
    Q_OBJECT

private:

    Ui::relationsWindows *ui;

    ~relationsWindows();

    QAction* exitAction;

    Relation* getCurrentRelation();


    //! \brief history window
    QUndoView *undoView;

    //! \brief edit menu
    QMenu *editMenu;

    //! \brief windows menu
    QMenu *windowsMenu;

    //! Undostack for the undo/redo process in the app
    QUndoStack *undoStack;


    //-------
    // Actions
    //! \brief QAction for undoing
    QAction *undoAction;

    //! \brief QAction for redoing
    QAction *redoAction;

    //! \brief QAction to open the history window
    QAction *viewUndoHistory;


public:
    explicit relationsWindows(QWidget *parent = 0);

    //! Function to add an listRelationAndPointer* to the list of relation
    void addItemRelationToList(listRelationAndPointer* item);

    //! Function to add an listCoupleAndPointer* to the list of couple
    void addItemCoupleToList(listCoupleAndPointer *item);

    //! Function to add a Relation to the list of Relations in the UI \n
    //! With creation of a listRelationAndPointer*
    listRelationAndPointer* addRelationToList(Relation *rel);

    //! Function to remove a Relation from the list a relation\n
    void removeRelationFromList(Relation *rel);

    //! Function to add a Couple to the list of Couple in the UI \n
    //! With creation of a listCoupleAndPointer*
    listCoupleAndPointer* addCoupleToList(NoteCouple *couple);

    //! Function to populate the comboboxes of NoteEntities in the UI \n
    void addNoteEntityToComboBoxes();

    //! Before closing
    void closeEvent ( QCloseEvent * event );

    //! After showing
    void showEvent ( QShowEvent * event );

    //! Method to change multiple widget state
    void restrictInteractivity(bool b, unsigned int level = 0);

    //! method to display a specific relation
    void displayRelation(Relation* rel);

signals:
    public slots:
    //! Short function to be called before closing the window
    void beforeClose();
    void toNewRelationForm();

    void displayRelation();

    //! \brief add relation slot
    void addRelation();

    //! \brief remove relation slot
    void removeRelation();


    void addCouple();

    void changeCoupleLabel();
    void deleteCouple();

    //! \todo to show the undo history
    void showUndoHistoryWindows();
};

#endif // RELATIONSWINDOWS_H
