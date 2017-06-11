#include "application.h"
#include "ui_plurinotes.h"
#include "othertools.h"
#include "notes.h"
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

    //Load data from UML
    load();

    //! \toto delete
    testFunction();

    //! Load data into UI
    loadDataIntoUi();

    //Affiche l'écran de démarrage
    ui->mainStackedWidget->setCurrentIndex(3);
}

void PluriNotes::testFunction(){
    Relation* ref = relations[0];
    QString l = QString("couple 1");
    NoteCouple& c = *(new NoteCouple(l,notes[0],notes[1]));
    ref->addCouple(c);


    l = QString("couple 2");
    c = *(new NoteCouple(l,notes[1],notes[2]));
    ref->addCouple(c);
}

const QString PluriNotes::getNoteTitleEdit() {
    return ui->titleDisplayLineEdit->text();
}


const QString PluriNotes::getArticleContent() {
    return ui->articleContent->toPlainText();
}

const QString PluriNotes::getArticleContentEdit() {
    return ui->articleDisplayContent->toPlainText();
}

unsigned int PluriNotes::getTaskPriority() {
    return ui->taskPriority->currentIndex();
}

const QString PluriNotes::getTaskAction() {
    return ui->taskAction->toPlainText();
}

const QDateTime PluriNotes::getTaskDeadline() {
    return ui->taskDeadline->dateTime();
}

unsigned int PluriNotes::getTaskPriorityEdit() {
    return ui->taskDisplayPriority->currentIndex();
}

unsigned int PluriNotes::getTaskStatusEdit() {
    return ui->taskDisplayStatus->currentIndex();
}

const QString PluriNotes::getTaskActionEdit() {
    return ui->taskDisplayAction->toPlainText();
}

const QDateTime PluriNotes::getTaskDeadlineEdit() {
    return ui->taskDisplayDeadline->dateTime();
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


void PluriNotes::saveApplication(){
    save();
}


void PluriNotes::openRelationsWindow(){
    relationsView->show();
    setEnabled(false);
}

void PluriNotes::showUndoHistoryWindows(){
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
    ui->idLineEdit->setText("");
    ui->titleLineEdit->setText("");
    ui->TypeComboBox->setCurrentIndex(0);
    ui->listNotesWidget->setEnabled(false);
    ui->mainStackedWidget->setCurrentIndex(1);
    typeChangedForm();
}

//void PluriNotes::setNoteId(const QString& i){
//    ui->idDisplayLineEdit->setText(i);
//}

void PluriNotes::setArticleContent(const QString& content) {
    ui->articleDisplayContent->setPlainText(content);
}

void PluriNotes::setNoteTitle(const QString& t){
    ui->titleDisplayLineEdit->setText(t);
}

void PluriNotes::setNoteDate(const QDateTime& d){
    ui->dateDisplayLineEdit->setText(d.toString("dddd dd MMMM yyyy hh:mm:ss"));
}

void PluriNotes::setTaskAction(const QString& action) {
    ui->taskDisplayAction->setText(action);
}

void PluriNotes::setTaskStatus(unsigned int i) {
    ui->taskDisplayStatus->setCurrentIndex(i);
}

void PluriNotes::setTaskPriority(unsigned int i) {
    ui->taskDisplayPriority->setCurrentIndex(i);
}

void PluriNotes::setTaskDeadline(const QDateTime& date) {
    ui->taskDisplayDeadline->setDateTime(date);
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

void PluriNotes::saveNote() {
    //Enregistre dans le vecteur notes de la classe PluriNotes
    //! \todo Faire des vérifications de validité (id...)
    //Puis créer la note
    NoteEntity *newNoteEntity = new NoteEntity(ui->idLineEdit->text());

    map<QString,NoteElement*> myMap = NoteElement::getTypesNotes();
    NoteElement* newNote = myMap[ui->TypeComboBox->currentText()]->saveNote(ui->titleLineEdit->text());
    QDateTime creationDate = QDateTime::currentDateTime();
    newNote->setCreationDate(creationDate);
    newNoteEntity->addVersion(*newNote);

    QUndoCommand *addCommand = new addNoteEntityCommand(newNoteEntity);
    undoStack->push(addCommand);

    //Impossible d'enregistrer des documents pour le moment !
    //Il faut refaire save() pour qu'il s'adapte à tout type de note
    //(créer une méthode virtuelle pure comme pour les boutons...)
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

bool PluriNotes::isInsideApp(const NoteEntity *note){
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
void PluriNotes::moveToTrash(NoteEntity *noteEl){
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


void PluriNotes::moveBackFromTrash(NoteEntity* noteEl){
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
    if (!is_idChanged) { ui->idLineEdit->setText(currentTitle); } //Modifier id
}

void PluriNotes::idChanged() {
    //Si l'id est modifié manuellement, on arrête de le changer automatiquement
    is_idChanged = true;
    //Checker ici si l'id n'est pas déjà pris
}

void PluriNotes::typeChangedForm() {
    //Ajout des champs selon le type de note
    map<QString,NoteElement*> myMap = NoteElement::getTypesNotes();
    ui->customWidgets->setCurrentIndex(myMap[ui->TypeComboBox->currentText()]->indexPageCreation());
    ui->taskDeadline->setDateTime(QDateTime::currentDateTime());
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
    stream.writeStartElement("notes");
    //à terminer !
    for(auto const& note: notes) {
        stream.writeStartElement("article");
        stream.writeTextElement("id",note->getId());
        stream.writeTextElement("title",note->getTitle());
        const Article *noteContent = dynamic_cast<const Article*>(&note->getLastVersion());
        stream.writeTextElement("creationDate",noteContent->getCreationDate().toString("dddd dd MMMM yyyy hh:mm:ss"));
        stream.writeTextElement("content",noteContent->getText());
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
        qDebug() << "Erreur ouverture fichier notes";
    }
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next.
            if(xml.name() == "notes") continue;
            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "article") {
                qDebug()<<"new article\n";
                QString id;
                QString title;
                QString creationDate;
                QString content;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "article")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificateur.
                        if(xml.name() == "id") {
                            xml.readNext(); id=xml.text().toString();
                            qDebug()<<"id="<<id<<"\n";
                        }

                        // We've found title.
                        if(xml.name() == "title") {
                            xml.readNext(); title=xml.text().toString();
                            qDebug()<<"title="<<title<<"\n";
                        }


                        // We've found date.
                        if(xml.name() == "creationDate") {
                            xml.readNext(); creationDate=xml.text().toString();
                            qDebug()<<"creationDate="<<creationDate<<"\n";
                        }


                        // We've found text
                        if(xml.name() == "content") {
                            xml.readNext();
                            content=xml.text().toString();
                            qDebug()<<"content="<<content<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout note "<<id<<"\n";
                NoteEntity *newNoteEntity = new NoteEntity(QString(id));
                const Article *newNote = new Article(QString(title), QDateTime::fromString(QString(creationDate),"dddd dd MMMM yyyy hh:mm:ss"), QString(content));
                newNoteEntity->addVersion(*newNote);
                notes.push_back(newNoteEntity);
                listItemAndPointer* itm = new listItemAndPointer(newNoteEntity);
                itm->setText(title);
                ui->listNotesWidget->insertItem(0, itm);
            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        qDebug() << "Erreur lecteur fichier notes, parser xml";
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";

    setDataChanged(false);
}

void PluriNotes::loadDataIntoUi(){
    //! \todo add loading functionnalities to trash and notes

     for(auto& rel: relations){
         static_cast<relationsWindows*>(relationsView)->addRelationToList(const_cast<Relation*>(rel));
     }
}


listItemAndPointer* PluriNotes::addNote(NoteEntity *note){
    notes.push_back(note);
    listItemAndPointer* item = addNoteToList(note);
    return item;
}

void PluriNotes::removeNote(NoteEntity *note){
    notes.removeAll(note);
}

//! \todo add item to list based on last modified date !
listItemAndPointer* PluriNotes::addNoteToList(NoteEntity* note){
    listItemAndPointer* itm = new listItemAndPointer(note);
    itm->setText(note->getTitle());
    addItemNoteToList(itm);
    return itm;
}


void PluriNotes::addItemNoteToList(listItemAndPointer *item){
    ui->listNotesWidget->insertItem(0, item);
    ui->listNotesWidget->setCurrentRow(0);
    ui->mainStackedWidget->setCurrentIndex(0);
    ui->ButtonNewNote->setEnabled(true);
    ui->listNotesWidget->setEnabled(true);
}


listItemAndPointer* PluriNotes::removeItemNoteFromList(listItemAndPointer* item){
    unsigned int i = ui->listNotesWidget->row(item);
    return static_cast<listItemAndPointer*>(ui->listNotesWidget->takeItem(i));
}

//! ####################################
//! ####################################
void PluriNotes::removeNoteFromList(NoteEntity *note){
    QListWidget* panel = ui->listNotesWidget;

    //We remove the item from the panel
    //! \todo check if have to use delete for memomry
    unsigned int i = panel->row(findItemInList(note));
    panel->takeItem(i);
}

listItemAndPointer* PluriNotes::findItemInList(NoteEntity* note){
    //! \todo add function to loog for wich panel the note is on!
    QListWidget* panel = ui->listNotesWidget;

    unsigned int nbItems = panel->count();
    listItemAndPointer* current;

    QString idWeAreLookingFor = note->getId();

    // We have to go throw all items in the list to know where is note
    unsigned int i=0;
    for(i=0; i<nbItems; i++){
        current = static_cast<listItemAndPointer*>(panel->item(i));
        if (current->getNotePointer()->getId() == idWeAreLookingFor) break;
    }

    return current;
}

void PluriNotes::selectItemIntoList(listItemAndPointer* item){
    QListWidget* panel = ui->listNotesWidget;
    panel->setCurrentItem(item);
}



//! \todo add item to list based on last modified date !
treeItemNoteAndPointer* PluriNotes::addNoteToTree(NoteEntity* note, QTreeWidget* tree){
    treeItemNoteAndPointer* itm = new treeItemNoteAndPointer(note);
    itm->setText(0,note->getTitle());
    tree->insertTopLevelItem(0,itm);
    addNoteChildToTree(itm,tree);
    return itm;
}


void PluriNotes::addNoteChildToTree(treeItemNoteAndPointer* item, QTreeWidget* tree){
    QSet<NoteEntity*> noteChildren;
    if(tree == ui->treeViewPredecessors) {
        noteChildren = getAllPredecessorsOf(item->getNotePointer());
    }
    else{
        noteChildren = getAllSuccessorsOf(item->getNotePointer());
    }


    treeItemNoteAndPointer* child;

    for (auto note : noteChildren){
        child = new treeItemNoteAndPointer(note);
        child->setText(0,note->getTitle());
        item->addChild(child);
    }
}



void PluriNotes::updateTrees(NoteEntity* note){
    ui->treeViewPredecessors->clear();
    ui->treeViewSuccessors->clear();

    QSet<NoteEntity*> successorsOfNote = getAllSuccessorsOf(note);
    QSet<NoteEntity*> predecessorsOfNote = getAllPredecessorsOf(note);

    for(auto note : successorsOfNote){
        addNoteToTree(note,ui->treeViewSuccessors);
    }

    for(auto note : predecessorsOfNote){
        addNoteToTree(note,ui->treeViewPredecessors);
    }
}

//! ####################################
//! ####################################

void PluriNotes::setDataChanged(bool b) {
    dataChanged = b;
    saveAction->setEnabled(b);
}


void PluriNotes::closeEvent(QCloseEvent *event){
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


unsigned int PluriNotes::getMaxRelationId(){
    unsigned int nbOfRealations = relations.size();
    //return nbOfRealations;

    if (nbOfRealations == 0) return 0;

    unsigned int max = 0;

    for (unsigned int i = 0; i < nbOfRealations ; i++){
        if( (relations[i])->getNumber() > max) max = (relations[i])->getNumber();
    }

    return max;
}



Relation* PluriNotes::getReferencesRelation(){
    unsigned int nbOfRelations = relations.size();
    for (unsigned int i = 0; i < nbOfRelations ; i++){
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
    for (unsigned int i = 0; i < nbOfRealations ; i++){
        result = result + (relations[i])->successorsOf(note);
    }

    return result;
}

QSet<NoteEntity*> PluriNotes::getAllPredecessorsOf(NoteEntity* note) const{
    unsigned int nbOfRealations = relations.size();
    QSet<NoteEntity*> result;

    // Quick way to get all successors;
    for (unsigned int i = 0; i < nbOfRealations ; i++){
        result = result + (relations[i])->predecessorsOf(note);
    }

    return result;
}


void PluriNotes::updateSelectionFromTreeSuccessors(){
    qWarning()<<QString("Enter updateSelectionFromTreeSuccessors");
    treeItemNoteAndPointer* itm = static_cast<treeItemNoteAndPointer*>(ui->treeViewSuccessors->currentItem());
    selectItemIntoList(findItemInList(itm->getNotePointer()));
}

void PluriNotes::updateSelectionFromTreePredecessors(){
    qWarning()<<QString("Enter updateSelectionFromTreePredecessors");
    treeItemNoteAndPointer* itm = static_cast<treeItemNoteAndPointer*>(ui->treeViewPredecessors->currentItem());
    selectItemIntoList(findItemInList(itm->getNotePointer()));
}
