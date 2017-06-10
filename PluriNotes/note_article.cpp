#include "note_article.h"
#include "ui_plurinotes.h"
#include "application.h"
#include <QDateTime>

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
