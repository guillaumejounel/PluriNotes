#ifndef RELATIONSWINDOWS_H
#define RELATIONSWINDOWS_H

#include <QMainWindow>
#include "othertools.h"

namespace Ui {
class relationsWindows;
}

class Relation;

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

    //! Function to populate the comboboxes of NoteEntities in the UI \n
    void addNoteEntityToComboBoxes();

    //! Before closing
    void closeEvent ( QCloseEvent * event );

    //! After showing
    void showEvent ( QShowEvent * event );

signals:
    public slots:
    //! Short function to be called before closing the window
    void beforeClose();
    void toNewRelationForm();
    void displayRelation();
    void addRelation();

};

#endif // RELATIONSWINDOWS_H
