#include "application.h"
#include "ui_plurinotes.h"
#include "othertools.h"
#include "notes.h"
#include <QDateTime>

#include "commands.h"
#include <QtWidgets>

PluriNotes::PluriNotes(QWidget *parent) : QMainWindow(parent), ui(new Ui::PluriNotes) {
    //Constructeur de la classe PluriNotes
    ui->setupUi(this);
    //Chargement des notes existantes
    load();
    //Chargement des différents types de notes dont il faut proposer la création
    map<QString,NoteElement*> myMap = NoteElement::getTypesNotes();
    for (MapIterator iter = myMap.begin(); iter != myMap.end(); iter++) {
        ui->TypeComboBox->addItem(iter->first);
    }
    //Affiche l'écran de démarrage
    if(notes.size()) {
        ui->mainStackedWidget->setCurrentIndex(0);
        //Sélectionner la note active
        ui->listNotesWidget->item(0)->setSelected(true);
    }
    else {
        ui->mainStackedWidget->setCurrentIndex(2);
    }

    //! Creation of the undo stack
    undoStack = new QUndoStack(this);

    createActions();
    createMenus();

    createUndoView();

}



void PluriNotes::createUndoView()
{
    undoView = new QUndoView(undoStack);
    undoView->setWindowTitle(tr("Command List"));
    undoView->show();
    undoView->setAttribute(Qt::WA_QuitOnClose, false);
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

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    /*
    aboutAction = new QAction(tr("&About"), this);
    QList<QKeySequence> aboutShortcuts;
    aboutShortcuts << tr("Ctrl+A") << tr("Ctrl+B");
    aboutAction->setShortcuts(aboutShortcuts);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    */
}

void PluriNotes::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
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



PluriNotes::~PluriNotes() {
    //Destructeur de la classe PluriNotes
    save();
    delete ui;
    if(instanceUnique) delete instanceUnique;
    instanceUnique = nullptr;
    notes.clear();
    corbeille.clear();
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
    typeChanged();
}


void PluriNotes::setTextContentArticle(const QString& c){
    ui->noteTextContent->setText(c);
}

void PluriNotes::setNoteId(const QString& i){
    ui->noteTextId->setText(i);
}


void PluriNotes::setNoteTitle(const QString& t){
    ui->noteTextTitle->setText(t);
}

void PluriNotes::setNoteDate(const QDateTime& d){
    ui->noteTextDate->setText(d.toString("dddd dd MMMM yyyy hh:mm:ss"));
}

void PluriNotes::displayNote() {
    if(notes.size()) {
        listItemAndPointer* item = static_cast<listItemAndPointer*> (ui->listNotesWidget->currentItem());
        NoteEntity* currentSelectedNote = item->getNotePointer();
        ui->noteTextId->setText(currentSelectedNote->getId());

        const NoteElement& note = currentSelectedNote->getLastVersion();
        note.displayNote();
        ui->mainStackedWidget->setCurrentIndex(0);
    } else {
        ui->mainStackedWidget->setCurrentIndex(2);
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
    save();
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
    //NoteEntity* currentSelectedNote = item->getNotePointer();

    //Enregistre dans le fichier
    //save();

    //Supprime la note selectionnée de listNotesWidget
    //qDeleteAll(ui->listNotesWidget->selectedItems());

    QUndoCommand *deleteCommand = new deleteNoteCommand(item);
    undoStack->push(deleteCommand);
}

//! \todo add error handling
void PluriNotes::moveToTrash(NoteEntity *noteEl){
    unsigned int i = 0;
    for (auto note: notes) {
        if (noteEl==note) {
            notes.erase(notes.begin()+i);
            corbeille.push_back(note);
            return;
        }
        ++i;
    }

    //! \todo error handling
}


void PluriNotes::moveBackFromTrash(NoteEntity* noteEl){
    unsigned int i = 0;
    for (auto note: corbeille) {
        if (noteEl==note) {
            corbeille.erase(corbeille.begin()+i);
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

void PluriNotes::typeChanged() {
    //Suppression des champs non communs
    while (ui->formNoteWidget->count() > 7) {
        QLayoutItem* temp = ui->formNoteWidget->itemAt(6);
        temp->widget()->hide();
        ui->formNoteWidget->removeItem(temp);
        delete temp;
    }
    //Ajout des champs selon le type de note
    map<QString,NoteElement*> myMap = NoteElement::getTypesNotes();
    for (auto widget: myMap[ui->TypeComboBox->currentText()]->champsForm()) {
        ui->formNoteWidget->insertWidget(6,widget,0);
    }
}

PluriNotes& PluriNotes::getManager() {
    if(!instanceUnique) instanceUnique = new PluriNotes;
    return *instanceUnique;
}

void PluriNotes::save() const {
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
}


listItemAndPointer* PluriNotes::addNote(NoteEntity *note){
    notes.push_back(note);
    listItemAndPointer* item = addNoteToList(note);
    return item;
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
