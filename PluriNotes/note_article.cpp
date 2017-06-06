#include "note_article.h"
#include "ui_plurinotes.h"
#include "application.h"
#include <QDateTime>

void Article::displayNote() const {
    PluriNotes& manager = PluriNotes::getManager();
    manager.setTextContentArticle(this->getText());
    manager.setNoteTitle(this->getTitle());
    manager.setNoteDate(this->getCreationDate());
}

QList<QWidget*> Article::champsForm() {
    textFormZone = new QTextEdit();
    textLabel = new QLabel(QString("Texte"));
    QList<QWidget*> listeWidgets;
    listeWidgets << textFormZone << textLabel;
    return listeWidgets;
}

Article* Article::saveNote(QString title) {
    return new Article(title, QDateTime::currentDateTime(), textFormZone->toPlainText());
}

Article* Article::addVersion() const {
    PluriNotes& manager = PluriNotes::getManager();
    return new Article(manager.getUi()->noteTextTitle->toPlainText(), QDateTime::currentDateTime(), manager.getUi()->noteTextContent->toPlainText());
}
