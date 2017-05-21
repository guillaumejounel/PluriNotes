#ifndef PLURINOTES_H
#define PLURINOTES_H

#include <iostream>
#include <vector>
#include <QDate>
#include <QString>
#include <QtGui>
#include <QLabel>
#include <QLineEdit>

using namespace std;

class NoteEntity;
class NoteArticle;

namespace Ui {
    class PluriNotes;
}


class NoteElement;

class NoteForm : public QWidget
{
    Q_OBJECT

public:
    NoteForm(QWidget *parent=0);

public slots:
    void titleChanged(int) {}
    void idChanged(int) {}
    void typeChanged(int) {}

private:
    QLabel *label;
    QLineEdit *title;
    QLineEdit *id;
    QLineEdit *type;
};

class NoteEntity {
private:
    QString id;
    QDate creationDate;
    QDate modificationDate;
    bool archived;
    bool bin;
    vector<const NoteElement*> versions;
public:
    NoteEntity(const QString& id);
    ~NoteEntity() {versions.clear();}
    QString getId() const;
    QString getTitle() const;
    const NoteElement& getLastVersion() const;
    QDate getCreationDate() const;
    QDate getModificationDate() const;
    bool isArchived() const;
    void addVersion(const NoteElement&);
};

class NoteElement {
    const QString title;
public:
    NoteElement(const QString& title) : title(title) {}
    //virtual ~NoteElement() {}
    const QString& getTitle() const { return title; }
    virtual void test() const = 0;
    // Need to implement a function to open the specific edition window
    // what about virtual pure

};


class NoteArticle : public NoteElement {
private:
    const QString text;

public:
    NoteArticle(const QString& title, const QString& text):
        NoteElement(title), text(text) {}
    const QString& getText() const {return text;}
    void test() const {}
    ~NoteArticle();
};

#endif // PLURINOTES_H
