/**
\file relationswindows.h
\date 14/06/2017
\author Florent Chehab, Guillaume Jounel and Félix Boisselier
\brief contains the relations windows management definition
**/


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

/**
\class relationsWindows
\brief Relation manager window
**/
class relationsWindows : public QMainWindow
{
    Q_OBJECT

private:
    //! \brief pointer to the ui of the window
    Ui::relationsWindows *ui;

    //! \brief destructor of the class
    ~relationsWindows();


    Relation* getCurrentRelation();


    //! \brief history window
    QUndoView *undoView;

    //! \brief edit menu
    QMenu *editMenu;

    //! \brief windows menu
    QMenu *windowsMenu;

    //! Undostack for the undo/redo process in the window
    QUndoStack *undoStack;


    //-------
    // Actions
    //! \brief QAction for exiting window
    QAction* exitAction;

    //! \brief QAction for undoing
    QAction *undoAction;

    //! \brief QAction for redoing
    QAction *redoAction;

    //! \brief QAction to open the history window
    QAction *viewUndoHistory;


public:
    //! \brief CF QT
    //! @param parent parent widget
    explicit relationsWindows(QWidget *parent = 0);

    //! \brief Function to add an listRelationAndPointer* to the list of relation
    //! @param item item to add in the list
    void addItemRelationToList(listRelationAndPointer* item);

    //! \brief Function to add an listCoupleAndPointer* to the list of couple
    //! @param item item couple to add to the list
    void addItemCoupleToList(listCoupleAndPointer *item);

    //! \brief Function to add a Relation to the list of Relations in the UI
    //! With creation of a listRelationAndPointer*
    //! @param rel relation to add in the list
    listRelationAndPointer* addRelationToList(Relation *rel);

    //! \brief Function to remove a Relation from the list a relation
    //! @param rel relation to remove from the list
    void removeRelationFromList(Relation *rel);

    //! \brief Function to add a Couple to the list of Couple in the UI
    //! With creation of a listCoupleAndPointer*
    //! @param couple couple to add to the list
    listCoupleAndPointer* addCoupleToList(NoteCouple *couple);

    //! \brief Function to populate the comboboxes of NoteEntities in the UI
    void addNoteEntityToComboBoxes();

    //! \brief Before closing
    //! @param event event...
    void closeEvent ( QCloseEvent * event );

    //! \brief After showing
    //! @param event event...
    void showEvent ( QShowEvent * event );

    //! \brief Method to change multiple widget state
    //! @param b state of the widget after function is called
    //! @param level different widget that can be changed based on the level
    void restrictInteractivity(bool b, unsigned int level = 0);

    //! \brief method to display a specific relation
    //! @param rel relation to display
    void displayRelation(Relation* rel);

signals:
    public slots:

    //! \brief Short function to be called before closing the window
    void beforeClose();

    //! \brief switch to the form for a new relation
    void toNewRelationForm();

    //! \brief display a relaiton when selected in the list
    void displayRelation();

    //! \brief Called when we click on add relation button
    void addRelation();

    //! \brief Called when we click on delete relation button
    void removeRelation();

    //! \brief Called when we click on add couple button
    void addCouple();

    //! \brief Called when we click on add change couple label
    void changeCoupleLabel();

    //! \brief Called when we click on delete couple button
    void deleteCouple();

    //! \brief to show the undo history
    void showUndoHistoryWindows();

    //! \brief called when we change the type of orientation for a relation
    void orientationChanged(int choice);
};

#endif // RELATIONSWINDOWS_H
