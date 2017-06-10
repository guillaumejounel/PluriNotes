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

    QAction* exitAction;

public:
    explicit relationsWindows(QWidget *parent = 0);


signals:
    public slots:
    //! Short function to be called before closing the window
    void beforeClose();

};

#endif // RELATIONSWINDOWS_H
