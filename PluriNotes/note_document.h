#ifndef NOTE_DOCUMENT_H
#define NOTE_DOCUMENT_H

using namespace std;
#include "notetemplate.h"

#include <QLineEdit>
#include <QLabel>
#include <QDateTime>

setNoteType(Document)
private:
    const QString description;
    QLineEdit *fichier, *descr;
    QLabel *lfichier, *ldescr;
public:
    Document() {}
    Document(const QString& title, const QDateTime& creaDate, const QString& description):
    BaseNoteType(title,creaDate), description(description) {}
    const QString& getDescription() const {return description;}
    virtual void displayNote() const override;
    QList<QWidget*> champsForm() override;
    Document* saveNote(QString title) override;
    ~Document() {}
};

#endif // NOTE_DOCUMENT_H
