/**
\file notetemplate.h
\date 14/06/2017
\author Florent Chehab, Guillaume Jounel and Félix Boisselier
\brief contains the BaseNoteType template and a macro defining the beginning of each derived class (note types)
**/

#ifndef NOTETEMPLATE_H
#define NOTETEMPLATE_H

#include "noteelement.h"

class NoteElement;

/**
\class BaseNoteType
\brief Template class herited from NoteElement, aimed to register each note type

This class is herited from NoteElement and is aimed to register each note type into\n
the static NoteTypeList map of NoteElement (name of the type as well as a pointer\n
on an object of this type^) so that we can iterate on note types (and display a list\n
of the note types for example).
**/

template <class Note>
class BaseNoteType : public NoteElement {
public:

    //! \brief Default constructor for the class
    BaseNoteType() {}

    //! \brief Constructor for the class
    //! @param title of the note we want to create
    //! @param creation date of the note we want to create
    BaseNoteType(const QString& title, const QDateTime& creaDate) : NoteElement(title,creaDate)  {}


    //! \brief Returns the name of the note type
    virtual QString typeName() const override {
        return Note::name();
    }

    //! \brief Add a new note type into the static NoteTypeList of NoteElement
    //! NoteTypeList contains a map with the name of the type as well as a pointer on an object of that note type
    static int setTypeInList() {
        return NoteElement::NoteTypeList(Note::name(), Note::newType()).size();
    }

    //! \brief A static integer calling setTypeInList when a derived note type class is defined
    //! The integer is initialized for each defined derived note type class
    static int id;

    //! \brief Class default destructor
    virtual ~BaseNoteType() = default;
};

//! \brief Definition of the id static integer, calling the setTypeInList function for each derived note type
template <class Note>
int BaseNoteType<Note>::id = setTypeInList();

/**
\class TypeNote
\brief Macro that defines the beginning of a class herited from BaseNoteType<TypeNote>

This class is herited from BaseNoteType<TypeNote> and is used for each note type\n
definition, it certifies that every note type class definition will be automatically\n
registered into the static NoteTypeList of the NoteElement class, by making use of\n
the BaseNoteType<TypeNote> methods.
**/

//! \brief idc initialization implies BaseNoteType<Note>::id initialization (calling the setTypeInList() method)
//! \brief newType() returns a pointer to a TypeNote object
//! \brief name() returns the name of the TypeNote class
#define setNoteType(TypeNote) \
class TypeNote : public BaseNoteType<TypeNote> { \
public:\
    int idc { id }; \
    static TypeNote* newType() { return new TypeNote; } \
    static QString name() { return QString::fromUtf8(#TypeNote); }

#endif // NOTETEMPLATE_H
