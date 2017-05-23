#include "application.h"
#include "ui_plurinotes.h"
#include "notes.h"

#include <iostream>
#include <QInputDialog>
#include <QLineEdit>
#include <QScrollArea>



PluriNotes::PluriNotes(QWidget *parent) : QMainWindow(parent), ui(new Ui::PluriNotes) {
    ui->setupUi(this);
    ui->mainStackedWidget->setCurrentIndex(0);
    load();

    map<QString,NoteElement*> myMap = NoteElement::getTypesNotes();
    for (MapIterator iter = myMap.begin(); iter != myMap.end(); iter++) {
        ui->TypeComboBox->addItem(iter->first);
    }
}

PluriNotes::~PluriNotes() {
    delete ui;
    if(instanceUnique) delete instanceUnique;
    instanceUnique = nullptr;
    notes.clear();
    corbeille.clear();
}

void PluriNotes::toNewNoteForm() {
    is_idChanged = false;
    ui->ButtonNewNote->setEnabled(false);
    ui->idLineEdit->setText("");
    ui->titleLineEdit->setText("");
    //REVOIR ui->contentTextEdit->setPlainText("");
    ui->TypeComboBox->setCurrentIndex(0);
    ui->mainStackedWidget->setCurrentIndex(1);
    ui->listNotesWidget->setEnabled(false);
    typeChanged();
}


void PluriNotes::setTextContentArticle(const QString& c){
    ui->noteTextContent->setText(c);
}

void PluriNotes::setNoteId(const QString &i){
    ui->noteTextId->setText(i);
}


void PluriNotes::setNoteTitle(const QString &t){
    ui->noteTextTitle->setText(t);
}

void PluriNotes::displayNote() {
    listItemAndPointer* item = static_cast<listItemAndPointer*> (ui->listNotesWidget->currentItem());
    NoteEntity* currentSelectedNote = item->getNotePointer();
    ui->noteTextId->setText(currentSelectedNote->getId());

    const NoteElement& note = currentSelectedNote->getLastVersion();
    note.displayNote();
    ui->mainStackedWidget->setCurrentIndex(0);

}

void PluriNotes::saveNote() {
    //Faire des vérifications de validité (id...)
    //Puis créer la note
    qDebug() << "Creation of \"" << ui->titleLineEdit->text() << "\"";
    NoteEntity *newNoteEntity = new NoteEntity(ui->idLineEdit->text());

    map<QString,NoteElement*> myMap = NoteElement::getTypesNotes();
    const NoteElement* newNote = myMap[ui->TypeComboBox->currentText()]->saveNote();
    newNoteEntity->addVersion(*newNote);
    notes.push_back(newNoteEntity);


    listItemAndPointer* itm = new listItemAndPointer(newNoteEntity);
    itm->setText(newNoteEntity->getTitle());


    ui->listNotesWidget->addItem(itm);
    ui->mainStackedWidget->setCurrentIndex(0);
    ui->ButtonNewNote->setEnabled(true);
    ui->listNotesWidget->setEnabled(true);
    save();
}

void PluriNotes::cancelNote() {
    ui->ButtonNewNote->setEnabled(true);
    ui->listNotesWidget->setEnabled(true);
    ui->mainStackedWidget->setCurrentIndex(0);
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
    while (ui->formNoteWidget->count() > 7) {
        QLayoutItem* temp = ui->formNoteWidget->itemAt(6);
        temp->widget()->hide();
        ui->formNoteWidget->removeItem(temp);
        free(temp);
    }
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
                QString content;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "article")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); id=xml.text().toString();
                            qDebug()<<"id="<<id<<"\n";
                        }

                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); title=xml.text().toString();
                            qDebug()<<"title="<<title<<"\n";
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
                const Article *newNote = new Article(QString(title), QString(content));
                newNoteEntity->addVersion(*newNote);
                notes.push_back(newNoteEntity);
                listItemAndPointer* itm = new listItemAndPointer(newNoteEntity);
                itm->setText(title);
                ui->listNotesWidget->addItem(itm);
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
