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


class Relation{
private:
    //! \brief title of the relation
    QString title;

    //! \brief label associated with the relation
    QString label;

    //! \brief description of the relation
    QString description;

    //! \brief content of the relation
    QVector<NoteCouple> content;

public:
    //! \brief constructor of the class
    Relation(QString& l, QString& t, QString& d) : title(t), label(l), description(d){}
    Relation(){}

    //! \brief getter for the label
    const QString getLabel() const {return label;}

    //! \brief getter for the title
    const QString getTitle() const {return title;}

    //! \brief getter for the Description
    const QString getDescription() const {return description;}

    //! \brief getter for the content
    QVector<NoteCouple> getContent() const {return content;}



    //! \brief setter for the title
    void setTitle(const QString& t) {title = t;}

    //! \brief setter for the description
    void setDescription(const QString& d) {description = d;}


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