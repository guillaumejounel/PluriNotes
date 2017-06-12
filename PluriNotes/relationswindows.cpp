#include "relationswindows.h"
#include "ui_relationswindows.h"
#include "application.h"
#include "commands.h"


relationsWindows::relationsWindows(QWidget *parent) : QMainWindow(parent), ui(new Ui::relationsWindows) {
    ui->setupUi(this);
    exitAction = menuBar()->addAction(QString("Close Window"));
    exitAction->setShortcuts(QKeySequence::Quit);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(beforeClose()));

    //! Creation of the undo stack
    undoStack = new QUndoStack(this);

    undoView = new QUndoView(undoStack);
    undoView->setWindowTitle(tr("Command List ~ Relations"));
    undoView->setAttribute(Qt::WA_QuitOnClose, false);


    viewUndoHistory = new QAction(tr("View&History"), this);
    connect(viewUndoHistory, SIGNAL(triggered()), this, SLOT(showUndoHistoryWindows()));

    undoAction = undoStack->createUndoAction(this, tr("&Undo"));
    undoAction->setShortcuts(QKeySequence::Undo);

    redoAction = undoStack->createRedoAction(this, tr("&Redo"));
    redoAction->setShortcuts(QKeySequence::Redo);


    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);


    windowsMenu = menuBar()->addMenu(tr("&Windows"));
    windowsMenu->addAction(viewUndoHistory);
}

void relationsWindows::beforeClose() {
    // Reactivate the previous window
    PluriNotes& manager = PluriNotes::getManager();
    manager.setEnabled(true);

    manager.onRelationsWindowsClose();

    // update trees if there have been modifications
    manager.updateTrees(manager.getCurrentNote());

    //Clear the couples ComboBoxes (to be reflilled at opening)
    ui->noteSelectorX->clear();
    ui->noteSelectorY->clear();

    //Clear the history
    undoStack->clear();

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

Relation *relationsWindows::getCurrentRelation() {
    listRelationAndPointer* item = static_cast<listRelationAndPointer*> (ui->listOfAllRelations->currentItem());
    if (item != nullptr) return item->getRelationPointer();
    return nullptr;
}

void relationsWindows::displayRelation() {
    ui->listOfAllRelations->setEnabled(true);
    ui->newRelationButton->setEnabled(true);
    ui->titleLineEdit->setReadOnly(true);
    ui->descriptionLineEdit->setReadOnly(true);
    const Relation* currentSelectedRelation = getCurrentRelation();
    // force bug removal
    if(currentSelectedRelation==nullptr){
        //the reference relation must be here !
        ui->listOfAllRelations->setCurrentRow(0);
        PluriNotes& manager = PluriNotes::getManager();
        currentSelectedRelation = manager.getReferencesRelation();
    }

    ui->titleLineEdit->setText(currentSelectedRelation->getTitle());
    ui->descriptionLineEdit->setText(currentSelectedRelation->getDescription());
    (currentSelectedRelation->isOriented())?ui->orientationSelection->setCurrentIndex(0):ui->orientationSelection->setCurrentIndex(1);

    ui->customWidgets->setCurrentIndex(1);
    ui->listCoupleWidget->clear();
    for (auto couple : currentSelectedRelation->getContent()) {
        addCoupleToList(couple);
    }
//    ui->mainStackedWidget->setCurrentIndex(0);
}

void relationsWindows::addRelation() {
    //Enregistre dans le vecteur relation de la classe PluriNotes
    //! \todo Faire des vérifications de validité (id...)
    //Puis créer la relation
    QString relationTitle = ui->titleLineEdit->text();
    QString relationDesc = ui->descriptionLineEdit->text();
    bool relationOriented;
    (ui->orientationSelection->currentIndex()==0)?relationOriented=true:relationOriented=false;
    Relation* newRelation = new Relation(relationTitle, relationDesc, relationOriented);

    PluriNotes& manager = PluriNotes::getManager();
    manager.addRelationToVector(newRelation);


    QUndoCommand *addCommand = new addRelationCommand(newRelation);
    undoStack->push(addCommand);
}

void relationsWindows::removeRelation(){
    Relation* relation = getCurrentRelation();

    QUndoCommand *removeCommand = new removeRelationCommand(relation);
    undoStack->push(removeCommand);
}

void relationsWindows::addCouple() {
    PluriNotes& manager = PluriNotes::getManager();
    NoteEntity* note1 = manager.getNoteById(ui->noteSelectorX->currentText());
    NoteEntity* note2 = manager.getNoteById(ui->noteSelectorY->currentText());
    if (note1->getId() == note2->getId()) {
        QMessageBox::warning(this, "Warning", "The couple is composed twice of the same note and cannot be added.");
    } else {
        QString defaultTitle = "";
        NoteCouple* newCouple = new NoteCouple(defaultTitle, note1, note2);

        Relation* currentSelectedRelation = getCurrentRelation();
        if (currentSelectedRelation->addCouple(newCouple)) {
            addCoupleToList(newCouple);
        }
    }
}

void relationsWindows::changeCoupleLabel() {
    QString label = QInputDialog::getText(this, "Change Couple Label", "New label :");
    listCoupleAndPointer* item = static_cast<listCoupleAndPointer*> (ui->listCoupleWidget->currentItem());
    NoteCouple* currentSelectedCouple = item->getCouplePointer();
    currentSelectedCouple->setLabel(label);
    displayRelation();
}

void relationsWindows::deleteCouple() {
    Relation* currentSelectedRelation = getCurrentRelation();
    listCoupleAndPointer* item = static_cast<listCoupleAndPointer*> (ui->listCoupleWidget->currentItem());
    NoteCouple* currentSelectedCouple = item->getCouplePointer();
    currentSelectedRelation->removeCouple(currentSelectedCouple);
    displayRelation();
}

void relationsWindows::closeEvent(QCloseEvent *event) {
    event->ignore();
    beforeClose();
    event->accept();
}

void relationsWindows::showEvent(QShowEvent *event) {
    event->accept();
    addNoteEntityToComboBoxes();
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

void relationsWindows::removeRelationFromList(Relation *rel){
    //! \todo add function to loog for wich panel the note is on!
    QListWidget* panel = ui->listOfAllRelations;

    unsigned int nbItems = panel->count();

    listRelationAndPointer* current;
    // We have to go throw all items in the list to know where is the relation
    unsigned int i=0;
    for(i=0; i<nbItems; i++) {
        current = static_cast<listRelationAndPointer*>(panel->item(i));
        if (current->getRelationPointer()->getNumber() == rel->getNumber()) break;
    }

    delete ui->listOfAllRelations->takeItem(i);
}


listCoupleAndPointer* relationsWindows::addCoupleToList(NoteCouple* couple) {
    listCoupleAndPointer* itm = new listCoupleAndPointer(couple);
    itm->setText(couple->print());
    addItemCoupleToList(itm);
    return itm;
}

void relationsWindows::addItemRelationToList(listRelationAndPointer *item) {
    ui->listOfAllRelations->insertItem(0, item);
    ui->listOfAllRelations->setCurrentRow(0);
}

void relationsWindows::addItemCoupleToList(listCoupleAndPointer *item) {
    ui->listCoupleWidget->insertItem(0, item);
    ui->listCoupleWidget->setCurrentRow(0);
}

void relationsWindows::addNoteEntityToComboBoxes() {
    PluriNotes& manager = PluriNotes::getManager();
    QVector<NoteEntity*> notes = manager.getNotesVector();
    if(notes.size()) {
        ui->noteSelectorX->setEnabled(true);
        ui->noteSelectorY->setEnabled(true);
        for(auto note : notes) {
            ui->noteSelectorX->addItem(note->getId());
            ui->noteSelectorY->addItem(note->getId());
        }
    } else {
        ui->noteSelectorX->setEnabled(false);
        ui->noteSelectorY->setEnabled(false);
    }
}


void relationsWindows::showUndoHistoryWindows() {
    undoView->show();
}
