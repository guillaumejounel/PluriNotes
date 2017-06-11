#include "note_task.h"
#include "ui_plurinotes.h"
#include "application.h"
#include <QDateTime>

void Task::displayNote() const {
    PluriNotes& manager = PluriNotes::getManager();
    manager.setNoteTitle(getTitle());
    manager.setNoteDate(getCreationDate());
    manager.setTaskAction(action);
    manager.setTaskPriority(priority);
    manager.setTaskStatus(status);
    manager.setTaskDeadline(deadline);
}

Task* Task::saveNote(QString title) {
    PluriNotes& manager = PluriNotes::getManager();
    return new Task(title, QDateTime::currentDateTime(), manager.getTaskAction(), 0, manager.getTaskPriority(), manager.getTaskDeadline());
}

Task* Task::addVersion() const {
    PluriNotes& manager = PluriNotes::getManager();
    return new Task(manager.getNoteTitleEdit(), QDateTime::currentDateTime(), manager.getTaskActionEdit(), manager.getTaskStatusEdit(), manager.getTaskPriorityEdit(), manager.getTaskDeadlineEdit());
}

bool Task::textChanged() const {
    PluriNotes& manager = PluriNotes::getManager();
    return action == manager.getTaskActionEdit() && status == manager.getTaskStatusEdit() && priority == manager.getTaskPriorityEdit() && deadline == manager.getTaskDeadlineEdit();
}

void Task::saveToXML(QXmlStreamWriter& stream) const {

}

void Task::loadFromXML(QXmlStreamReader& stream, NoteEntity& newNoteEntity) const {

}
