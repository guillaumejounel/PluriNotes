#ifndef NOTE_TASK_H
#define NOTE_TASK_H

#include "notetemplate.h"

#include <QTextEdit>
#include <QLabel>
#include <QDateTime>
#include <QComboBox>

using namespace std;

setNoteType(Tache)
private:
    enum Priority {low, normal, high};
    enum Status {awaiting, pending, finished};
    const QString action;
    Status taskStatus;
    Priority taskPrio;
    QLabel *laction, *lprio, *lstatus;
    QTextEdit* actionFormZone;
    QComboBox *taskPrioForm, *taskStatusForm;
public:
    Tache() {}
    Tache(const QString& title, const QDateTime& creaDate, const QString& action, const Status& taskStatus, const Priority& taskPrio): BaseNoteType(title,creaDate), action(action), taskStatus(taskStatus), taskPrio(taskPrio) {}
    const QString& getAction() const {return action;}
    virtual void displayNote() const override;
    virtual QList<QWidget*> champsForm() override;
    virtual Tache* saveNote(QString title) override;
    ~Tache() {}
};

#endif // NOTE_TASK_H
