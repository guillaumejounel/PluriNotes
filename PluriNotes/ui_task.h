#ifndef UI_TASK_H
#define UI_TASK_H
#include "ui_plurinotes.h"


class ui_task{
private:
    Ui::PluriNotes* ui;
public:
    ui_task();
    void setUi(Ui::PluriNotes* uiToSet) {ui = uiToSet;}


    //-------
    // Task related
    //\todo move to an other class for better POO ?

    //! \brief Initialize the Task creation form
    void initTaskForm();

    //! \todo add documentation
    void setTaskAction(const QString& action);

    //! \todo add documentation
    const QString getTaskAction();

    //! \todo add documentation
    const QString getTaskActionEdit();


    //! \brief Set the task status in the UI
    void setTaskStatus(unsigned int i);

    //! \brief get task status edit from the UI
    unsigned int getTaskStatusEdit();


    //! \brief set task priority in the UI
    void setTaskPriority(unsigned int i);

    //! \brief get Task Priority from thu ui
    unsigned int getTaskPriority();

    //! \brief get Task PriorityEdit from thu ui
    unsigned int getTaskPriorityEdit();


    //! \brief set task deadline in the UI
    void setTaskDeadline(const QDateTime& date);

    //! \brief get the task deadline from the UI
    const QDateTime getTaskDeadline();

    //! \brief get the task deadlineEdit from the UI
    const QDateTime getTaskDeadlineEdit();
    //-------

};

#endif // UI_TASK_H
