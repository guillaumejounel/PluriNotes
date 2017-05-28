#include "note_task.h"
#include "application.h"

#include <QDateTime>


void Tache::displayNote() const {
    // TODO: displayNote en fonction du type de note à afficher, il faut changer les champs de l'ui
    PluriNotes& manager = PluriNotes::getManager();
    manager.setTextContentArticle(this->getAction());
    manager.setNoteTitle(this->getTitle());
}

QList<QWidget*> Tache::champsForm() {
    laction = new QLabel(QString("Tache"));
    QList<QWidget*> listeWidgets;
    listeWidgets << laction;
    return listeWidgets;
}

Tache* Tache::saveNote(QString title) {
    //return new Tache(title, QDateTime::currentDateTime(), descr->text());
}
