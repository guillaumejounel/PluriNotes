#ifndef NOTE_ARTICLE_H
#define NOTE_ARTICLE_H


#include "notetemplate.h"

#include <QString>
#include <QTextEdit>
#include <QLabel>
#include <QWidget>
#include <QDateTime>

using namespace std;


setNoteType(Article)
private:
    const QString text;
    QTextEdit* testText;
    QLabel* testLabel;
public:
    Article() {}
    Article(const QString& title, const QDateTime& creaDate, const QString& text): BaseNoteType(title,creaDate), text(text) {}
    const QString& getText() const {return text;}
    virtual void displayNote() const override;
    QList<QWidget*> champsForm() override;
    Article* saveNote(QString title) override;
    ~Article() {}
};



#endif // NOTE_ARTICLE_H