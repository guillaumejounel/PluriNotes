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
public:
    Article() {}
    Article(const QString& title, const QDateTime& creaDate, const QString& text): BaseNoteType(title,creaDate), text(text) {}
    const QString& getText() const {return text;}
    virtual void displayNote() const override;
    virtual unsigned int indexPageCreation() const override { return 0; }
    virtual Article* saveNote(QString title) override;
    virtual Article* addVersion() const override;
    virtual bool textChanged() const override;
    virtual void saveToXML(QXmlStreamWriter& stream) const override;
    virtual void loadFromXML(QXmlStreamReader& stream, NoteEntity& newNoteEntity) const override;

    //! method to get the references inside a specific type of note
    virtual QStringList returnReferences() const override;


    ~Article() {}


    //-------
    // Article related Ui element setter.getter
    // \todo move to an other class for better POO ?


    //! \brief set the article Content in the UI
    void setUiArticleContent(const QString& content) const;

    //! \brief get the article articleContent in the UI
    const QString getUiArticleContent() const;

    //! \brief get the article articleDisplayContent in the UI
    const QString getUiArticleContentEdit() const;
    //-------

};

#endif // NOTE_ARTICLE_H
