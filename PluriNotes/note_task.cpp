#include "note_task.h"
#include "ui_plurinotes.h"
#include "application.h"
#include <QDateTime>


void Tache::displayNote() const {
    PluriNotes& manager = PluriNotes::getManager();
    manager.setNoteTitle(this->getTitle());
    manager.setNoteDate(this->getCreationDate());
    manager.setNoteContent(this->getAction());
    //Status
    QLabel* statusDisplayLabel = new QLabel(QString("Status"));
    QLineEdit* statusDisplayLineEdit = new QLineEdit(getStatus());
    manager.getUi()->displayNoteWidget->insertWidget(8, statusDisplayLineEdit, 0);
    manager.getUi()->displayNoteWidget->insertWidget(8, statusDisplayLabel, 0);
    //Priority
    QLabel* priorityDisplayLabel = new QLabel(QString("Priority"));
    QLineEdit* priorityDisplayLineEdit = new QLineEdit(getPriority());
    manager.getUi()->displayNoteWidget->insertWidget(8, priorityDisplayLineEdit, 0);
    manager.getUi()->displayNoteWidget->insertWidget(8, priorityDisplayLabel, 0);
}

QList<QWidget*> Tache::champsForm() {
    laction = new QLabel(QString("Tache"));
    actionFormZone = new QTextEdit();
    lprio = new QLabel(QString("Priorité"));
    taskPrioForm = new QComboBox();
    taskPrioForm->addItems(QStringList({"Faible","Normale","Elevée"}));
    taskPrioForm->setCurrentText(QString("Normale"));
    lstatus = new QLabel(QString("Statut"));
    taskStatusForm = new QComboBox();
    taskStatusForm->addItems(QStringList({"En attente","En cours","Accomplie"}));
    QList<QWidget*> listeWidgets;
    listeWidgets << actionFormZone << laction << taskStatusForm << lstatus << taskPrioForm << lprio;
    return listeWidgets;
}

Tache* Tache::saveNote(QString title) {
    QMap<QString, Status> stringToStatus;
    QMap<QString, Priority> stringToPrio;

    stringToStatus.insert("En attente", awaiting);
    stringToStatus.insert("En cours", pending);
    stringToStatus.insert("Accomplie", finished);
    stringToPrio.insert("Faible", low);
    stringToPrio.insert("Normale", normal);
    stringToPrio.insert("Elevée", high);

    Status taskStatus = stringToStatus[taskStatusForm->currentText()];
    Priority taskPrio = stringToPrio[taskPrioForm->currentText()];
    return new Tache(title, QDateTime::currentDateTime(), actionFormZone->toPlainText(), taskStatus, taskPrio);
}

const QString Tache::getPriority() const {
    QMap<Priority, QString> prioToString;
    prioToString.insert(low, "Faible");
    prioToString.insert(normal, "Normale");
    prioToString.insert(high, "Elevée");
    return prioToString[this->taskPrio];
}

const QString Tache::getStatus() const {
    QMap<Status, QString> statusToString;
    statusToString.insert(awaiting, "En attente");
    statusToString.insert(pending, "En cours");
    statusToString.insert(finished, "Accomplie");
    qDebug() << statusToString << this->taskStatus << statusToString[this->taskStatus];
    return statusToString[this->taskStatus];
}

Tache* Tache::addVersion() const {
    //return new Tache(title, QDateTime::currentDateTime(), descr->text());
}
