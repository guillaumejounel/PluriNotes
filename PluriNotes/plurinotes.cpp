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
    if(instanceUnique) delete instanceUnique; instanceUnique = nullptr;
}


void PluriNotes::createNote() {
    std::cout << "Clic sur createNote() !"<<std::endl;
    bool ok;
    QString text = QInputDialog::getText(this, tr("Création d'une nouvelle note"),
                   tr("Id du nouvel article :"), QLineEdit::Normal,
                   "Nom", &ok);
       if (ok && !text.isEmpty())
           std::cout << text.toUtf8().constData() << std::endl;
}

PluriNotes& PluriNotes::getManager() {
    if(!instanceUnique) instanceUnique = new PluriNotes;
    return *instanceUnique;
}
