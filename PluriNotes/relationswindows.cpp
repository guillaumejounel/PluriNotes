#include "relationswindows.h"
#include "ui_relationswindows.h"
#include "application.h"

relationsWindows::relationsWindows(QWidget *parent) : QMainWindow(parent), ui(new Ui::relationsWindows) {
    ui->setupUi(this);
    exitAction = menuBar()->addAction(QString("Close Window"));
    exitAction->setShortcuts(QKeySequence::Quit);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(beforeClose()));

    ui->mainStackedWidget->setCurrentIndex(1);
}

void relationsWindows::beforeClose() {
    // Reactivate the previous window
    PluriNotes& manager = PluriNotes::getManager();
    manager.setEnabled(true);

    //Close the window
    close();
}

void relationsWindows::toNewRelationForm() {
    ui->newRelationButton->setEnabled(false);
    ui->listOfAllRelations->setEnabled(false);
    ui->titleLineEdit->setReadOnly(false);
    ui->descriptionLineEdit->setReadOnly(false);
    ui->titleLineEdit->setText(QString(""));
    ui->descriptionLineEdit->setText(QString(""));
    ui->customWidgets->setCurrentIndex(0);
    ui->mainStackedWidget->setCurrentIndex(0);
}

Relation& relationsWindows::getCurrentRelation() {
    listRelationAndPointer* item = static_cast<listRelationAndPointer*> (ui->listOfAllRelations->currentItem());
    return *item->getRelationPointer();
}

void relationsWindows::displayRelation() {
    ui->listOfAllRelations->setEnabled(true);
    ui->newRelationButton->setEnabled(true);
    ui->titleLineEdit->setReadOnly(true);
    ui->descriptionLineEdit->setReadOnly(true);
    const Relation& currentSelectedRelation = getCurrentRelation();
    ui->titleLineEdit->setText(currentSelectedRelation.getTitle());
    ui->descriptionLineEdit->setText(currentSelectedRelation.getDescription());
    ui->customWidgets->setCurrentIndex(1);
//    ui->mainStackedWidget->setCurrentIndex(0);
}

void relationsWindows::closeEvent(QCloseEvent *event) {
    event->ignore();
    beforeClose();
    event->accept();
}

relationsWindows::~relationsWindows() {
    delete ui;
}

listRelationAndPointer* relationsWindows::addRelationToList(Relation* rel) {
    listRelationAndPointer* itm = new listRelationAndPointer(rel);
    itm->setText(rel->getTitle());
    addItemRelationToList(itm);
    return itm;
}

void relationsWindows::addItemRelationToList(listRelationAndPointer *item) {
    ui->listOfAllRelations->insertItem(0, item);
//    ui->listOfAllRelations->setCurrentRow(0);
}

