#include "application.h"
#include "ui_plurinotes.h"
#include "notes.h"

#include <iostream>
#include <QInputDialog>
#include <QLineEdit>

PluriNotes::PluriNotes(QWidget *parent) : QMainWindow(parent), ui(new Ui::PluriNotes) {
    ui->setupUi(this);
    ui->formWidget->hide();
}

PluriNotes::~PluriNotes() {
    delete ui;
    if(instanceUnique) delete instanceUnique;
    instanceUnique = nullptr;
}



void PluriNotes::createNote() {
    std::cout << "Clic sur createNote() !"<<std::endl;
    ui->idLineEdit->setText("");
    ui->titleLineEdit->setText("");
    ui->contentTextEdit->setPlainText("");
    ui->formWidget->show();
    bool ok;
    QStringList items;
    items << QString("Article");
    items << QString("Document");
    items << QString("Task");
    NoteForm note(this);
    note.show();
    /* QDate date = NoteDialog::getDate(this->centralWidget(),"test1", "test2", QDate(), &ok);
    QString text = QInputDialog::getText(this, tr("New note"), tr("Choose an id:"), QLineEdit::Normal, "", &ok);
    QString type = QInputDialog::getItem(this, tr("New note"), tr("Choose a note type:"), items,0,false);
       if (ok && !text.isEmpty()) {
           std::cout << text.toUtf8().constData() << std::endl;
           notes.push_back(NoteEntity(text));
       }
      */
}

void PluriNotes::saveNote() {
    std::cout << "Creation de " << this->ui->titleLineEdit->text().toUtf8().constData() << std::endl;
}

PluriNotes& PluriNotes::getManager() {
    if(!instanceUnique) instanceUnique = new PluriNotes;
    return *instanceUnique;
}
