#ifndef NOTE_DOCUMENT_H
#define NOTE_DOCUMENT_H

#include "notetemplate.h"

using namespace std;

setNoteType(Document)
private:
    const QString description;
    const QString file;
public:
    Document() {}
    Document(const QString& title, const QDateTime& creaDate, const QString& description, const QString& file): BaseNoteType(title,creaDate), description(description), file(file) {}
    virtual void displayNote() const override;
    virtual unsigned int indexPageCreation() const override { return 2; }
    virtual Document* saveNote(QString title) override;
    virtual Document* addVersion() const override;
    virtual bool textChanged() const override;
    virtual void saveToXML(QXmlStreamWriter& stream) const override;
    virtual void loadFromXML(QXmlStreamReader& stream, NoteEntity& newNoteEntity) const override;
    ~Document() {}

    virtual QStringList returnReferences() const override;

    QString getDescription() const { return description; }

    // UI
    //-------
    // Task related
    //\todo move to an other class for better POO ?


    //! \todo add documentation
    void setUiDocumentDescription(const QString& description) const;

    //! \todo add documentation
    const QString getUiDocumentDescription() const;

    //! \todo add documentation
    const QString getUiDocumentDescriptionEdit() const;

    //! \todo add documentation
    void setUiDocumentFile(const QString& file) const;

    //! \todo add documentation
    const QString getUiDocumentFile() const;

    //! \todo add documentation
    const QString getUiDocumentFileEdit() const;


    //-------

};

#endif // NOTE_DOCUMENT_H
