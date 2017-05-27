#ifndef NOTE_DOCUMENT_H
#define NOTE_DOCUMENT_H

using namespace std;
#include "notetemplate.h"

#include <QLineEdit>
#include <QLabel>

setNoteType(Document)
private:
    const QString description;
    QLineEdit *fichier, *descr;
    QLabel *lfichier, *ldescr;
public:
    Document() {}
    Document(const QString& title, const QString& description):
    BaseNoteType(title), description(description) {}
    const QString& getDescription() const {return description;}
    virtual void displayNote() const override;
    QList<QWidget*> champsForm() override;
    Document* saveNote(QString title) override;
    ~Document() {}
};

#endif // NOTE_DOCUMENT_H
