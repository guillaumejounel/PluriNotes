#ifndef NOTE_TASK_H
#define NOTE_TASK_H

#include "notetemplate.h"

#include <QTextEdit>
#include <QLabel>
#include <QDateTime>
#include <QComboBox>

using namespace std;

setNoteType(Task)
private:
    const QString action;
    unsigned int status;
    unsigned int priority;
    const QDateTime deadline;
public:
    Task() {}
    Task(const QString& title, const QDateTime& creaDate, const QString& action, const unsigned int taskStatus, const unsigned int taskPriority, const QDateTime& deadline): BaseNoteType(title,creaDate), action(action), status(taskStatus), priority(taskPriority), deadline(deadline) {}
    virtual void displayNote() const override;
    virtual unsigned int indexPageCreation() const override { return 1; }
    virtual Task* saveNote(QString title) override;
    virtual Task* addVersion() const override;
    virtual bool textChanged() const override;
    virtual void saveToXML(QXmlStreamWriter& stream) const override;
    virtual void loadFromXML(QXmlStreamReader& stream, NoteEntity& newNoteEntity) const override;
    ~Task() {}

    virtual QStringList returnReferences() const override;

    QString getAction() const {return action;}

    // UI
    //-------
    // Task related
    //\todo move to an other class for better POO ?


    //! \todo add documentation
    void setUiTaskAction(const QString& action) const;

    //! \todo add documentation
    const QString getUiTaskAction() const;

    //! \todo add documentation
    const QString getUiTaskActionEdit() const;


    //! \brief Set the task status in the UI
    void setUiTaskStatus(unsigned int i) const;


    //! \brief get task status edit from the UI
    unsigned int getUiTaskStatusEdit() const;


    //! \brief set task priority in the UI
    void setUiTaskPriority(unsigned int i) const;

    //! \brief get Task Priority from thu ui
    unsigned int getUiTaskPriority() const;

    //! \brief get Task PriorityEdit from thu ui
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
