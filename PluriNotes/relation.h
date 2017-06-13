/**
\file notecouple.h
\date 08/06/2017
\author Florent Chehab, Guillaume Jounel and Félix Boisselier
\brief Contains the class declaration for the note Couple
**/



#ifndef RELATION_H
#define RELATION_H

#include "notecouple.h"
#include "othertools.h"
#include <QString>
#include <QVector>
#include <QSet>


class NoteCouple;
class NoteEntity;
class Relation;
class coupleAndRelation;

/**
\class Relation
\brief The object storing and managing note couples !

\todo undo/redo on couple deletion
**/
class Relation{
private:
    //! \brief title of the relation
    QString title;

    //! \brief description of the relation
    QString description;

    //! \brief content of the relation
    QVector<NoteCouple*> content;

    //! \brief a simple attribute to know if the relation has been deleted
    bool deleted;

    //! Boolean to know if we actually have to consider both couple (x,y) and (y,x)
    bool oriented;

    //! Boolean to know is this relations is the reference one (there must be only one)
    bool references;

    //! Number of the relation to better identify it
    unsigned int number;



public:
    //! \brief constructor of the class
    //! Default orientation is oriented
    //! Default is NOT a references ; we only need one !
    Relation(QString& t, QString& d, bool isOriented);

    //! this constructor shouldn't be used in the app (or at least once)
    Relation(QString& title, QString& description, bool isOriented, bool isReferences, bool deleted = false, unsigned int number = 0);

    //! Simple constructor for creating vertor purposes
    Relation() {}

    //! \brief destructor of the class
    //! Redefinition of the destructor to prevent memoryleaks
    ~Relation();



    //! \brief getter for the title
    const QString getTitle() const {return title;}

    //! \brief getter for the Description
    const QString getDescription() const {return description;}

    //! \brief setter for the title
    void setTitle(const QString& t) {title = t;}

    //! \brief setter for the description
    void setDescription(const QString& d) {description = d;}



    //! \brief getter for the content ???
    //! Pas très propre... \todo replace by an iterator !
    QVector<NoteCouple*> getContent() const {return content;}

    //! \brief getter for the number of the relation
    unsigned int getNumber() const {return number;}

    //! Accessor to know if the relation is the references one
    bool isReferences() const {return references;}

    //! \brief Accessor to oriented attribute
    bool isOriented() const {return oriented;}

    //! setter for the orientation
    void setOriented(bool b) {oriented = b;}


    //! \brief setter for the state of the relation
    void setDeleted(bool b) {deleted = b;}

    //! \brief getter for the state of the relation
    bool isDeleted() const {return deleted;}






    //! Method to know if a couple is already inside the relation
    bool isInside(NoteEntity* note1, NoteEntity* note2) const;

    //! Method to know if a note is inside
    bool isInside(NoteEntity* note) const;

    //! oberload for use with a note couple directly
    bool isInside(const NoteCouple* c) const;


    //! Method to add a note couple to the relation
    bool addCouple(const NoteCouple* c);


    //! Method to remove a note couple to the relation
    void removeCouple(const NoteCouple* c);

    //! Method to remove a list of note from the relation
    void removeCouple(const QList<NoteCouple*> coupleList);

    //! Method to remove all couples that contains a note
    void removeCoupleWithNote(const NoteEntity* note);


    //! Method to remove all couples with predecessor :     //only for oriented !
    void removeCoupleWithNotePredecessor(const NoteEntity* note);

    //! Method to remove all couples that contains one of the note from the list
    void removeCoupleWithNote(const QList<NoteEntity*> noteList);


    //! Method to get all the predecessors of a note in a relation
    //! A QSet is used to make sure we don't have twice the same note...
    QSet<NoteEntity*> successorsOf(const NoteEntity* note) const;

    //! Method to get all the predecessors of a note in a relation
    //! A QSet is used to make sure we don't have twice the same note...
    //! For obbious reason we want to be able not to take into account predecessors that are already in the trash or archived
    QSet<NoteEntity*> predecessorsOf(const NoteEntity* note, bool outOfArchives = false) const;

    //! A method to know if a note has Predecessors in the relation
    //! For the same reason as for "predecessorsOf" we my want not to look into the trash and archives
    bool hasPredecessors(const NoteEntity *note, bool outOfArchives = false) const;



    //! Method to save the relation and its content in the xml file
    void saveToXML(QXmlStreamWriter& stream) const;

    //! Method to load the relations from the XML file
    static Relation* loadFromXML(QXmlStreamReader& stream);
};


#endif // RELATION_H
