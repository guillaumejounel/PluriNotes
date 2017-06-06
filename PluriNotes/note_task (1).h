#ifndef NOTE_TASK_H
#define NOTE_TASK_H

using namespace std;
#include "notetemplate.h"

#include <QLineEdit>
#include <QLabel>
#include <QDateTime>

setNoteType(Tache)
private:
    const QString action;
    QLabel* laction;
public:
    Tache() {}
    Tache(const QString& title, const QDateTime& creaDate, const QString& action): BaseNoteType(title,creaDate), action(action) {}
    const QString& getAction() const {return action;}
    virtual void displayNote() const override;
    virtual QList<QWidget*> champsForm() override;
    virtual Tache* saveNote(QString title) override;
    ~Tache() {}
};

#endif // NOTE_TASK_H
