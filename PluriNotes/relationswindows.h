#ifndef RELATIONSWINDOWS_H
#define RELATIONSWINDOWS_H

#include <QMainWindow>

namespace Ui {
class relationsWindows;
}

class relationsWindows : public QMainWindow
{
    Q_OBJECT

public:
    explicit relationsWindows(QWidget *parent = 0);
    ~relationsWindows();

private:
    Ui::relationsWindows *ui;
};

#endif // RELATIONSWINDOWS_H
