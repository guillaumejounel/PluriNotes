#include "application.h"
#include "ui_plurinotes.h"
#include "notes.h"

#include <iostream>
#include <QInputDialog>
#include <QLineEdit>
#include <QScrollArea>



PluriNotes::PluriNotes(QWidget *parent) : QMainWindow(parent), ui(new Ui::PluriNotes) {
    ui->setupUi(this);
    ui->formNoteWidget->hide();

    const QString & test = "test";
    ui -> listWidget -> addItem(test);
}

PluriNotes::~PluriNotes() {
    delete ui;
    if(instanceUnique) delete instanceUnique;
    instanceUnique = nullptr;
    notes.clear();
    corbeille.clear();
}

void PluriNotes::formNote() {
    is_idChanged = false;
    ui->newNote->setEnabled(false);
    ui->idLineEdit->setText("");
    ui->titleLineEdit->setText("");
    ui->contentTextEdit->setPlainText("");
    ui->TypeComboBox->setCurrentIndex(0);
    ui->formNoteWidget->show();
}

void PluriNotes::saveNote() {
    //Faire des vérifications de validité (id...)
    //Puis créer la note
    std::cout << "Creation of \"" << ui->titleLineEdit->text().toUtf8().constData() << "\"" << std::endl;
    NoteEntity *newNoteEntity = new NoteEntity(ui->idLineEdit->text());
    switch (ui->TypeComboBox->currentIndex()) {
    case 0:
        //const NoteArticle *newNote = new NoteArticle(ui->titleLineEdit->text(), ui->contentTextEdit->toPlainText());
        //newNoteEntity->addVersion(*newNote);
        break;
    case 1:
        std::cout << "Now Document !" << std::endl;
        break;
    case 2:
        std::cout << "Now Task !" << std::endl;
        break;
    }
    notes.push_back(newNoteEntity);
    ui -> listWidget -> addItem(newNoteEntity->getId());
    ui -> formNoteWidget -> hide();
}

void PluriNotes::cancelNote() {
    ui->newNote->setEnabled(true);
    ui->formNoteWidget->hide();
}

void PluriNotes::titleChanged() {
    //Titre modifié !
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
    switch (ui->TypeComboBox->currentIndex()) {
        case 0:
            std::cout << "Now Article !" << std::endl;
            break;
        case 1:
            std::cout << "Now Document !" << std::endl;
            break;
        case 2:
            std::cout << "Now Task !" << std::endl;
            break;
    }
    //Changer le formulaire selon le type
    QWidget* ok = new QWidget();
    ui->noteCreation->addWidget(ok);
}

PluriNotes& PluriNotes::getManager() {
    if(!instanceUnique) instanceUnique = new PluriNotes;
    return *instanceUnique;
}
