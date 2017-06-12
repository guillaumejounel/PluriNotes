/**
\file othertools.h
\date 28/05/2017
\author Florent Chehab, Guillaume Jounel and Félix Boisselier
\brief Contains other class/function implementation
**/


#ifndef OTHERTOOLS_H
#define OTHERTOOLS_H


#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include "relation.h"
#include "notecouple.h"

class NoteEntity;
class Relation;
class NoteCouple;

/**
\class listItemAndPointer
\brief Class herited from QListWidgetItem, to add a point to note

This class is herited from QListWidgetItem in order to add an attribut "notePointer"\n
to each items, so when we click on an item in the list we can directly access the note\n
in the application.
**/

class listItemAndPointer : public QListWidgetItem {
private :
    //! \brief Pointer to a note entity
    NoteEntity* notePointer;
public :
    //! Constructor for the class
    listItemAndPointer(NoteEntity* ptr = nullptr) : notePointer(ptr) {}

    //! Accessor to the added attribute
    NoteEntity* getNotePointer() const {return notePointer;}
};


/**
\class listRelationAndPointer
\brief Class herited from QListWidgetItem, to add a point to a relation

This class is herited from QListWidgetItem in order to add an attribut "relationPointer"\n
to each items, so when we click on an item in the list we can directly access the relation\n
in the application.
**/
class listRelationAndPointer : public QListWidgetItem {
private :
    //! \brief Pointer to a relation
    Relation* relationPointer;
public :
    //! Constructor for the class
    listRelationAndPointer(Relation* ptr = nullptr) : relationPointer(ptr) {}

    //! Accessor to the added attribute
    Relation* getRelationPointer() const {return relationPointer;}
};



/**
\class listCoupleAndPointer
\brief Class herited from QListWidgetItem, to add a point to a couple

This class is herited from QListWidgetItem in order to add an attribut "couplePointer"\n
to each items, so when we click on an item in the list we can directly access the couple\n
in the application.
**/
class listCoupleAndPointer : public QListWidgetItem {
private :
    //! \brief Pointer to a couple
    NoteCouple* couplePointer;
public :
    //! Constructor for the class
    listCoupleAndPointer(NoteCouple* ptr = nullptr) : couplePointer(ptr) {}

    //! Accessor to the added attribute
    NoteCouple* getCouplePointer() const {return couplePointer;}
};



/**
\class listRelationAndPointer
\brief Class herited from QListWidgetItem, to add a point to a relation

This class is herited from QListWidgetItem in order to add an attribut "relationPointer"\n
to each items, so when we click on an item in the list we can directly access the relation\n
in the application.
**/
class treeItemNoteAndPointer : public QTreeWidgetItem {
private :
    //! \brief Pointer to a note entity
    NoteEntity* notePointer;

    bool previouslyExpended;
public :
    //! Constructor for the class
    treeItemNoteAndPointer(NoteEntity* ptr = nullptr) : notePointer(ptr), previouslyExpended(false) {}

    //! Accessor to the added attribute
    NoteEntity* getNotePointer() const {return notePointer;}
    bool hasBeenExpended() const {return previouslyExpended;}
    void setExpensionCalculusStatus(bool status = true) {previouslyExpended = status;}
};



/**
\class coupleAndRelation
\brief Class to be able to store/restore couples in relations
**/
class coupleAndRelation {
private :
    //! \brief couple
    NoteCouple* couplePointer;
    Relation* relationPointer;
public :
    //! Constructor for the class
    coupleAndRelation(NoteCouple* couple, Relation* relation) : couplePointer(couple), relationPointer(relation) {}
    ~coupleAndRelation() {}
    NoteCouple* getCouple() const {return couplePointer;}
    Relation* getRelation() const {return relationPointer;}
};



#endif // OTHERTOOLS_H
