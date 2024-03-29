#include "application.h"
#include "ui_plurinotes.h"
#include "relationswindows.h"

#include <QDateTime>

#include "commands.h"
#include <QtWidgets>
#include <QFileDialog>

PluriNotes& PluriNotes::getManager() {
    if(!instanceUnique) instanceUnique = new PluriNotes;
    return *instanceUnique;
}

PluriNotes::PluriNotes(QWidget *parent) : QMainWindow(parent), ui(new Ui::PluriNotes) {
    //Constructeur de la classe PluriNotes
    ui->setupUi(this);

    //Chargement des différents types de notes dont il faut proposer la création
    map<QString,NoteElement*> myMap = NoteElement::getTypesNotes();
    for (map<QString,NoteElement*>::const_iterator iter = myMap.begin(); iter != myMap.end(); iter++) {
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
    ui->noteBox->setCurrentIndex(0);
}


void PluriNotes::noteCountUpdate() {
    ui->noteBox->setItemText(0, QString("Active notes (") + QString::number(ui->listNotesWidget->count()) + QString(")"));
    ui->noteBox->setItemText(1, QString("Archived (") + QString::number(ui->listArchivedWidget->count()) + QString(")"));
    ui->noteBox->setItemText(2, QString("Trash (") + QString::number(ui->listTrashWidget->count()) + QString(")"));
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
    static_cast<relationsWindows*>(relationsView)->displayRelation();
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



    windowsMenu = menuBar()->addMenu(tr("&Windows"));
    windowsMenu->addAction(viewUndoHistory);
    windowsMenu->addAction(openRelations);
}



void PluriNotes::createActions()
{
    undoAction = undoStack->createUndoAction(this, tr("&Undo"));
    undoAction->setShortcuts(QKeySequence::Undo);


    QList<QKeySequence> shortcutsRedo;
    shortcutsRedo << QKeySequence::Redo << QKeySequence("Ctrl+y");

    redoAction = undoStack->createRedoAction(this, tr("&Redo"));
    redoAction->setShortcuts(shortcutsRedo);

    saveAction = new QAction(tr("S&ave"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveApplication()));
    saveAction->setEnabled(false);

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    viewUndoHistory = new QAction(tr("View History"), this);
    connect(viewUndoHistory, SIGNAL(triggered()), this, SLOT(showUndoHistoryWindows()));

    openRelations = new QAction(tr("Manage Relation"), this);
    connect(openRelations,SIGNAL(triggered()),this, SLOT(openRelationsWindow()));
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
    ui->noteBox->setCurrentIndex(0);
    setInteractivity(false);
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

void PluriNotes::setInteractivity(bool b, unsigned int type){
    if (type == 0){
        ui->noteBox->setEnabled(b);
        ui->treeViewPredecessors->setEnabled(b);
        ui->treeViewSuccessors->setEnabled(b);
        ui->manageRelationButton->setEnabled(b);
        ui->ButtonNewNote->setEnabled(b);
        ui->filterComboBox->setEnabled(b);
    } else if (type==1){ //when we are in archived
        ui->titleDisplayLineEdit->setEnabled(b);
        ui->buttonCancelEdit->setEnabled(b);
        ui->buttonSaveEdit->setEnabled(b);
        ui->deleteNoteButton->setEnabled(b);

        //Task
        ui->taskAction->setEnabled(b);
        ui->taskDisplayAction->setEnabled(b);
        ui->taskDeadline->setEnabled(b);
        ui->taskDisplayPriority->setEnabled(b);
        ui->taskDisplay->setEnabled(b);

        //Content
        ui->documentDescription->setEnabled(b);
        ui->documentDisplay->setEnabled(b);
        ui->documentDisplayFileButton->setEnabled(b);

        //Article
        ui->articleDisplayContent->setEnabled(b);

    }

}

NoteEntity* PluriNotes::getCurrentNote() {
    int nb = ui->noteBox->currentIndex();
    listItemAndPointer* item = nullptr;
    if (nb == 0 && ui->listNotesWidget->count() != 0){
        item = static_cast<listItemAndPointer*> (ui->listNotesWidget->currentItem());
    } else if (nb == 1 && ui->listArchivedWidget->count() != 0){
        item = static_cast<listItemAndPointer*> (ui->listArchivedWidget->currentItem());
    } else if (nb == 2 && ui->listTrashWidget->count() != 0){
        return nullptr; // it is in trash
    }
    if (item != nullptr) return item->getNotePointer();
    ui->mainStackedWidget->setCurrentIndex(2);
    return nullptr;
}

QString PluriNotes::getCurrentNoteType() {
    return getCurrentNote()->getLastVersion()->typeName();
}

void PluriNotes::displayNote(unsigned int n) {
    noteCountUpdate();
    setInteractivity(true,1);
    ui->idDisplayLineEdit->setReadOnly(true);
    ui->dateDisplayLineEdit->setReadOnly(true);
    if (!n) ui->buttonSaveEdit->setText(QString("Save"));
    const NoteEntity* currentSelectedNote = getCurrentNote();

    isDisplayed = 0;


    if(notes.size() && currentSelectedNote!= nullptr) {
        ui->noteTypeDisplayLabel->setText(QString("<html><head/><body><p><span style='font-size:24pt;'>")+getCurrentNoteType()+ QString("</span></p></body></html>"));
        ui->idDisplayLineEdit->setText(currentSelectedNote->getId());
        ui->noteTextVersion->clear();
        updateTrees(const_cast<NoteEntity*>(currentSelectedNote));
        if (currentSelectedNote->getSize() == 1) {
            ui->noteTextVersion->addItem(QString("Version 1"));
            ui->noteTextVersion->setEnabled(0);
        } else {
            ui->noteTextVersion->setEnabled(1);
            for(unsigned int i = currentSelectedNote->getSize(); i > 0; --i)
                ui->noteTextVersion->addItem(QString("Version ") + QString::number(i));
            ui->noteTextVersion->setCurrentIndex(n);
        }
        n = ui->noteTextVersion->count() - ui->noteTextVersion->currentIndex() - 1;
        const NoteElement& note = currentSelectedNote->getVersion(n);
        ui->noteTypeDisplay->setCurrentIndex(note.indexPageCreation());
        //Ajout et remplissage des champs de type de note
        note.displayNote();
        ui->mainStackedWidget->setCurrentIndex(0);
        if (currentSelectedNote->hasIssues()) setInteractivity(false);
    } else {
        int nb = ui->noteBox->currentIndex();
        if (nb != 2)  ui->mainStackedWidget->setCurrentIndex(2);
        setInteractivity(true);
    }
    if (currentSelectedNote && currentSelectedNote->isArchived()) setInteractivity(false,1);
    isDisplayed = 1;
}

void PluriNotes::noteVersionChanged() {
    if (isDisplayed != 0) {
        displayNote(ui->noteTextVersion->currentIndex());
        if (ui->noteTextVersion->currentIndex() == 0 || isDisplayed == 2) {
            ui->buttonSaveEdit->setText(QString("Save"));
            ui->titleDisplayLineEdit->setReadOnly(0);
            ui->articleDisplayContent->setReadOnly(0);
            ui->taskDisplayAction->setReadOnly(0);
            ui->taskDisplayDeadline->setReadOnly(0);
            ui->taskDisplayPriority->setDisabled(0);
            ui->taskDisplayStatus->setDisabled(0);
            ui->documentDisplayDescription->setReadOnly(0);
            ui->documentDisplayFileButton->setDisabled(0);
        } else {
            ui->buttonSaveEdit->setText(QString("Restore"));
            ui->titleDisplayLineEdit->setReadOnly(1);
            ui->articleDisplayContent->setReadOnly(1);
            ui->taskDisplayAction->setReadOnly(1);
            ui->taskDisplayDeadline->setReadOnly(1);
            ui->taskDisplayPriority->setDisabled(1);
            ui->taskDisplayStatus->setDisabled(1);
            ui->documentDisplayDescription->setReadOnly(1);
            ui->documentDisplayFileButton->setDisabled(1);
        }
    }
}

void PluriNotes::selectDocumentFile() {
    QString lastFileName = ui->documentDisplayFile->text();
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open file"),
        QDir::homePath(),
        tr("Sound, Image or Video Files (*.gif *.png *.jpg *.bmp *.raw *.mp3 *.m4a *.wav *.flac *.wmv *.mp4 *.mkv *.m4v)")
        );
    if (fileName.isEmpty()) fileName = lastFileName;
    ui->documentFile->setText(fileName);
    ui->documentDisplayFile->setText(fileName);
}

void PluriNotes::openDocumentFolder() {
    QString fileDir = ui->documentDisplayFile->text();
    fileDir.remove(QRegExp("([^/]+$)"));
    QDesktopServices::openUrl(QUrl(QString("file:///")+fileDir, QUrl::TolerantMode));
}

void PluriNotes::openDocumentFile() {
    QDesktopServices::openUrl(QUrl(QString("file:///")+ui->documentDisplayFile->text(), QUrl::TolerantMode));
}

void PluriNotes::noteTextChanged() {
    if (ui->mainStackedWidget->currentIndex()==1) return;
    NoteEntity* currentNote = getCurrentNote();
    const NoteElement* note = currentNote->getLastVersion();
    if (note!=nullptr && currentNote!=nullptr){
        bool issue = currentNote->hasIssues();
        if(ui->noteTextVersion->currentIndex() != 0 && !issue) {
            setInteractivity(true);
            ui->buttonSaveEdit->setEnabled(1);
            ui->buttonCancelEdit->setEnabled(0);
        } else {
            if((ui->titleDisplayLineEdit->text() == note->getTitle() && note->textChanged()) && !issue) {
                setInteractivity(true);
                ui->buttonCancelEdit->setEnabled(0);
                ui->buttonSaveEdit->setEnabled(0);
            } else {
                setInteractivity(false);
                ui->buttonCancelEdit->setEnabled(1);
                ui->buttonSaveEdit->setEnabled(1);
            }
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

NoteEntity* PluriNotes::getNoteById(const QString& id) const {
    for (auto note : notes) {
        if(note->getId() == id) return note;
    }
    return nullptr;
}

void PluriNotes::saveNote() {
    map<QString,NoteElement*> myMap = NoteElement::getTypesNotes();
    bool flag = true;

    //Check validity
    if (ui->titleLineEdit->text().isEmpty() || ui->idLineEdit->text().isEmpty() || !isIdAvailable(ui->idLineEdit->text())) flag = false;
    for(QTextEdit* widget: ui->customWidgets->widget(myMap[ui->TypeComboBox->currentText()]->indexPageCreation())->findChildren<QTextEdit*>())
        if(widget->property("obligatory").toBool() && widget->toPlainText().isEmpty()) flag = false;

    for(QLineEdit* widget: ui->customWidgets->widget(myMap[ui->TypeComboBox->currentText()]->indexPageCreation())->findChildren<QLineEdit*>())
        if(widget->property("obligatory").toBool() && widget->text().isEmpty()) flag = false;

    //Create and save the note ; to check references it is easier
    NoteEntity *newNoteEntity = new NoteEntity(ui->idLineEdit->text());
    NoteElement* newNote = myMap[ui->TypeComboBox->currentText()]->saveNote(ui->titleLineEdit->text());
    QDateTime creationDate = QDateTime::currentDateTime();
    newNote->setCreationDate(creationDate);
    newNoteEntity->addVersion(*newNote);

    // references check
    bool references = refencesCheck(newNoteEntity->getLastVersion(),newNoteEntity,newNoteEntity->getId());

    if(flag && references) {
        setInteractivity(true);
        QUndoCommand *addCommand = new addNoteEntityCommand(newNoteEntity);
        undoStack->push(addCommand);
    } else {
        delete newNoteEntity;

        //Input is not valid
        if (references == false){
            QMessageBox::warning(this, "Warning", "Please check your input. You notably have references issues !");
            setInteractivity(false);
        }
        else QMessageBox::warning(this, "Warning", "Please check your inputs !\nStarred items must be filled in.");
    }
}


void PluriNotes::saveNewVersion() {
    // We get which note is selected
    NoteEntity& currentNote = *getCurrentNote();
    // We create a newVersion identical to the last one
    const NoteElement& currentVersion = *(currentNote.getLastVersion());

    const NoteElement& newVersion = *currentVersion.addVersion();


    bool references = refencesCheck(&newVersion,&currentNote,currentNote.getId());

    //Input is not valid
    if (references == false){
        if (ui->buttonSaveEdit->text()==QString("Restore")){
            isDisplayed = 2;
            noteVersionChanged();
        }
        delete &newVersion;
        QMessageBox::warning(this, "Warning", "Please check your input. You notably have references issues !");
        setInteractivity(false);
    }else{
        QUndoCommand *addVersionCommand = new addVersionNoteCommand(const_cast<NoteEntity*>(&currentNote),const_cast<NoteElement*>(&newVersion));
        undoStack->push(addVersionCommand);
        noteVersionChanged();
        //setInteractivity(true,1);
    }
}


void PluriNotes::deleteNote() {
    listItemAndPointer* item = static_cast<listItemAndPointer*> (ui->listNotesWidget->currentItem());
    NoteEntity* currentSelectedNote = item->getNotePointer();

    QUndoCommand *deleteCommand = new deleteNoteCommand(currentSelectedNote,0);
    undoStack->push(deleteCommand);
    displayNote();
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

}

void PluriNotes::cancelNote() {
    setInteractivity(true);
    ui->ButtonNewNote->setEnabled(true);
    ui->listNotesWidget->setEnabled(true);
    if (notes.size()) ui->mainStackedWidget->setCurrentIndex(0);
    else ui->mainStackedWidget->setCurrentIndex(2);
}

void PluriNotes::titleChanged() {
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
    ui->documentDescription->clear();
}


void PluriNotes::save() {
    QString path = QCoreApplication::applicationDirPath();
    path.append("/data");
    QFile newfile(path);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("data");
    {
        stream.writeStartElement("conf");
        stream.writeTextElement("autoEmpty",getAutoEmptyTrash()?"true":"false");
        stream.writeEndElement();

        stream.writeStartElement("notes");
            for(auto const& note: notes)
                note->saveToXML(stream);
        stream.writeEndElement();
        stream.writeStartElement("trash");
            for(auto const& note: trash)
                note->saveToXML(stream);
        stream.writeEndElement();
        stream.writeStartElement("relations");
            for(auto const& relation: relations)
                relation->saveToXML(stream);
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
        //
    }
    QXmlStreamReader xml(&fin);
    bool toTrash = false;
    NoteEntity* newNoteEntity;
    Relation* newRelation;
    while(!xml.atEnd() && !xml.hasError()) {

        if(xml.name()== "autoEmpty" && xml.tokenType() == QXmlStreamReader::StartElement ){
            xml.readNext(); QString b = xml.text().toString();
            if (b == QString("true")){
                ui->autoEmptyButton->setText(QString("Auto empty is on"));
                setAutoEmptyTrash(true);
            }
            else {
                ui->autoEmptyButton->setText(QString("Auto empty is off"));
                setAutoEmptyTrash(false);
            }

        }

        if(xml.name() == "trash") toTrash = true;
        if(xml.name() == "note" && xml.tokenType() == QXmlStreamReader::StartElement) {
            newNoteEntity = NoteEntity::loadFromXML(xml);
            if (toTrash) trash.push_back(newNoteEntity);
            else notes.push_back(newNoteEntity);
        }
        if(xml.name() == "relation" && xml.tokenType() == QXmlStreamReader::StartElement) {
            newRelation = Relation::loadFromXML(xml);
            if (newRelation != getReferencesRelation()) relations.push_back(newRelation);
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
    loadNotesIntoUi();
    loadRelationsIntoUi();

    noteCountUpdate();
}

void PluriNotes::loadNotesIntoUi() {
    if (ui->filterComboBox->currentIndex() == 1) {
        for(NoteEntity* note:notes) {
            if (note->getLastVersion()->typeName() == "Task") addNoteToList(note, note->isArchived()?ui->listArchivedWidget:ui->listNotesWidget);
        }
        for(NoteEntity* note:trash) {
            if (note->getLastVersion()->typeName() == "Task") addNoteToList(note, ui->listTrashWidget);
        }
    } else {
        for(NoteEntity* note:notes) {
            addNoteToList(note, note->isArchived()?ui->listArchivedWidget:ui->listNotesWidget);
        }
        for(NoteEntity* note:trash) {
            addNoteToList(note, ui->listTrashWidget);
        }
    }
}

void PluriNotes::loadRelationsIntoUi() {
    for(auto& rel: relations) {
        static_cast<relationsWindows*>(relationsView)->addRelationToList(const_cast<Relation*>(rel));
    }
}

void PluriNotes::filterDataIntoUi() {
    ui->listNotesWidget->clear();
    ui->listTrashWidget->clear();
    loadNotesIntoUi();
}


listItemAndPointer* PluriNotes::addNote(NoteEntity& note, QListWidget* list) {
    notes.push_back(&note);
    listItemAndPointer* item = addNoteToList(&note, list);
    return item;
}

void PluriNotes::removeNote(NoteEntity *note) {
    notes.removeAll(note);
}

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
    unsigned int i = list->row(findItemInList(note, list));
    list->takeItem(i);
}

listItemAndPointer* PluriNotes::findItemInList(NoteEntity* note, QListWidget* list) const {
    QListWidget* panel = list;

    unsigned int nbItems = panel->count();
    listItemAndPointer* current;
    listItemAndPointer* out = nullptr;


    QString idWeAreLookingFor = note->getId();

    // We have to go throw all items in the list to know where is note
    unsigned int i=0;
    for(i=0; i<nbItems; i++) {
        current = static_cast<listItemAndPointer*>(panel->item(i));
        if (current->getNotePointer()->getId() == idWeAreLookingFor) {
            out = current;
            break;
        }
    }

    return out;
}

void PluriNotes::selectItemIntoList(listItemAndPointer* item, QListWidget* list) const {
    QListWidget* panel = list;
    panel->setCurrentItem(item);
}



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

    if (note!=nullptr){

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

}

//! ####################################
//! ####################################

void PluriNotes::setDataChanged(bool b) {
    dataChanged = b;
    saveAction->setEnabled(b);
}


void PluriNotes::closeEvent(QCloseEvent *event) {
    event->ignore();
    if (getAutoEmptyTrash()){
        emptyTrashSlot(true);
    }

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


void PluriNotes::onRelationsWindowsClose(){
    for (auto rel : relations){
        if (rel->isDeleted() && (!rel->isReferences()) ){
            relations.removeAll(rel);
            delete rel;
        }
    }
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



QStringList PluriNotes::getActiveReferences() const {
    QStringList output;
    for (auto note : notes){
        if (!note->isArchived()) output += note->getId();
    }
    return output;
}



bool PluriNotes::refencesCheck(const NoteElement *noteEl, NoteEntity *note, QString id) const{
        QStringList referencesInNotes = noteEl->returnReferences();
        QStringList allActiveRefences = getActiveReferences();

        // references check
        if (referencesInNotes.contains(id)){
            note->setHasIssues(true);
            return false;
        }

        for (auto s : referencesInNotes ){
            // for all references in the field we check if they are valid
            if (!allActiveRefences.contains(s)){
                note->setHasIssues(true);
                return false;
            }
        }
        note->setHasIssues(false);
        return true;
}



void PluriNotes::addReferences(NoteEntity* note, const QStringList& idList){
    // We have first to build a list of NoteEntity* based on the list of ID
    QList<NoteEntity*> listOfNoteMatchingId;

    for(auto note : notes){
        if (idList.contains(note->getId())){
            listOfNoteMatchingId.append(note);
        }

    }

    QString label("ref");
    for (auto y : listOfNoteMatchingId){
        NoteCouple* couple = new NoteCouple(label, note, y);
        getReferencesRelation()->addCouple(couple);
    }
}

void PluriNotes::removeReferencesWithOrigin(NoteEntity* note){
    getReferencesRelation()->removeCoupleWithNotePredecessor(note);
}

void PluriNotes::superRedirecteEasy(NoteEntity* note) const{
    listItemAndPointer* tmp;
    tmp = findItemInList(note, ui->listNotesWidget);
    if (tmp != nullptr){
        selectItemIntoList(tmp, ui->listNotesWidget);
        ui->noteBox->setCurrentIndex(0);
        return;
    }

    tmp = findItemInList(note, ui->listArchivedWidget);
    if (tmp != nullptr){
        selectItemIntoList(tmp, ui->listArchivedWidget);
        ui->noteBox->setCurrentIndex(1);
        return;
    }

    tmp = findItemInList(note, ui->listTrashWidget);
    if (tmp != nullptr){
        selectItemIntoList(tmp, ui->listTrashWidget);
        ui->noteBox->setCurrentIndex(2);
        return;
    }


}

void PluriNotes::updateSelectionFromTreeSuccessors() {
    treeItemNoteAndPointer* itm = static_cast<treeItemNoteAndPointer*>(ui->treeViewSuccessors->currentItem());
    superRedirecteEasy(itm->getNotePointer());
}

void PluriNotes::updateSelectionFromTreePredecessors() {
    treeItemNoteAndPointer* itm = static_cast<treeItemNoteAndPointer*>(ui->treeViewPredecessors->currentItem());
    superRedirecteEasy(itm->getNotePointer());
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
        ui->manageRelationButton->hide();
    }
    else{
        text = QString(">");
        button->setText(text);
        button->setMinimumHeight(200);
        ui->treeViewPredecessors->show();
        ui->treeViewSuccessors->show();
        ui->manageRelationButton->show();
    }
}



void PluriNotes::emptyTrashSlot(bool out){
    // method may be used at exit, we don't want to show message box on exit...
    if (!out){

        QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this, "Warning !",
                                        "Emptying the trash is non-reversible and will also clear the history for coherence purpose.",
                                        QMessageBox::Cancel|QMessageBox::Ok);
          if (reply == QMessageBox::Ok) {
            emptyTrashSlot(true);
            setDataChanged(true);
          }
          displayNote();
    }
    else{
        undoStack->clear();
        for (auto note:trash){
            for(auto rel:relations){
                // We clean the different relations
                rel->removeCoupleWithNote(note);
            }
            delete note;
        }
        trash.clear();
        ui->listTrashWidget->clear();
    }

}

void PluriNotes::restoreTrashSlot(){
    listItemAndPointer* item = static_cast<listItemAndPointer*> (ui->listTrashWidget->currentItem());
    NoteEntity* currentSelectedNote = item->getNotePointer();

    QUndoCommand *deleteCommand = new deleteNoteCommand(currentSelectedNote,1);
    undoStack->push(deleteCommand);

    displayNote();
}

void PluriNotes::restoreArchiveSlot(){
    listItemAndPointer* item = static_cast<listItemAndPointer*> (ui->listArchivedWidget->currentItem());
    NoteEntity* currentSelectedNote = item->getNotePointer();

    QUndoCommand *deleteCommand = new deleteNoteCommand(currentSelectedNote,1);
    undoStack->push(deleteCommand);
}

void PluriNotes::checkArchiveSlot(){
    unsigned int n = 0;
    for(auto note : notes){
        if (note->isArchived() && !note->isReferenced(true)) n++;
    }

    if(n==0){
        //QMessageBox::warning(this, "Sorry", "We haven't found any modifcation to do...");
    } else { //he the can be some modification
        QString msg = QString("We found ")+ QString::number(n) + QString(" that we can move to the trash, do you want to proceed ?");
       if( QMessageBox::Yes == QMessageBox::question(this, "Move to trash?",
                                          msg,
                                          QMessageBox::Yes|QMessageBox::No)
         ){ // move to trash

           for(auto note : notes){
               if (note->isArchived() && !note->isReferenced(true)){
                   QUndoCommand *deleteCommand = new deleteNoteCommand(note,2);
                   undoStack->push(deleteCommand);
               }
           }
           ui->mainStackedWidget->setCurrentIndex(4);
       }
    }


}


void PluriNotes::showTrashSlot(int n){
    setInteractivity(true,1);
    if (n==2){
        if (ui->listTrashWidget->count() == 0){
            ui->mainStackedWidget->setCurrentIndex(5);
            ui -> emptyTrashButton -> setEnabled(false);
            ui-> restoreTrashButton -> setEnabled(false);
        }else {
            ui -> emptyTrashButton -> setEnabled(true);
            ui-> restoreTrashButton -> setEnabled(true);
            ui->mainStackedWidget->setCurrentIndex(4);
        }
    }else if (n==1){
        if (ui->listArchivedWidget->count()==0){
            ui->restoreArchivedButton->setEnabled(false);
        } else {
         checkArchiveSlot();
         ui->restoreArchivedButton->setEnabled(true);
        }
        displayNote();
    }else{
        displayNote();
        setInteractivity(true,1);
    }
}


void PluriNotes::setAutoEmptySlot(){
    setDataChanged(true);
    if (getAutoEmptyTrash()){
        setAutoEmptyTrash(false);
        ui->autoEmptyButton->setText(QString("Auto empty is off"));
    } else {
        setAutoEmptyTrash(true);
        ui->autoEmptyButton->setText(QString("Auto empty is on"));
    }
}
