#include "note_article.h"
#include "ui_plurinotes.h"
#include "application.h"
#include <QDateTime>
#include <QString>

void Article::displayNote() const {
    PluriNotes& manager = PluriNotes::getManager();
    manager.setNoteTitle(this->getTitle());
    manager.setNoteDate(this->getCreationDate());
    setUiArticleContent(getText());
}


Article* Article::saveNote(QString title) {
    PluriNotes& manager = PluriNotes::getManager();
    return new Article(title, QDateTime::currentDateTime(), getUiArticleContent());
}

Article* Article::addVersion() const {
    PluriNotes& manager = PluriNotes::getManager();
    return new Article(manager.getNoteTitleEdit(), QDateTime::currentDateTime(), getUiArticleContentEdit());
}

bool Article::textChanged() const {
    PluriNotes& manager = PluriNotes::getManager();
    return text == getUiArticleContentEdit();
}

void Article::saveToXML(QXmlStreamWriter& stream) const {
    stream.writeStartElement("version");
    stream.writeTextElement("title",getTitle());
    stream.writeTextElement("content", text);
    stream.writeTextElement("date",getCreationDate().toString("dddd dd MMMM yyyy hh:mm:ss"));
    stream.writeEndElement();
}

void Article::loadFromXML(QXmlStreamReader& stream, NoteEntity& newNoteEntity) const {
    QString title, content;
    QDateTime date;
    Article *newNote;
    while(!(stream.tokenType() == QXmlStreamReader::EndElement && stream.name() == "versions")) {
        if(stream.tokenType() == QXmlStreamReader::StartElement && stream.name() == "version") {
            while(!(stream.tokenType() == QXmlStreamReader::EndElement && stream.name() == "version")) {
                if(stream.tokenType() == QXmlStreamReader::StartElement) {
                    if(stream.name() == "title") {
                        stream.readNext(); title=stream.text().toString();
                    }
                    if(stream.name() == "content") {
                        stream.readNext(); content=stream.text().toString();
                    }
                    if(stream.name() == "date") {
                        stream.readNext(); date=QDateTime::fromString(stream.text().toString(),"dddd dd MMMM yyyy hh:mm:ss");
                    }
                }
                stream.readNext();
            }
            newNote = new Article(title, date, content);
            newNoteEntity.addVersion(*newNote);
        }
        stream.readNext();
    }
}


// UI
void Article::setUiArticleContent(const QString& content) const {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    ui->articleDisplayContent->setPlainText(content);
}

const QString Article::getUiArticleContent() const{
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    return ui->articleContent->toPlainText();
}

const QString Article::getUiArticleContentEdit() const {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    return ui->articleDisplayContent->toPlainText();
}
