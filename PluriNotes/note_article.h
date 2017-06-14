#ifndef NOTE_ARTICLE_H
#define NOTE_ARTICLE_H

#include "notetemplate.h"

using namespace std;

/**
\class Article
\brief Class of the Article note type
**/

setNoteType(Article)
private:
    //! \brief Text of the Article
    const QString text;

public:
    //! \brief Constructor of Article without argument
    Article() {}

    //! \brief Constructor of Article
    //! @param title title of the article
    //! @param creaDate creation date
    //! @param text content of the article
    Article(const QString& title, const QDateTime& creaDate, const QString& text): BaseNoteType(title,creaDate), text(text) {}

    //! \brief Display Article on the PluriNotes UI
    virtual void displayNote() const override;

    //! \brief Return index of the note creation form page related to Article
    virtual unsigned int indexPageCreation() const override { return 0; }

    //! \brief Return a new Article initialized by the note creation form UI inputs
    //! @param title title of the article
    virtual Article* saveNote(QString title) override;

    //! \brief Return a new Article initialized by the note edition form UI inputs
    virtual Article* addVersion() const override;

    //! \brief Return true if the note edition form has UI inputs different from the Article
    virtual bool textChanged() const override;

    //! \brief Save the Article data in a file
    //! @param stream the resulting stream
    virtual void saveToXML(QXmlStreamWriter& stream) const override;

    //! \brief Load a Article from a file and add it into a NoteEntity
    //! @param stream the stream of XML
    //! @param newNoteEntity parent of the article
    virtual void loadFromXML(QXmlStreamReader& stream, NoteEntity& newNoteEntity) const override;

    //! \brief Return detected references from the Article data
    virtual QStringList returnReferences() const override;

    //! \brief Accessor to the text
    const QString& getText() const {return text;}

    //! \brief Destructor of Document
    ~Article() {}

    // UI
    //-------

    //! \brief set the article Content in the UI
    //! @param content the content of the article
    void setUiArticleContent(const QString& content) const;

    //! \brief get the article articleContent in the UI
    const QString getUiArticleContent() const;

    //! \brief get the article articleDisplayContent in the UI
    const QString getUiArticleContentEdit() const;

    //-------

};

#endif // NOTE_ARTICLE_H
