/**
\file notecouple.h
\date 08/06/2017
\author Florent Chehab, Guillaume Jounel and Félix Boisselier
\brief Contains the class declaration for the note Couple
**/



#ifndef NOTECOUPLE_H
#define NOTECOUPLE_H

#include "noteentity.h"
#include <QString>

class NoteCouple{
private:
    //! \brief label for the couple
    QString label;

     //! \brief pointer to the first NoteEntity of the couple
    NoteEntity* x;

    //! \brief pointer to the second NoteEntity of the couple
    NoteEntity* y;

public:
    //! \brief Constructor
    NoteCouple(QString& s, NoteEntity* x, NoteEntity* y):label(s), x(x),y(y) {}

    //! Constructor with no argument
    NoteCouple(){}

    //! \brief Accessor to x
    NoteEntity* getX() const {return x;}

    //! \brief Accessor to y
    NoteEntity* getY() const {return y;}

    //! \brief getter for the label
    const QString getLabel() const {return label;}

    //! comparaison of note couple
    bool operator==(const NoteCouple& c)const;

    //! Check if note is equal to x
    bool isEqualX(const NoteEntity* note) const;

    //! Check if note is equal to y
    bool isEqualY(const NoteEntity* note) const;


    //! \brief setter for the label
    void setLabel(QString& l) {label = l;}

    //! \brief return successor
    //! If (note,y) then y is a successor of note
    //! If (x,note) and oriented = false then x is successor of note
    NoteEntity* successor(NoteEntity* note, bool oriented = true) const;

    //! \brief return predecessor
    //! If (x,note) then y is a predecessor of note
    //! If (note,y) and oriented = false then y is a predecessor of note
    NoteEntity* predecessor(NoteEntity* note, bool oriented = true) const;
};

#endif // NOTECOUPLE_H
