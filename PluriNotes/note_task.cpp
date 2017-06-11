#include "note_task.h"
#include "ui_plurinotes.h"
#include "application.h"
#include <QDateTime>

void Task::displayNote() const {
    PluriNotes& manager = PluriNotes::getManager();
    manager.setNoteTitle(getTitle());
    manager.setNoteDate(getCreationDate());
    setUiTaskAction(action);
    manager.setTaskPriority(priority);
    manager.setTaskStatus(status);
    manager.setTaskDeadline(deadline);
}

Task* Task::saveNote(QString title) {
    PluriNotes& manager = PluriNotes::getManager();
    return new Task(title, QDateTime::currentDateTime(), getUiTaskAction(), 0, manager.getTaskPriority(), manager.getTaskDeadline());
}

Task* Task::addVersion() const {
    PluriNotes& manager = PluriNotes::getManager();
    return new Task(manager.getNoteTitleEdit(), QDateTime::currentDateTime(), getUiTaskActionEdit(), manager.getTaskStatusEdit(), manager.getTaskPriorityEdit(), manager.getTaskDeadlineEdit());
}

bool Task::textChanged() const {
    PluriNotes& manager = PluriNotes::getManager();
    return action == getUiTaskActionEdit() && status == manager.getTaskStatusEdit() && priority == manager.getTaskPriorityEdit() && deadline == manager.getTaskDeadlineEdit();
}

void Task::saveToXML(QXmlStreamWriter& stream) const {
    stream.writeStartElement("version");
    stream.writeTextElement("title",getTitle());
    stream.writeTextElement("action", action);
    stream.writeTextElement("status", QString::number(status));
    stream.writeTextElement("priority", QString::number(priority));
    stream.writeTextElement("deadline",deadline.toString("dddd dd MMMM yyyy hh:mm:ss"));
    stream.writeTextElement("date",getCreationDate().toString("dddd dd MMMM yyyy hh:mm:ss"));
    stream.writeEndElement();
}

void Task::loadFromXML(QXmlStreamReader& stream, NoteEntity& newNoteEntity) const {
    QString title, action;
    unsigned int status, priority;
    QDateTime date, deadline;
    Task *newNote;
    while(!(stream.tokenType() == QXmlStreamReader::EndElement && stream.name() == "versions")) {
        if(stream.tokenType() == QXmlStreamReader::StartElement && stream.name() == "version") {
            while(!(stream.tokenType() == QXmlStreamReader::EndElement && stream.name() == "version")) {
                if(stream.tokenType() == QXmlStreamReader::StartElement) {
                    if(stream.name() == "title") {
                        stream.readNext(); title=stream.text().toString();
                    }
                    if(stream.name() == "action") {
                        stream.readNext(); action=stream.text().toString();
                    }
                    if(stream.name() == "status") {
                        stream.readNext(); status=stream.text().toInt();
                    }
                    if(stream.name() == "priority") {
                        stream.readNext(); priority=stream.text().toInt();
                    }
                    if(stream.name() == "deadline") {
                        stream.readNext(); deadline=QDateTime::fromString(stream.text().toString(),"dddd dd MMMM yyyy hh:mm:ss");
                    }
                    if(stream.name() == "date") {
                        stream.readNext(); date=QDateTime::fromString(stream.text().toString(),"dddd dd MMMM yyyy hh:mm:ss");
                    }
                }
                stream.readNext();
            }
            newNote = new Task(title, date, action, status, priority, deadline);
            newNoteEntity.addVersion(*newNote);
        }
        stream.readNext();
    }
}


// UI
void Task::setUiTaskAction(const QString& action) const {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    ui->taskDisplayAction->setText(action);
}


const QString Task::getUiTaskActionEdit() const {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    return ui->taskDisplayAction->toPlainText();
}

const QString Task::getUiTaskAction() const {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    return ui->taskAction->toPlainText();
}
