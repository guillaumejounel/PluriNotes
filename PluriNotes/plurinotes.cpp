#include "plurinotes.h"
#include "ui_plurinotes.h"

#include <iostream>
#include <QInputDialog>
#include <QLineEdit>

PluriNotes::PluriNotes(QWidget *parent) : QMainWindow(parent), ui(new Ui::PluriNotes) {
    ui->setupUi(this);
}

PluriNotes::~PluriNotes() {
    delete ui;
    if(instanceUnique) delete instanceUnique;
    instanceUnique = nullptr;
}


void PluriNotes::createNote() {
    std::cout << "Clic sur createNote() !"<<std::endl;
    bool ok;

    QStringList items;
    items << QString("Choice 1");
    items << QString("Choice 2");
    items << QString("Choice 3");


    QString text = QInputDialog::getText(this, tr("Nouvelle note"),
                   tr("Choisissez un id :"), QLineEdit::Normal,
                   "Nom", &ok);
    QString type = QInputDialog::getItem(this, tr("ok"), tr("go"), items);
       if (ok && !text.isEmpty()) {
           std::cout << text.toUtf8().constData() << std::endl;
           notes.push_back(NoteEntity(text));
       }
}

PluriNotes& PluriNotes::getManager() {
    if(!instanceUnique) instanceUnique = new PluriNotes;
    return *instanceUnique;
}
