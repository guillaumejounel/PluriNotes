#include "note_task.h"
#include "application.h"
#include <QDateTime>


void Tache::displayNote() const {
    // TODO: displayNote en fonction du type de note à afficher, il faut changer les champs de l'ui
    PluriNotes& manager = PluriNotes::getManager();
    manager.setActionContentTask(this->getAction());
    manager.setNoteTitle(this->getTitle());
}

QList<QWidget*> Tache::champsForm() {
    laction = new QLabel(QString("Tache"));
    actionFormZone = new QTextEdit();
    lprio = new QLabel(QString("Priorité"));
    taskPrioForm = new QComboBox();
    taskPrioForm->addItems(QStringList({"Faible","Normale","Haute"}));
    taskPrioForm->setCurrentText(QString("Normale"));
    lstatus = new QLabel(QString("Statut"));
    taskStatusForm = new QComboBox();
    taskStatusForm->addItems(QStringList({"En attente","En cours","Finie"}));
    QList<QWidget*> listeWidgets;
    listeWidgets << actionFormZone << laction << taskStatusForm << lstatus << taskPrioForm << lprio;
    return listeWidgets;
}

Tache* Tache::saveNote(QString title) {
    QMap<QString, Status> stringToStatus;
    QMap<QString, Priority> stringToPrio;

    stringToStatus.insert("En attente", awaiting);
    stringToStatus.insert("En cours", pending);
    stringToStatus.insert("Finie", finished);
    stringToPrio.insert("Faible", low);
    stringToPrio.insert("Normale", normal);
    stringToPrio.insert("Haute", high);

    Status taskStatus = stringToStatus[taskPrioForm->currentText()];
    Priority taskPrio = stringToPrio[taskPrioForm->currentText()];

    return new Tache(title, QDateTime::currentDateTime(), actionFormZone->toPlainText(), taskStatus, taskPrio);
}
