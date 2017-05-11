#include "plurinotes.h"
#include "ui_plurinotes.h"

PluriNotes::PluriNotes(QWidget *parent) : QMainWindow(parent), ui(new Ui::PluriNotes) {
    ui->setupUi(this);
}

PluriNotes::~PluriNotes() {
    delete ui;
}
