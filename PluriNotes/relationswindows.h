#ifndef RELATIONSWINDOWS_H
#define RELATIONSWINDOWS_H

#include <QMainWindow>
//#include "application.h"
#include "othertools.h"
#include "relation.h"

namespace Ui {
class relationsWindows;
}

class relationsWindows : public QMainWindow
{
    Q_OBJECT

private:

    Ui::relationsWindows *ui;

    ~relationsWindows();

    QAction* exitAction;

    Relation& getCurrentRelation();

public:
    explicit relationsWindows(QWidget *parent = 0);

    //! Function to add an listRelationAndPointer* to the list of notes
    void addItemRelationToList(listRelationAndPointer* item);

    //! Function to add a Relation to the list of Relations in the UI \n
    //! With creation of a listRelationAndPointer*
    listRelationAndPointer* addRelationToList(Relation *rel);

    //! Before closing
    void closeEvent ( QCloseEvent * event );

signals:
    public slots:
    //! Short function to be called before closing the window
    void beforeClose();
    void toNewRelationForm();
    void displayRelation();
    void addRelation();

};

#endif // RELATIONSWINDOWS_H
