#include "noteelement.h"


const map<QString, NoteElement*>& NoteElement::NoteTypeList(QString typeName, NoteElement* ptNote) {
    static map<QString, NoteElement*> ensTypeNote; //L'ensemble des noms des classes dérivées
    if (ptNote) ensTypeNote.insert(make_pair(typeName, ptNote));
    return ensTypeNote;
}

map<QString, NoteElement*> NoteElement::getTypesNotes() {
    return NoteTypeList("", nullptr);
}


QStringList NoteElement::getReferences(const QString& text) const{
        QRegExp rx("[\\ref\{]([\\w|\\d]+)[\}]");

        QStringList list = rx.capturedTexts();

        int pos = 0;

        while ((pos = rx.indexIn(text, pos)) != -1) {
            list << rx.cap(1);
            pos += rx.matchedLength();
        }

        //cleaning process
        QString tmp("");
        list.removeAll(tmp);

        return list;
}


// UI

void NoteElement::setUiNoteTitle(const QString& t) const{
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    ui->titleDisplayLineEdit->setText(t);
}

void NoteElement::setUiNoteDate(const QDateTime& d) const{
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    ui->dateDisplayLineEdit->setText(d.toString("dddd dd MMMM yyyy hh:mm:ss"));
}


const QString NoteElement::getUiNoteTitleEdit()const {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    return ui->titleDisplayLineEdit->text();
}

