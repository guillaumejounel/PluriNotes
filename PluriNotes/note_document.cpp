#include "note_document.h"
#include "ui_plurinotes.h"
#include <QDateTime>

void Document::displayNote() const {
    setUiNoteTitle(getTitle());
    setUiNoteDate(getCreationDate());
    setUiDocumentDescription(description);
    setUiDocumentFile(file);
}

Document* Document::saveNote(QString title) {
    return new Document(title, QDateTime::currentDateTime(), getUiDocumentDescription(), getUiDocumentFile());
}

Document* Document::addVersion() const {
    return new Document(getUiNoteTitleEdit(), QDateTime::currentDateTime(), getUiDocumentDescriptionEdit(), getUiDocumentFileEdit());
}

bool Document::textChanged() const {
    return description == getUiDocumentDescriptionEdit() && file == getUiDocumentFileEdit();
}

void Document::saveToXML(QXmlStreamWriter& stream) const {
    stream.writeStartElement("version");
    stream.writeTextElement("title",getTitle());
    stream.writeTextElement("description", description);
    stream.writeTextElement("file", file);
    stream.writeTextElement("date",getCreationDate().toString("dddd dd MMMM yyyy hh:mm:ss"));
    stream.writeEndElement();
}

void Document::loadFromXML(QXmlStreamReader& stream, NoteEntity& newNoteEntity) const {
    QString title, description, file;
    QDateTime date;
    Document *newNote;
    while(!(stream.tokenType() == QXmlStreamReader::EndElement && stream.name() == "versions")) {
        if(stream.tokenType() == QXmlStreamReader::StartElement && stream.name() == "version") {
            while(!(stream.tokenType() == QXmlStreamReader::EndElement && stream.name() == "version")) {
                if(stream.tokenType() == QXmlStreamReader::StartElement) {
                    if(stream.name() == "title") {
                        stream.readNext(); title=stream.text().toString();
                    }
                    if(stream.name() == "description") {
                        stream.readNext(); description=stream.text().toString();
                    }
                    if(stream.name() == "file") {
                        stream.readNext(); file=stream.text().toString();
                    }
                    if(stream.name() == "date") {
                        stream.readNext(); date=QDateTime::fromString(stream.text().toString(),"dddd dd MMMM yyyy hh:mm:ss");
                    }
                }
                stream.readNext();
            }
            newNote = new Document(title, date, description, file);
            newNoteEntity.addVersion(*newNote);
        }
        stream.readNext();
    }
}

QStringList Document::returnReferences() const{
    QStringList ref = getReferences(getTitle())+getReferences(getDescription());
    ref.QStringList::removeDuplicates();
    return ref;
}

// UI
void Document::setUiDocumentDescription(const QString& description) const {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    ui->documentDisplayDescription->setText(description);
}

const QString Document::getUiDocumentDescription() const {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    return ui->documentDescription->toPlainText();
}

const QString Document::getUiDocumentDescriptionEdit() const {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    return ui->documentDisplayDescription->toPlainText();
}

void Document::setUiDocumentFile(const QString& file) const {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    ui->documentDisplayFile->setText(file);
}

const QString Document::getUiDocumentFile() const {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    return ui->documentFile->text();
}

const QString Document::getUiDocumentFileEdit() const {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    return ui->documentDisplayFile->text();
}
