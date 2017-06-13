#ifndef NOTE_TASK_H
#define NOTE_TASK_H

#include "notetemplate.h"

using namespace std;

/**
\class Task
\brief Class of the Task note type
**/

setNoteType(Task)
private:
    //! \brief Action of the Task
    const QString action;

    //! \brief Status of the Task, (0: in progress, 1: pending, 2: done)
    unsigned int status;

    //! \brief Priority of the Task (0: no priority, 1: low, 2: normal, 3: high)
    unsigned int priority;

    //! \brief Deadline of the Task
    const QDateTime deadline;

public:
    //! \brief Constructor of Task without argument
    Task() {}

    //! \brief Constructor of Task
    Task(const QString& title, const QDateTime& creaDate, const QString& action, const unsigned int taskStatus, const unsigned int taskPriority, const QDateTime& deadline): BaseNoteType(title,creaDate), action(action), status(taskStatus), priority(taskPriority), deadline(deadline) {}

    //! \brief Display Task on the PluriNotes UI
    virtual void displayNote() const override;

    //! \brief Return index of the note creation form page related to Task
    virtual unsigned int indexPageCreation() const override { return 1; }

    //! \brief Return a new Task initialized by the note creation form UI inputs
    virtual Task* saveNote(QString title) override;

    //! \brief Return a new Task initialized by the note edition form UI inputs
    virtual Task* addVersion() const override;

    //! \brief Return true if the note edition form has UI inputs different from the Task
    virtual bool textChanged() const override;

    //! \brief Save the Task data in a file
    virtual void saveToXML(QXmlStreamWriter& stream) const override;

    //! \brief Load a Task from a file and add it into a NoteEntity
    virtual void loadFromXML(QXmlStreamReader& stream, NoteEntity& newNoteEntity) const override;

    //! \brief Return detected references from the Task data
    virtual QStringList returnReferences() const override;

    //! \brief Accessor to the action
    QString getAction() const { return action; }

    //! \brief Destructor of Task
    ~Task() {}

    // UI
    //-------

    //! \brief Set the the UI action field content in Task edition form
    void setUiTaskAction(const QString& action) const;

    //! \brief Get the the UI action field content in Task creation form
    const QString getUiTaskAction() const;

    //! \brief Get the the UI action field content in Task edition form
    const QString getUiTaskActionEdit() const;

    //! \brief Set the the UI status field content in Task edition form
    void setUiTaskStatus(unsigned int i) const;

    ///! \brief Get the the UI status field content in Task edition form
    unsigned int getUiTaskStatusEdit() const;

    //! \brief Set the the UI priority field content in Task edition form
    void setUiTaskPriority(unsigned int i) const;

    //! \brief Get the the UI priority field content in Task creation form
    unsigned int getUiTaskPriority() const;

    //! \brief Get the the UI priority field content in Task edition form
    unsigned int getUiTaskPriorityEdit() const;

    //! \brief set task deadline in the UI
    void setUiTaskDeadline(const QDateTime& date) const;

    //! \brief get the task deadline from the UI
    const QDateTime getUiTaskDeadline() const;

    //! \brief get the task deadlineEdit from the UI
    const QDateTime getUiTaskDeadlineEdit() const;

    //-------

};

#endif // NOTE_TASK_H
