#include "relationswindows.h"
#include "ui_relationswindows.h"
#include "application.h"

relationsWindows::relationsWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::relationsWindows)
{
    ui->setupUi(this);




    exitAction = menuBar()->addAction(QString("Close Window"));
    exitAction->setShortcuts(QKeySequence::Quit);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(beforeClose()));
}

void relationsWindows::beforeClose(){
    // Reactivate the previous window
    PluriNotes& manager = PluriNotes::getManager();
    manager.setEnabled(true);

    //Close the window
    close();
}

relationsWindows::~relationsWindows()
{
    delete ui;
}
