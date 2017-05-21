#include "application.h"
#include "ui_plurinotes.h"
#include "notes.h"

#include <iostream>
#include <QInputDialog>
#include <QLineEdit>
#include <QScrollArea>



PluriNotes::PluriNotes(QWidget *parent) : QMainWindow(parent), ui(new Ui::PluriNotes) {
    ui->setupUi(this);
    ui->mainStackedWidget->setCurrentIndex(0);
}

PluriNotes::~PluriNotes() {
    delete ui;
    if(instanceUnique) delete instanceUnique;
    instanceUnique = nullptr;
    notes.clear();
    corbeille.clear();
}

void PluriNotes::toNewNoteForm() {
    is_idChanged = false;
    ui->ButtonNewNote->setEnabled(false);
    ui->idLineEdit->setText("");
    ui->titleLineEdit->setText("");
    ui->contentTextEdit->setPlainText("");
    ui->TypeComboBox->setCurrentIndex(0);
    ui->mainStackedWidget->setCurrentIndex(1);
    ui->listNotesWidget->setEnabled(false);
}

void PluriNotes::displayNote() {
    listItemAndPointer* item = static_cast<listItemAndPointer*> (ui->listNotesWidget->currentItem());
    NoteEntity* currentSelectedNote = item->getNotePointer();

    const NoteArticle *note = dynamic_cast<const NoteArticle*>(&currentSelectedNote->getLastVersion());

    ui->noteTextTitle->setText(currentSelectedNote->getTitle());
    ui->noteTextId->setText(currentSelectedNote->getId());
    ui->noteTextContent->setText(note->getText());
    ui->mainStackedWidget->setCurrentIndex(0);

}

void PluriNotes::saveNote() {
    //Faire des vérifications de validité (id...)
    //Puis créer la note
    std::cout << "Creation of \"" << ui->titleLineEdit->text().toUtf8().constData() << "\"" << std::endl;
    NoteEntity *newNoteEntity = new NoteEntity(ui->idLineEdit->text());
    const NoteArticle *newNote = new NoteArticle(ui->titleLineEdit->text(), ui->contentTextEdit->toPlainText());
    newNoteEntity->addVersion(*newNote);
    notes.push_back(newNoteEntity);


    listItemAndPointer* itm = new listItemAndPointer(newNoteEntity);
    itm->setText(newNoteEntity->getTitle());


    ui->listNotesWidget->addItem(itm);
    ui->mainStackedWidget->setCurrentIndex(0);
    ui->ButtonNewNote->setEnabled(true);
    ui->listNotesWidget->setEnabled(true);
}

void PluriNotes::cancelNote() {
    ui->ButtonNewNote->setEnabled(true);
    ui->listNotesWidget->setEnabled(true);
    ui->mainStackedWidget->setCurrentIndex(0);
}

void PluriNotes::titleChanged() {
    //Creer un id automatique
    QString currentTitle = ui->titleLineEdit->text().toUtf8().constData();
    currentTitle = currentTitle.toLower().remove(QRegExp("^.{1,2}\\s|\\s.{1,2}\\s|\\s.{1,2}$|^.{1,2}'|['\\s-_!.]"));
    currentTitle.truncate(10);
    currentTitle.replace("é", "e"); currentTitle.replace("è", "e"); currentTitle.replace("ë", "e");
    currentTitle.replace("ê", "e"); currentTitle.replace("à", "a"); currentTitle.replace("â", "a");
    currentTitle.replace("ù", "u"); currentTitle.replace("ö", "o"); currentTitle.replace("ï", "i");
    currentTitle.replace("ç", "c");
    if (!is_idChanged) { ui->idLineEdit->setText(currentTitle); } //Modifier id
}

void PluriNotes::idChanged() {
    //Si l'id est modifié manuellement, on arrête de le changer automatiquement
    is_idChanged = true;
    //Checker ici si l'id n'est pas déjà pris
}

void PluriNotes::typeChanged() {
    std::cout << "Type modified ! ";
    while (ui->formNoteWidget->count() > 9) {
        QLayoutItem* temp = ui->formNoteWidget->itemAt(8);
        ui->formNoteWidget->removeItem(temp);
        free(temp);
    }
    //Changer le formulaire selon le type
    //Pas très POO les switchs... Une autre solution ?
    QLineEdit *task, *doc;
    switch (ui->TypeComboBox->currentIndex()) {
        case 0:
            std::cout << "Now Article !" << std::endl;
            break;
        case 1:
            std::cout << "Now Document !" << std::endl;
            doc = new QLineEdit(tr("Document"));
            ui->formNoteWidget->insertWidget(8,doc,0);
            break;
        case 2:
            std::cout << "Now Task !" << std::endl;
            task = new QLineEdit(tr("Task"));
            ui->formNoteWidget->insertWidget(8,task,0);
            break;
    }
}

PluriNotes& PluriNotes::getManager() {
    if(!instanceUnique) instanceUnique = new PluriNotes;
    return *instanceUnique;
}
