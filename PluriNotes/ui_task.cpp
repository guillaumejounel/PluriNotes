#include "ui_task.h"

ui_task::ui_task()
{

}


//-------
// Task related

void ui_task::initTaskForm() {
    ui->taskAction->clear();
    ui->taskPriority->setCurrentIndex(0);
    ui->taskDeadline->setDateTime(QDateTime::currentDateTime());
}





void ui_task::setTaskAction(const QString& action) {
    ui->taskDisplayAction->setText(action);
}

void ui_task::setTaskStatus(unsigned int i) {
    ui->taskDisplayStatus->setCurrentIndex(i);
}

void ui_task::setTaskPriority(unsigned int i) {
    ui->taskDisplayPriority->setCurrentIndex(i);
}

void ui_task::setTaskDeadline(const QDateTime& date) {
    ui->taskDisplayDeadline->setDateTime(date);
}



//! \todo add documentation
const QString getTaskAction();

//! \todo add documentation
const QString getTaskActionEdit();




//! \brief get task status edit from the UI
unsigned int getTaskStatusEdit();



//! \brief get Task Priority from thu ui
unsigned int getTaskPriority();

//! \brief get Task PriorityEdit from thu ui
unsigned int getTaskPriorityEdit();


//! \brief get the task deadline from the UI
const QDateTime getTaskDeadline();

//! \brief get the task deadlineEdit from the UI
const QDateTime getTaskDeadlineEdit();
//-------
