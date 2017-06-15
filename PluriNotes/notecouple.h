/**
\file notecouple.h
\date 14/06/2017
\author Florent Chehab, Guillaume Jounel and Félix Boisselier
\brief Contains the class declaration for the note Couple
**/



#ifndef NOTECOUPLE_H
#define NOTECOUPLE_H

#include "noteentity.h"
#include <QString>
#include <ostream>

class NoteEntity;


/**
\class NoteCouple
\brief Class for couples for relations
**/
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
    //! @param s label for the couple
    //! @param x note x
    //! @param y note y
    NoteCouple(QString& s, NoteEntity* x, NoteEntity* y):label(s), x(x),y(y) {}

    //! \brief copy constructor
    //! @param couple the note couple to copy
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
    //! @param c note couple to compare to
    bool operator==(const NoteCouple& c)const;

    //! Check if note is equal to x
    //! @param note Note to check
    bool isEqualX(const NoteEntity* note) const;

    //! Check if note is equal to y
    //! @param note Note to check
    bool isEqualY(const NoteEntity* note) const;

    //! \brief Metod to know if a couple contains a note
    //! @param note Note to check
    bool contains(const NoteEntity* note) const;


    //! \brief setter for the label
    //! @param l label
    void setLabel(QString& l) {label = l;}

    //! \brief return successor
    //! If (note,y) then y is a successor of note
    //! If (x,note) and oriented = false then x is successor of note
    //! @param note the note
    //! @param oriented Is the relation storing the couple oriented
    NoteEntity* successor(const NoteEntity* note, bool oriented = true) const;

    //! \brief return predecessor
    //! If (x,note) then y is a predecessor of note
    //! If (note,y) and oriented = false then y is a predecessor of note
    //! @param note the note
    //! @param oriented Is the relation storing the couple oriented
    //! @param outOfArchives default false ; do we have to check in archives ?
    NoteEntity* predecessor(const NoteEntity* note, bool oriented = true,bool outOfArchives = false) const;

    //! \brief output a nice "(x,y)"
    QString print() const;

    //! \brief Write to xml file
    //! @param stream the xlm stream
    void saveToXML(QXmlStreamWriter& stream) const;


    //! \brief Load from xml file
    //! @param stream the xlm stream
    static NoteCouple* loadFromXML(QXmlStreamReader& stream);
};

#endif // NOTECOUPLE_H
