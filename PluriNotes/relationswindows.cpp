#include "relationswindows.h"
#include "ui_relationswindows.h"

relationsWindows::relationsWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::relationsWindows)
{
    ui->setupUi(this);
}

relationsWindows::~relationsWindows()
{
    delete ui;
}
