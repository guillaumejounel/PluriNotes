#ifndef PLURINOTES_H
#define PLURINOTES_H

#include <QMainWindow>

namespace Ui {
    class PluriNotes;
}

class PluriNotes : public QMainWindow {
    Q_OBJECT

public:
    explicit PluriNotes(QWidget *parent = 0);
    ~PluriNotes();

private:
    Ui::PluriNotes *ui;
};

#endif // PLURINOTES_H
