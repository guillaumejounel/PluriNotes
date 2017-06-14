/**
\file note_article.h
\date 14/06/2017
\author Florent Chehab, Guillaume Jounel and Félix Boisselier
\brief contains the note document class
**/

#ifndef NOTE_DOCUMENT_H
#define NOTE_DOCUMENT_H

#include "notetemplate.h"

using namespace std;

/**
\class Document
\brief Class of the Document note type
**/

setNoteType(Document)
private:
    //! \brief Description of the Document
    const QString description;

    //! \brief File path of the Document
    const QString file;

public:
    //! \brief Constructor of Document without argument
    Document() {}

    //! \brief Constructor of Document
    //! @param title title of the article
    //! @param creaDate creation date
    //! @param description description of the document
    //! @param file file linked with the document
    Document(const QString& title, const QDateTime& creaDate, const QString& description, const QString& file): BaseNoteType(title,creaDate), description(description), file(file) {}

    //! \brief Display Document on the PluriNotes UI
    virtual void displayNote() const override;

    //! \brief Return index of the note creation form page related to Document
    virtual unsigned int indexPageCreation() const override { return 2; }

    //! \brief Return a new Document initialized by the note creation form UI inputs
    //! @param title title of the document
    virtual Document* saveNote(QString title) override;

    //! \brief Return a new Document initialized by the note edition form UI inputs
    virtual Document* addVersion() const override;

    //! \brief Return true if the note edition form has UI inputs different from the Document
    virtual bool textChanged() const override;

    //! \brief Save the Document data in a file
    //! @param stream the resulting stream
    virtual void saveToXML(QXmlStreamWriter& stream) const override;

    //! \brief Load a Document from a file and add it into a NoteEntity
    //! @param stream the resulting stream
    //! @param newNoteEntity the note parent
    virtual void loadFromXML(QXmlStreamReader& stream, NoteEntity& newNoteEntity) const override;

    //! \brief Return detected references from the Document data
    virtual QStringList returnReferences() const override;

    //! \brief Accessor to the description
    QString getDescription() const { return description; }

    //! \brief Accessor to the file path
    QString getFile() const { return file; }

    //! \brief Destructor of Document
    ~Document() {}


    // UI
    //-------

    //! \brief Set the the UI description field content in Document edition form
    //! @param description description of the document
    void setUiDocumentDescription(const QString& description) const;

    //! \brief Get the the UI description field content in Document creation form
    const QString getUiDocumentDescription() const;

    //! \brief Get the the UI description field content in Document edition form
    const QString getUiDocumentDescriptionEdit() const;

    //! \brief Set the the UI file field content in Document edition form
    //! @param file file linked with the document
    void setUiDocumentFile(const QString& file) const;

    //! \brief Get the the UI file field content in Document creation form
    const QString getUiDocumentFile() const;

    //! \brief Get the the UI file field content in Document edition form
    const QString getUiDocumentFileEdit() const;

    //-------

};

#endif // NOTE_DOCUMENT_H
