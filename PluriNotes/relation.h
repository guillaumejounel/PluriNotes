/**
\file notecouple.h
\date 08/06/2017
\author Florent Chehab, Guillaume Jounel and Félix Boisselier
\brief Contains the class declaration for the note Couple
**/



#ifndef RELATION_H
#define RELATION_H

#include "notecouple.h"
#include <QString>
#include <QVector>
#include <QSet>

class NoteCouple;
class NoteEntity;
class Relation;

class Relation{
private:
    //! \brief title of the relation
    QString title;

    //! \brief description of the relation
    QString description;

    //! \brief content of the relation
    QVector<NoteCouple> content;

    //! Boolean to know if we actually have to consider both couple (x,y) and (y,x)
    bool oriented;

    //! Boolean to know is this relations is the reference one
    bool references;

    //! Number of the relation to better identify it
    unsigned int number;



public:
    //! \brief constructor of the class
    //! Default orientation is oriented
    //! Default is NOT a references ; we only need one !
    Relation(QString& t, QString& d, bool isOriented);
    Relation(QString& t, QString& d, bool isOriented, bool isReferences);

    Relation(){}

    //! \brief getter for the title
    const QString getTitle() const {return title;}

    //! \brief getter for the Description
    const QString getDescription() const {return description;}

    //! \brief getter for the content
    QVector<NoteCouple> getContent() const {return content;}

    //! \brief getter for the number
    unsigned int getNumber() const {return number;}

    //! Accessor to References
    bool isReferences() const {return references;}

    //! \brief Accessor to oriented
    bool isOriented() const {return oriented;}

    //! setter for the orientation
    void setOriented(bool b) {oriented = b;}



    //! \brief setter for the title
    void setTitle(const QString& t) {title = t;}

    //! \brief setter for the description
    void setDescription(const QString& d) {description = d;}



    //! Method to know if a couple is already inside the relation
    bool isInside(NoteEntity* note1, NoteEntity* note2);

    //! Method to add a note couple to the relation
    void addCouple(const NoteCouple& c);

    //! Method to remove a note couple to the relation
    void removeCouple(const NoteCouple& c);


    //! Method to get successors of a note in a relation
    //! A QSet is used to make sure we don't have twice the same note...
    QSet<NoteEntity*> successorsOf(NoteEntity* note) const;

    //! Method to get successors of a note in a relation
    //! A QSet is used to make sure we don't have twice the same note...
    QSet<NoteEntity*> predecessorsOf(NoteEntity* note) const;
};


#endif // RELATION_H
