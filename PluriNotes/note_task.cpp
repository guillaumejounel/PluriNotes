#include "note_task.h"
#include "ui_plurinotes.h"
#include <QDateTime>

void Task::displayNote() const {
    setUiNoteTitle(getTitle());
    setUiNoteDate(getCreationDate());
    setUiTaskAction(action);
    setUiTaskPriority(priority);
    setUiTaskStatus(status);
    setUiTaskDeadline(deadline);
}

Task* Task::saveNote(QString title) {
    return new Task(title, QDateTime::currentDateTime(), getUiTaskAction(), 0, getUiTaskPriority(), getUiTaskDeadline());
}

Task* Task::addVersion() const {
    return new Task(getUiNoteTitleEdit(), QDateTime::currentDateTime(), getUiTaskActionEdit(), getUiTaskStatusEdit(), getUiTaskPriorityEdit(), getUiTaskDeadlineEdit());
}

bool Task::textChanged() const {
    return action == getUiTaskActionEdit() && status == getUiTaskStatusEdit() && priority == getUiTaskPriorityEdit() && deadline == getUiTaskDeadlineEdit();
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


void Task::setUiTaskStatus(unsigned int i) const {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    ui->taskDisplayStatus->setCurrentIndex(i);
}


unsigned int Task::getUiTaskStatusEdit() const {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    return ui->taskDisplayStatus->currentIndex();
}


void Task::setUiTaskPriority(unsigned int i) const {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    ui->taskDisplayPriority->setCurrentIndex(i);
}


unsigned int Task::getUiTaskPriority() const {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    return ui->taskPriority->currentIndex();
}

unsigned int Task::getUiTaskPriorityEdit() const {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    return ui->taskDisplayPriority->currentIndex();
}




const QDateTime Task::getUiTaskDeadline() const  {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    return ui->taskDeadline->dateTime();
}



void Task::setUiTaskDeadline(const QDateTime& date)const  {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    ui->taskDisplayDeadline->setDateTime(date);
}


const QDateTime Task::getUiTaskDeadlineEdit()const  {
    Ui::PluriNotes * ui = PluriNotes::getManager().getUi();
    return ui->taskDisplayDeadline->dateTime();
}
