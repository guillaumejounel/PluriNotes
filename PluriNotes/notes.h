#ifndef PLURINOTES_H
#define PLURINOTES_H

#include <iostream>
#include <vector>
#include <QDateTime>
#include <QString>
#include <QtGui>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <map>

using namespace std;

class NoteEntity;
class NoteArticle;

namespace Ui {
    class PluriNotes;
}


class NoteElement;

class NoteEntity {
private:
    QString id;
    bool archived;
    vector<const NoteElement*> versions;
public:
    NoteEntity(const QString& id);
    ~NoteEntity() { versions.clear(); }
    QString getId() const;
    QString getTitle() const;
    const NoteElement& getLastVersion() const;
    bool isArchived() const;
    void addVersion(const NoteElement&);
};

class NoteElement {
private:
    const QString title;
    QDateTime creationDate;
protected:
    static map<QString, NoteElement*> const& NoteTypeList (QString typeName, NoteElement* ptNote);
public:
    NoteElement() {}
    NoteElement(const QString& title) : title(title) {
        creationDate = QDateTime::currentDateTime();
    }
    static map<QString, NoteElement*> getTypesNotes();
    const QString& getTitle() const { return title; }
    const QDateTime& getCreationDate() const { return creationDate; }
    virtual QList<QWidget*> champsForm() = 0;
    virtual void displayNote() const = 0;
    virtual NoteElement* saveNote(QString title) = 0;
    virtual ~NoteElement() = default;
};

template <class Note>
class BaseNoteType : public NoteElement {
public:
    BaseNoteType() {}
    BaseNoteType(const QString& title) : NoteElement(title) {}

    static int setTypeInList() {
        return NoteTypeList(Note::name(), Note::newType()).size();
    }
    static int id;
};

template <class Note>
int BaseNoteType<Note>::id = setTypeInList();

#define setNoteType(TypeNote) \
class TypeNote : public BaseNoteType<TypeNote> { \
public:\
int idc { id }; \
static TypeNote* newType() { return new TypeNote; } \
static QString name() { return QString::fromUtf8(#TypeNote); }

setNoteType(Article)
private:
    const QString text;
    QTextEdit* testText;
    QLabel* testLabel;
public:
    Article() {}
    Article(const QString& title, const QString& text): BaseNoteType(title), text(text) {}
    const QString& getText() const {return text;}
    virtual void displayNote() const override;
    QList<QWidget*> champsForm() override;
    Article* saveNote(QString title) override;
    ~Article() {}
};

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

#endif // PLURINOTES_H
