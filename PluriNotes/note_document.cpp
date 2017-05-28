#include "note_document.h"
#include "application.h"

#include <QDateTime>


void Document::displayNote() const {
    PluriNotes& manager = PluriNotes::getManager();
    manager.setTextContentArticle(this->getDescription());
    manager.setNoteTitle(this->getTitle());
}


QList<QWidget*> Document::champsForm() {
    fichier = new QLineEdit();
    descr = new QLineEdit();
    lfichier = new QLabel(QString("Fichier"));
    ldescr = new QLabel(QString("Description"));
    QList<QWidget*> listeWidgets;
    listeWidgets << fichier << lfichier << descr << ldescr;
    return listeWidgets;
}

Document* Document::saveNote(QString title) {
    return new Document(title, QDateTime::currentDateTime(), descr->text());
}
