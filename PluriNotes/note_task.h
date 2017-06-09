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
    ~Task() {}
};

#endif // NOTE_TASK_H
