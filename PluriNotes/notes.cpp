#include "notes.h"

NoteForm::NoteForm(QWidget *parent)
{
    QGroupBox *noteGroup = new QGroupBox(tr("Note creation"));
    QComboBox *typeComboBox = new QComboBox();
    typeComboBox->addItem(tr("Article"));
    typeComboBox->addItem(tr("Document"));
    typeComboBox->addItem(tr("Tache"));

    title = new QLineEdit;
    title->setFocus();

    QGridLayout *noteLayout = new QGridLayout;
    noteLayout->addWidget(typeComboBox, 0, 1);
    noteLayout->addWidget(title, 1, 0, 1, 2);
    noteGroup->setLayout(noteLayout);

    label = new QLabel();

    QVBoxLayout *layoutPrincipal = new QVBoxLayout();
    layoutPrincipal->addWidget(label);
    layoutPrincipal->addWidget(noteGroup);

    QHBoxLayout *layoutBt = new QHBoxLayout;
    layoutBt->addStretch();

    layoutPrincipal->addLayout(layoutBt);

    setLayout(layoutPrincipal);
}
