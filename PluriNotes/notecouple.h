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
#include <ostream>

class NoteEntity;

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

    //! \brief copy constructor
    NoteCouple(const NoteCouple& couple):label(couple.getLabel()), x(couple.getX()),y(couple.getY()) {}

    //! Constructor with no argument
    NoteCouple() {}

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

    //! \brief Metod to know if a couple contains a note
    bool contains(const NoteEntity* note) const;


    //! \brief setter for the label
    void setLabel(QString& l) {label = l;}

    //! \brief return successor
    //! If (note,y) then y is a successor of note
    //! If (x,note) and oriented = false then x is successor of note
    NoteEntity* successor(const NoteEntity* note, bool oriented = true) const;

    //! \brief return predecessor
    //! If (x,note) then y is a predecessor of note
    //! If (note,y) and oriented = false then y is a predecessor of note
    NoteEntity* predecessor(const NoteEntity* note, bool oriented = true,bool outOfArchives = false) const;

    //! for easier debug
    QString print() const;

    void saveToXML(QXmlStreamWriter& stream) const;
};

#endif // NOTECOUPLE_H
