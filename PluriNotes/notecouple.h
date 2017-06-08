/**
\file notecouple.h
\date 08/06/2017
\author Florent Chehab, Guillaume Jounel and Félix Boisselier
\brief Contains the class declaration for the note Couple
**/



#ifndef NOTECOUPLE_H
#define NOTECOUPLE_H

#include "noteentity.h"

class NoteCouple{
private:
     //! \brief pointer to the first NoteEntity of the couple
    NoteEntity* x;

    //! \brief pointer to the second NoteEntity of the couple
    NoteEntity* y;

    //! Boolean to know if we actually have to consider both couple (x,y) and (y,x)
    bool oriented;

public:
    //! \brief Constructor
    NoteCouple(NoteEntity* x, NoteEntity* y, bool b = true):x(x),y(y), oriented(b) {}

    //! Constructor with no argument
    NoteCouple(){}

    //! \brief Accessor to x
    NoteEntity* getX() const {return x;}

    //! \brief Accessor to y
    NoteEntity* getY() const {return y;}

    //! \brief Accessor to oriented
    bool isOriented() const {return oriented;}

    //! setter for the orientation
    void setOriented(bool b) {oriented = b;}

    //! comparaison of note couple
    bool operator==(const NoteCouple& c)const;
};

#endif // NOTECOUPLE_H
