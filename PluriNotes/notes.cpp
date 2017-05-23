#include "notes.h"
#include "application.h"

NoteEntity::NoteEntity(const QString& id) : id(id){
}

QString NoteEntity::getId() const {return id;}

QString NoteEntity::getTitle() const{return versions.back() -> getTitle();}


void NoteEntity::addVersion(const NoteElement& newVersion) {
    versions.push_back(&newVersion);
}

const NoteElement& NoteEntity::getLastVersion() const {
    return *versions.back();
}

const map<QString, NoteElement*>& NoteElement::NoteTypeList(QString typeName, NoteElement* ptNote) {
    static map<QString, NoteElement*> ensTypeNote; //L'ensemble des noms des classes dérivées
    if (ptNote) ensTypeNote.insert(make_pair(typeName, ptNote));
    return ensTypeNote;
}

map<QString, NoteElement*> NoteElement::getTypesNotes() {
    return NoteTypeList("", nullptr);
}

void Article::displayNote() const {
    PluriNotes& manager = PluriNotes::getManager();
    manager.setTextContentArticle(this->getText());
    manager.setNoteTitle(this->getTitle());

    //ui->mainStackedWidget->setCurrentIndex(0);
}

void Document::displayNote() const {
    PluriNotes& manager = PluriNotes::getManager();
    manager.setTextContentArticle(this->getDescription());
    manager.setNoteTitle(this->getTitle());

    //ui->mainStackedWidget->setCurrentIndex(0);
}

QList<QWidget*> Article::champsForm() {
    testText = new QTextEdit();
    testLabel = new QLabel(QString("ok"));
    QList<QWidget*> listeWidgets;
    listeWidgets <<testText << testLabel;
    return listeWidgets;
}

Article* Article::saveNote(QString title)  {
    return new Article(title, testText->toPlainText());
}

QList<QWidget*> Document::champsForm() {
    fichier = new QLineEdit();
    descr = new QLineEdit();
    lfichier = new QLabel(QString("Fichier"));
    ldescr = new QLabel(QString("Description"));
    QList<QWidget*> listeWidgets;
    listeWidgets << fichier << lfichier << descr << ldescr;
    return listeWidgets;
}

Document* Document::saveNote(QString title) {
    return new Document(title, descr->text());
}

