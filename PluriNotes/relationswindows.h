#ifndef RELATIONSWINDOWS_H
#define RELATIONSWINDOWS_H

#include <QMainWindow>
#include "application.h"

namespace Ui {
class relationsWindows;
}

class relationsWindows : public QMainWindow
{
    Q_OBJECT

private:

    Ui::relationsWindows *ui;

    ~relationsWindows();

public:
    explicit relationsWindows(QWidget *parent = 0);



};

#endif // RELATIONSWINDOWS_H
