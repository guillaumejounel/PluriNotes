#include "note_article.h"
#include "application.h"
#include <QDateTime>

void Article::displayNote() const {
    PluriNotes& manager = PluriNotes::getManager();
    manager.setTextContentArticle(this->getText());
    manager.setNoteTitle(this->getTitle());
    manager.setNoteDate(this->getCreationDate());
}



QList<QWidget*> Article::champsForm() {
    testText = new QTextEdit();
    testLabel = new QLabel(QString("Texte"));
    QList<QWidget*> listeWidgets;
    listeWidgets << testText << testLabel;
    return listeWidgets;
}

Article* Article::saveNote(QString title)  {
    return new Article(title, QDateTime::currentDateTime(), testText->toPlainText());
}

