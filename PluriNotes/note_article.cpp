#include "note_article.h"
#include "ui_plurinotes.h"
#include "application.h"
#include <QDateTime>
#include <QString>

void Article::displayNote() const {
    PluriNotes& manager = PluriNotes::getManager();
    manager.setNoteTitle(this->getTitle());
    manager.setNoteDate(this->getCreationDate());
    manager.setArticleContent(getText());
}


Article* Article::saveNote(QString title) {
    PluriNotes& manager = PluriNotes::getManager();
    return new Article(title, QDateTime::currentDateTime(), manager.getArticleContent());
}

Article* Article::addVersion() const {
    PluriNotes& manager = PluriNotes::getManager();
    return new Article(manager.getNoteTitleEdit(), QDateTime::currentDateTime(), manager.getArticleContentEdit());
}

bool Article::textChanged() const {
    PluriNotes& manager = PluriNotes::getManager();
    return text == manager.getArticleContentEdit();
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
    while(stream.name() != "note") {
        if(stream.tokenType() == QXmlStreamReader::StartElement) {
            if(stream.name() == "title") {
                stream.readNext(); title=stream.text().toString();
                qDebug()<<"title="<<title;
            }
            if(stream.name() == "content") {
                stream.readNext(); content=stream.text().toString();
                qDebug()<<"content="<<content;
            }
            if(stream.name() == "date") {
                stream.readNext(); date=QDateTime::fromString(stream.text().toString(),"dddd dd MMMM yyyy hh:mm:ss");
                qDebug()<<"date="<<date.toString("dddd dd MMMM yyyy hh:mm:ss");
            }
            const Article *newNote = new Article(title, date, content);
            newNoteEntity.addVersion(*newNote);
        }
        stream.readNext();
    }
}
