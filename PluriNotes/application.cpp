#include "application.h"
#include "ui_plurinotes.h"
#include "relationswindows.h"

#include <QDateTime>

#include "commands.h"
#include <QtWidgets>

PluriNotes& PluriNotes::getManager() {
    if(!instanceUnique) instanceUnique = new PluriNotes;
    return *instanceUnique;
}

PluriNotes::PluriNotes(QWidget *parent) : QMainWindow(parent), ui(new Ui::PluriNotes) {
    //Constructeur de la classe PluriNotes
    ui->setupUi(this);

    //Chargement des différents types de notes dont il faut proposer la création
    map<QString,NoteElement*> myMap = NoteElement::getTypesNotes();
    for (MapIterator iter = myMap.begin(); iter != myMap.end(); iter++) {
        ui->TypeComboBox->addItem(iter->first);
    }

    //! Creation of the undo stack
    undoStack = new QUndoStack(this);

    createActions();
    createMenus();

    createUndoView();
    createRelationsView();

    // Creation of the reference relation
    QString t = "References";
    QString d = "Here is the relation with all the diffent reference";
    Relation* Reference = new Relation(t,d,true,true);
    relations.push_back(Reference);

    //Affiche l'écran de démarrage
    ui->mainStackedWidget->setCurrentIndex(3);
}

void PluriNotes::testFunction() {
    /*
    Relation* ref = relations[0];
    QString l = QString("couple 1");
    NoteCouple& c = *(new NoteCouple(l,notes[0],notes[1]));
    ref->addCouple(c);


    l = QString("couple 2");
    c = *(new NoteCouple(l,notes[1],notes[2]));
    ref->addCouple(c);


    l = QString("couple 3");
    c = *(new NoteCouple(l,notes[2],notes[3]));
    ref->addCouple(c);
    */

}



void PluriNotes::createUndoView()
{
    undoView = new QUndoView(undoStack);
    undoView->setWindowTitle(tr("Command List"));
    undoView->setAttribute(Qt::WA_QuitOnClose, false);
}

void PluriNotes::createRelationsView()
{

    relationsView = new relationsWindows();
    relationsView->setWindowTitle(tr("Relations managment"));
    relationsView->setAttribute(Qt::WA_QuitOnClose, false);
}


void PluriNotes::saveApplication() {
    save();
}


void PluriNotes::openRelationsWindow() {
    relationsView->show();
    setEnabled(false);
}

void PluriNotes::showUndoHistoryWindows() {
    undoView->show();
}

void PluriNotes::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(saveAction);
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();

    openRelations = menuBar()->addAction(QString("Manage Relations"));
    connect(openRelations,SIGNAL(triggered()),this, SLOT(openRelationsWindow()));

    windowsMenu = menuBar()->addMenu(tr("&Windows"));
    windowsMenu->addAction(viewUndoHistory);
    /*
    editMenu->addAction(deleteAction);

    connect(editMenu, SIGNAL(aboutToShow()),
            this, SLOT(itemMenuAboutToShow()));
    connect(editMenu, SIGNAL(aboutToHide()),
            this, SLOT(itemMenuAboutToHide()));
    */
    /*
    itemMenu = menuBar()->addMenu(tr("&Item"));

    itemMenu->addAction(addBoxAction);
    itemMenu->addAction(addTriangleAction);

    helpMenu = menuBar()->addMenu(tr("&About"));
    helpMenu->addAction(aboutAction);
    */
}



void PluriNotes::createActions()
{
    /*
    deleteAction = new QAction(tr("&Delete Item"), this);
    deleteAction->setShortcut(tr("Del"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));


    addBoxAction = new QAction(tr("Add &Box"), this);
    addBoxAction->setShortcut(tr("Ctrl+O"));
    connect(addBoxAction, SIGNAL(triggered()), this, SLOT(addBox()));

    addTriangleAction = new QAction(tr("Add &Triangle"), this);
    addTriangleAction->setShortcut(tr("Ctrl+T"));
    connect(addTriangleAction, SIGNAL(triggered()), this, SLOT(addTriangle()));
    */

    undoAction = undoStack->createUndoAction(this, tr("&Undo"));
    undoAction->setShortcuts(QKeySequence::Undo);

    redoAction = undoStack->createRedoAction(this, tr("&Redo"));
    redoAction->setShortcuts(QKeySequence::Redo);

    saveAction = new QAction(tr("S&ave"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveApplication()));
    saveAction->setEnabled(false);

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    viewUndoHistory = new QAction(tr("View&History"), this);
    connect(viewUndoHistory, SIGNAL(triggered()), this, SLOT(showUndoHistoryWindows()));
    /*
    aboutAction = new QAction(tr("&About"), this);
    QList<QKeySequence> aboutShortcuts;
    aboutShortcuts << tr("Ctrl+A") << tr("Ctrl+B");
    aboutAction->setShortcuts(aboutShortcuts);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    */
}



PluriNotes::~PluriNotes() {
    //Destructeur de la classe PluriNotes
    delete ui;
    if(instanceUnique) delete instanceUnique;
    instanceUnique = nullptr;
    notes.clear();
    trash.clear();

    delete relationsView;
    delete undoView;
}

void PluriNotes::toNewNoteForm() {
    //Ouverture du formulaire de création de notes
    is_idChanged = false;
    ui->ButtonNewNote->setEnabled(false);
    ui->idLineEdit->clear();
    ui->titleLineEdit->clear();
    ui->TypeComboBox->setCurrentIndex(0);
    ui->listNotesWidget->setEnabled(false);
    ui->mainStackedWidget->setCurrentIndex(1);
    ui->idUniqueEdit->hide();
    typeChangedForm();
}


QListWidget* PluriNotes::getListActiveNotes() const {
    return ui->listNotesWidget;
}

QListWidget* PluriNotes::getListArchived() const {
    return ui->listArchivedWidget;
}

QListWidget* PluriNotes::getListTrash() const {
    return ui->listTrashWidget;
}

QListWidget* PluriNotes::getListTasks() const {
    return ui->listTaskWidget;
}


NoteEntity& PluriNotes::getCurrentNote() {
    listItemAndPointer* item = static_cast<listItemAndPointer*> (ui->listNotesWidget->currentItem());
    return *item->getNotePointer();
}

void PluriNotes::displayNote(unsigned int n) {
    isDisplayed = false;
    ui->idDisplayLineEdit->setReadOnly(true);
    ui->dateDisplayLineEdit->setReadOnly(true);
    if(notes.size()) {
        const NoteEntity& currentSelectedNote = getCurrentNote();
        ui->idDisplayLineEdit->setText(currentSelectedNote.getId());
        ui->noteTextVersion->clear();
        updateTrees(const_cast<NoteEntity*>(&currentSelectedNote));
        if (currentSelectedNote.getSize() == 1) {
            ui->noteTextVersion->addItem(QString("Version 1"));
            ui->noteTextVersion->setEnabled(0);
        } else {
            ui->noteTextVersion->setEnabled(1);
            for(unsigned int i = currentSelectedNote.getSize(); i > 0; --i)
                ui->noteTextVersion->addItem(QString("Version ") + QString::number(i));
            ui->noteTextVersion->setCurrentIndex(n);
        }
        n = ui->noteTextVersion->count() - ui->noteTextVersion->currentIndex() - 1;
        const NoteElement& note = currentSelectedNote.getVersion(n);
        ui->noteTypeDisplay->setCurrentIndex(note.indexPageCreation());
        //Ajout et remplissage des champs de type de note
        note.displayNote();
        ui->mainStackedWidget->setCurrentIndex(0);
    } else {
        ui->mainStackedWidget->setCurrentIndex(2);
    }
    isDisplayed = true;
}

void PluriNotes::noteVersionChanged() {
    if (isDisplayed) {
        displayNote(ui->noteTextVersion->currentIndex());
        if (ui->noteTextVersion->currentIndex() == 0) {
            ui->buttonSaveEdit->setText(QString("Save"));
            ui->titleDisplayLineEdit->setReadOnly(0);
            ui->articleDisplayContent->setReadOnly(0);
            ui->taskDisplayAction->setReadOnly(0);
            ui->taskDisplayDeadline->setReadOnly(0);
            ui->taskDisplayPriority->setDisabled(0);
            ui->taskDisplayStatus->setDisabled(0);
            ui->fileDisplayDescription->setReadOnly(0);
            ui->fileDisplayFile->setDisabled(0);
        } else {
            ui->buttonSaveEdit->setText(QString("Restore"));
            ui->titleDisplayLineEdit->setReadOnly(1);
            ui->articleDisplayContent->setReadOnly(1);
            ui->taskDisplayAction->setReadOnly(1);
            ui->taskDisplayDeadline->setReadOnly(1);
            ui->taskDisplayPriority->setDisabled(1);
            ui->taskDisplayStatus->setDisabled(1);
            ui->fileDisplayDescription->setReadOnly(1);
            ui->fileDisplayFile->setDisabled(1);
        }
    }
}

void PluriNotes::noteTextChanged() {
    const NoteElement& note = getCurrentNote().getLastVersion();
    if(ui->noteTextVersion->currentIndex() != 0) {
        ui->buttonSaveEdit->setEnabled(1);
        ui->buttonCancelEdit->setEnabled(0);
    } else {
        if((ui->titleDisplayLineEdit->text() == note.getTitle() && note.textChanged())) {
            ui->buttonCancelEdit->setEnabled(0);
            ui->buttonSaveEdit->setEnabled(0);
        } else {
            ui->buttonCancelEdit->setEnabled(1);
            ui->buttonSaveEdit->setEnabled(1);
        }
    }
}

bool PluriNotes::isIdAvailable(const QString& id) const {
    for (auto note : notes) {
        if(note->getId() == id) return false;
    }
    for (auto note : trash) {
        if(note->getId() == id) return false;
    }
    return true;
}

NoteEntity* PluriNotes::getNoteById(const QString& id) {
    for (auto note : notes) {
        if(note->getId() == id) return note;
    }
    return nullptr;
}

void PluriNotes::saveNote() {
    map<QString,NoteElement*> myMap = NoteElement::getTypesNotes();
    bool flag = true;

    //Check validity
    if (ui->titleLineEdit->text() == QString("") || ui->idLineEdit->text() == QString("") || !isIdAvailable(ui->idLineEdit->text())) flag = false;
    for(QTextEdit* widget: ui->customWidgets->widget(myMap[ui->TypeComboBox->currentText()]->indexPageCreation())->findChildren<QTextEdit*>())
        if(widget->property("obligatory").toBool() && widget->toPlainText() == QString("")) flag = false;

    //Create and save the note ; to check references it is easier
    NoteEntity *newNoteEntity = new NoteEntity(ui->idLineEdit->text());
    NoteElement* newNote = myMap[ui->TypeComboBox->currentText()]->saveNote(ui->titleLineEdit->text());
    QDateTime creationDate = QDateTime::currentDateTime();
    newNote->setCreationDate(creationDate);
    newNoteEntity->addVersion(*newNote);

    // references check
    bool references = true;
    QStringList referencesInNotes = newNoteEntity->returnReferences();
    QStringList allActiveRefences = getActiveReferences();
    for (auto s : referencesInNotes ){
        // for all references in the field we check if they are valid
        if (!allActiveRefences.contains(s)){
            flag = false; references = false;
        }
    }

    if(flag) {
        QUndoCommand *addCommand = new addNoteEntityCommand(newNoteEntity);
        undoStack->push(addCommand);
    } else {
        delete newNoteEntity;

        //Input is not valid
        QMessageBox msgBox;
        msgBox.setText("Please check your input");

        if (references == false) msgBox.setText("Please check your input. You notably have references issues !");
        msgBox.exec();
    }
}

void PluriNotes::saveNewVersion() {
    // We get which not is selected
    NoteEntity& currentNote = getCurrentNote();
    // We create a newVersion identical to the last one
    const NoteElement& currentVersion = currentNote.getLastVersion();

    const NoteElement& newVersion = *currentVersion.addVersion();

    QUndoCommand *addVersionCommand = new addVersionNoteCommand(const_cast<NoteEntity*>(&currentNote),const_cast<NoteElement*>(&newVersion));
    undoStack->push(addVersionCommand);
}


void PluriNotes::deleteNote() {
    //Demande de confirmation
    //à plutôt faire pour vider la corbeille étant donné que les notes sont récupérables jusque là
    /* QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Suppression", "Are you sure?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
    } */

    //Supprime la note selectionnée du vecteur notes
    listItemAndPointer* item = static_cast<listItemAndPointer*> (ui->listNotesWidget->currentItem());
    NoteEntity* currentSelectedNote = item->getNotePointer();

    QUndoCommand *deleteCommand = new deleteNoteCommand(currentSelectedNote);
    undoStack->push(deleteCommand);
}

bool PluriNotes::isInsideApp(const NoteEntity *note) {
    for (auto current: notes) {
        if (current==note) {
            return true;
        }
    }

    for (auto current: trash) {
        if (current==note) {
            return true;
        }
    }

    return false;

}

//! \todo add error handling
void PluriNotes::moveToTrash(NoteEntity *noteEl) {
    unsigned int i = 0;
    for (auto note: notes) {
        if (noteEl==note) {
            notes.erase(notes.begin()+i);
            trash.push_back(note);
            return;
        }
        ++i;
    }

    //! \todo error handling
}


void PluriNotes::moveBackFromTrash(NoteEntity* noteEl) {
    unsigned int i = 0;
    for (auto note: trash) {
        if (noteEl==note) {
            trash.erase(trash.begin()+i);
            notes.push_back(note);
            return;
        }
        ++i;
    }

    //! \todo add error ?
}

void PluriNotes::cancelNote() {
    ui->ButtonNewNote->setEnabled(true);
    ui->listNotesWidget->setEnabled(true);
    if (notes.size()) ui->mainStackedWidget->setCurrentIndex(0);
    else ui->mainStackedWidget->setCurrentIndex(2);
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
    if (!is_idChanged) { ui->idLineEdit->setText(currentTitle); idChanged(true); }
}

void PluriNotes::idChanged(bool fromTitle) {
    //Si l'id est modifié manuellement, on arrête de le changer automatiquement
    if (!fromTitle) is_idChanged = true;
    //Check si l'id n'est pas déjà pris
    if (!isIdAvailable(ui->idLineEdit->text()))
        ui->idUniqueEdit->show();
    else ui->idUniqueEdit->hide();
}

void PluriNotes::typeChangedForm() {
    //! \todo évolutivité ??
    //Ajout des champs selon le type de note
    map<QString,NoteElement*> myMap = NoteElement::getTypesNotes();
    ui->customWidgets->setCurrentIndex(myMap[ui->TypeComboBox->currentText()]->indexPageCreation());
    //init article form
    ui->articleContent->clear();

    //init task form
    ui->taskAction->clear();
    ui->taskPriority->setCurrentIndex(0);
    ui->taskDeadline->setDateTime(QDateTime::currentDateTime());

    //init file form
    ui->fileDescription->clear();
}


void PluriNotes::save() {
    QString path = QCoreApplication::applicationDirPath();
    path.append("/data");
    QFile newfile(path);
    //Faire une classe pour les exceptions
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        qDebug() << "erreur sauvegarde notes : ouverture fichier xml";
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("data");
    {
        stream.writeStartElement("notes");
            for(auto const& note: notes)
                note->saveToXML(stream);
        stream.writeEndElement();
        stream.writeStartElement("trash");
            for(auto const& note: trash)
                note->saveToXML(stream);
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
    setDataChanged(false);
}

void PluriNotes::load() {
    QString path = QCoreApplication::applicationDirPath();
    path.append("/data");
    QFile fin(path);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening the data file";
    }
    QXmlStreamReader xml(&fin);
    bool toTrash = false;
    NoteEntity* newNoteEntity;
    while(!xml.atEnd() && !xml.hasError()) {
        if(xml.name() == "trash") toTrash = true;
        if(xml.name() == "note" && xml.tokenType() == QXmlStreamReader::StartElement) {
            newNoteEntity = NoteEntity::loadFromXML(xml);
            if (toTrash) trash.push_back(newNoteEntity);
            else notes.push_back(newNoteEntity);
        }
        xml.readNext();
    }
    // Error handling.
    if(xml.hasError()) {
        qDebug() << "Data file is corrupted";
    }
    xml.clear();
    setDataChanged(false);
}

void PluriNotes::loadDataIntoUi() {
    //! \todo add loading functionnalities to trash and notes
    for(auto& rel: relations) {
        static_cast<relationsWindows*>(relationsView)->addRelationToList(const_cast<Relation*>(rel));
    }
    for(NoteEntity* note:trash) {
        addNoteToList(note, ui->listTrashWidget);
    }
    for(NoteEntity* note:notes) {
        if (note->getLastVersion().typeName() == "Task")
            addNoteToList(note, ui->listTaskWidget);
        else
            addNoteToList(note, note->isArchived()?ui->listArchivedWidget:ui->listNotesWidget);
    }
}


listItemAndPointer* PluriNotes::addNote(NoteEntity& note, QListWidget* list) {
    notes.push_back(&note);
    listItemAndPointer* item = addNoteToList(&note, list);
    return item;
}

void PluriNotes::removeNote(NoteEntity *note) {
    notes.removeAll(note);
}

//! \todo add item to list based on last modified date !
listItemAndPointer* PluriNotes::addNoteToList(NoteEntity* note, QListWidget* list) {
    listItemAndPointer* itm = new listItemAndPointer(note);
    itm->setText(note->getTitle());
    addItemNoteToList(itm, list);
    return itm;
}


void PluriNotes::addItemNoteToList(listItemAndPointer *item, QListWidget* list) {
    list->insertItem(0, item);
    list->setCurrentRow(0);
    ui->mainStackedWidget->setCurrentIndex(0);
    ui->ButtonNewNote->setEnabled(true);
    ui->listNotesWidget->setEnabled(true);
}


listItemAndPointer* PluriNotes::removeItemNoteFromList(listItemAndPointer* item, QListWidget* list) {
    unsigned int i = list->row(item);
    return static_cast<listItemAndPointer*>(list->takeItem(i));
}

//! ####################################
//! ####################################
void PluriNotes::removeNoteFromList(NoteEntity *note, QListWidget* list) {
    //We remove the item from the panel
    //! \todo check if have to use delete for memomry
    unsigned int i = list->row(findItemInList(note, list));
    list->takeItem(i);
}

listItemAndPointer* PluriNotes::findItemInList(NoteEntity* note, QListWidget* list) {
    //! \todo add function to loog for wich panel the note is on!
    QListWidget* panel = list;

    unsigned int nbItems = panel->count();
    listItemAndPointer* current;

    QString idWeAreLookingFor = note->getId();

    // We have to go throw all items in the list to know where is note
    unsigned int i=0;
    for(i=0; i<nbItems; i++) {
        current = static_cast<listItemAndPointer*>(panel->item(i));
        if (current->getNotePointer()->getId() == idWeAreLookingFor) break;
    }

    return current;
}

void PluriNotes::selectItemIntoList(listItemAndPointer* item, QListWidget* list) {
    QListWidget* panel = list;
    panel->setCurrentItem(item);
}



//! \todo add item to list based on last modified date !
treeItemNoteAndPointer* PluriNotes::addNoteToTree(NoteEntity* note, QTreeWidget* tree) {
    treeItemNoteAndPointer* itm = new treeItemNoteAndPointer(note);
    itm->setText(0,note->getTitle());
    tree->insertTopLevelItem(0,itm);
    addNoteChildToTree(itm,tree);
    return itm;
}



void PluriNotes::addNoteChildToTree(treeItemNoteAndPointer* item, QTreeWidget* tree) {
    QSet<NoteEntity*> noteChildren;

    // Which tree is concerned ?
    if(tree == ui->treeViewPredecessors) {
        noteChildren = getAllPredecessorsOf(item->getNotePointer());
    }
    else{
        noteChildren = getAllSuccessorsOf(item->getNotePointer());
    }


    treeItemNoteAndPointer* child;

    for (auto note : noteChildren) {
        child = new treeItemNoteAndPointer(note);
        child->setText(0,note->getTitle());
        item->addChild(child);
    }
}

void PluriNotes::addNoteChildrenToItem(QTreeWidgetItem* item, QTreeWidget* tree) {
    treeItemNoteAndPointer* tmp = static_cast<treeItemNoteAndPointer*>(item);

    //We have to check if we haven't already calculated the children
    if (!tmp->hasBeenExpended()) {
        QList<QTreeWidgetItem*> childrenList =	item->takeChildren();
        // We add back the childre because this process removes them...
        item->addChildren(childrenList);

        for(auto noteChild : childrenList) {
            addNoteChildToTree(static_cast<treeItemNoteAndPointer*>(noteChild),tree);
        }
        tmp->setExpensionCalculusStatus(true);
    }

}

void PluriNotes::updateAddChildTreeSuccessors(QTreeWidgetItem* item) {
    QTreeWidget* tree = ui->treeViewSuccessors;
    addNoteChildrenToItem(item,tree);
}

void PluriNotes::updateAddChildTreePredecessors(QTreeWidgetItem* item) {
    QTreeWidget* tree = ui->treeViewPredecessors;
    addNoteChildrenToItem(item,tree);
}


void PluriNotes::updateTrees(NoteEntity* note) {
    ui->treeViewPredecessors->clear();
    ui->treeViewSuccessors->clear();

    QSet<NoteEntity*> successorsOfNote = getAllSuccessorsOf(note);
    QSet<NoteEntity*> predecessorsOfNote = getAllPredecessorsOf(note);

    for(auto note : successorsOfNote) {
        addNoteToTree(note,ui->treeViewSuccessors);
    }

    for(auto note : predecessorsOfNote) {
        addNoteToTree(note,ui->treeViewPredecessors);
    }

    QString label;
    if (successorsOfNote.isEmpty()) {
        label = QString("This note has no Successors");
        ui->treeViewSuccessors->setHeaderLabel(label);
    }
    else{
        label = QString("Successors of the note :");
        ui->treeViewSuccessors->setHeaderLabel(label);
    }

    if (predecessorsOfNote.isEmpty()) {
        label = QString("This note has no Predecessors");
        ui->treeViewPredecessors->setHeaderLabel(label);
    }
    else{
        label = QString("Predecessors of the note :");
        ui->treeViewPredecessors->setHeaderLabel(label);
    }

}

//! ####################################
//! ####################################

void PluriNotes::setDataChanged(bool b) {
    dataChanged = b;
    saveAction->setEnabled(b);
}


void PluriNotes::closeEvent(QCloseEvent *event) {
    event->ignore();
    if (hasDataChanged()) {
        if (QMessageBox::Yes == QMessageBox::question(this, "Save data?",
                                  "Do you want to save data?",
                                  QMessageBox::Yes|QMessageBox::No))
         {
            save();
         }
    }
    event->accept();
}


unsigned int PluriNotes::getMaxRelationId() {
    unsigned int nbOfRealations = relations.size();
    //return nbOfRealations;

    if (nbOfRealations == 0) return 0;

    unsigned int max = 0;

    for (unsigned int i = 0; i < nbOfRealations ; i++) {
        if( (relations[i])->getNumber() > max) max = (relations[i])->getNumber();
    }

    return max;
}



Relation* PluriNotes::getReferencesRelation() {
    unsigned int nbOfRelations = relations.size();
    for (unsigned int i = 0; i < nbOfRelations ; i++) {
        if( (relations[i])->isReferences()) return const_cast<Relation*>(relations[i]);
    }
    return nullptr;
}

void PluriNotes::addRelationToVector(Relation* r) {
    relations.push_back(r);
}


QSet<NoteEntity*> PluriNotes::getAllSuccessorsOf(NoteEntity* note) const{
    unsigned int nbOfRealations = relations.size();
    QSet<NoteEntity*> result;

    // Quick way to get all successors;
    for (unsigned int i = 0; i < nbOfRealations ; i++) {
        result = result + (relations[i])->successorsOf(note);
    }

    return result;
}

QSet<NoteEntity*> PluriNotes::getAllPredecessorsOf(NoteEntity* note) const{
    unsigned int nbOfRealations = relations.size();
    QSet<NoteEntity*> result;

    // Quick way to get all successors;
    for (unsigned int i = 0; i < nbOfRealations ; i++) {
        result = result + (relations[i])->predecessorsOf(note);
    }

    return result;
}

QSet<NoteEntity*> PluriNotes::getAllPredecessorsOf(QList<NoteEntity*> noteList) const{
    QSet<NoteEntity*> result;
    for (auto note : noteList){
        result = result + getAllPredecessorsOf(note);
    }

    return result;
}


QSet<NoteEntity*> PluriNotes::getAllReferencesOf(NoteEntity * note) const{
    return getAllPredecessorsOf(note) + getAllSuccessorsOf(note);
}

bool PluriNotes::isReferenced(NoteEntity* note){
    return relations[0]->hasPredecessors(note);
}


QList<coupleAndRelation> PluriNotes::deletedCouples(NoteEntity* note){
//
}

QStringList PluriNotes::getActiveReferences() const {
    QStringList output;
    for (auto note : notes){
        if (!note->isArchived()) output += note->getId();
    }
    return output;
}

void PluriNotes::addReferences(NoteEntity* note, const QStringList& idList){
    // We have first to build a list of NoteEntity* based on the list of ID
    QList<NoteEntity*> listOfNoteMatchingId;

    for(auto note : notes){
        if (idList.contains(note->getId())){
            listOfNoteMatchingId.append(note);
            qWarning()<<QString("reference matched !");
        }

    }

    QString label("ref");
    for (auto y : listOfNoteMatchingId){
        NoteCouple* couple = new NoteCouple(label, note, y);
        getReferencesRelation()->addCouple(couple);
    }
}



void PluriNotes::updateSelectionFromTreeSuccessors() {
    treeItemNoteAndPointer* itm = static_cast<treeItemNoteAndPointer*>(ui->treeViewSuccessors->currentItem());
    selectItemIntoList(findItemInList(itm->getNotePointer(), ui->listNotesWidget), ui->listNotesWidget);
}

void PluriNotes::updateSelectionFromTreePredecessors() {
    treeItemNoteAndPointer* itm = static_cast<treeItemNoteAndPointer*>(ui->treeViewPredecessors->currentItem());
    selectItemIntoList(findItemInList(itm->getNotePointer(), ui->listNotesWidget), ui->listNotesWidget);
}


void PluriNotes::retracteOrUnretracteArborescence() {
    QString text;
    QToolButton* button = ui -> showArborescenceButton;
    if (button->text() == QString(">")) {
        text = QString("<");
        button->setText(text);
        button->setMinimumHeight(400);

        ui->treeViewPredecessors->hide();
        ui->treeViewSuccessors->hide();
    }
    else{
        text = QString(">");
        button->setText(text);
        button->setMinimumHeight(200);
        ui->treeViewPredecessors->show();
        ui->treeViewSuccessors->show();
    }
}



