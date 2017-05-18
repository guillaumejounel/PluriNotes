/********************************************************************************
** Form generated from reading UI file 'plurinotes.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLURINOTES_H
#define UI_PLURINOTES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PluriNotes
{
public:
    QAction *actionNouvelle;
    QAction *actionHopla;
    QWidget *centralWidget;
    QPushButton *newNote;
    QWidget *formNoteWidget;
    QFormLayout *noteCreation;
    QPlainTextEdit *contentTextEdit;
    QLabel *titleLabel_4;
    QLineEdit *titleLineEdit;
    QLabel *titleLabel;
    QPushButton *cancel;
    QPushButton *save;
    QLineEdit *idLineEdit;
    QComboBox *TypeComboBox;
    QLabel *idLabel;
    QLabel *typeLabel;
    QLabel *typeLabel_3;
    QListWidget *listWidget;
    QMenuBar *menuBar;
    QMenu *menuPluriNotes;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PluriNotes)
    {
        if (PluriNotes->objectName().isEmpty())
            PluriNotes->setObjectName(QStringLiteral("PluriNotes"));
        PluriNotes->resize(799, 448);
        actionNouvelle = new QAction(PluriNotes);
        actionNouvelle->setObjectName(QStringLiteral("actionNouvelle"));
        actionHopla = new QAction(PluriNotes);
        actionHopla->setObjectName(QStringLiteral("actionHopla"));
        centralWidget = new QWidget(PluriNotes);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        newNote = new QPushButton(centralWidget);
        newNote->setObjectName(QStringLiteral("newNote"));
        newNote->setGeometry(QRect(10, 0, 181, 32));
        formNoteWidget = new QWidget(centralWidget);
        formNoteWidget->setObjectName(QStringLiteral("formNoteWidget"));
        formNoteWidget->setGeometry(QRect(210, 30, 301, 351));
        noteCreation = new QFormLayout(formNoteWidget);
        noteCreation->setSpacing(6);
        noteCreation->setContentsMargins(11, 11, 11, 11);
        noteCreation->setObjectName(QStringLiteral("noteCreation"));
        contentTextEdit = new QPlainTextEdit(formNoteWidget);
        contentTextEdit->setObjectName(QStringLiteral("contentTextEdit"));

        noteCreation->setWidget(8, QFormLayout::FieldRole, contentTextEdit);

        titleLabel_4 = new QLabel(formNoteWidget);
        titleLabel_4->setObjectName(QStringLiteral("titleLabel_4"));

        noteCreation->setWidget(7, QFormLayout::FieldRole, titleLabel_4);

        titleLineEdit = new QLineEdit(formNoteWidget);
        titleLineEdit->setObjectName(QStringLiteral("titleLineEdit"));

        noteCreation->setWidget(1, QFormLayout::FieldRole, titleLineEdit);

        titleLabel = new QLabel(formNoteWidget);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        noteCreation->setWidget(0, QFormLayout::FieldRole, titleLabel);

        cancel = new QPushButton(formNoteWidget);
        cancel->setObjectName(QStringLiteral("cancel"));

        noteCreation->setWidget(9, QFormLayout::FieldRole, cancel);

        save = new QPushButton(formNoteWidget);
        save->setObjectName(QStringLiteral("save"));

        noteCreation->setWidget(10, QFormLayout::FieldRole, save);

        idLineEdit = new QLineEdit(formNoteWidget);
        idLineEdit->setObjectName(QStringLiteral("idLineEdit"));

        noteCreation->setWidget(3, QFormLayout::FieldRole, idLineEdit);

        TypeComboBox = new QComboBox(formNoteWidget);
        TypeComboBox->setObjectName(QStringLiteral("TypeComboBox"));

        noteCreation->setWidget(5, QFormLayout::FieldRole, TypeComboBox);

        idLabel = new QLabel(formNoteWidget);
        idLabel->setObjectName(QStringLiteral("idLabel"));

        noteCreation->setWidget(2, QFormLayout::FieldRole, idLabel);

        typeLabel = new QLabel(formNoteWidget);
        typeLabel->setObjectName(QStringLiteral("typeLabel"));

        noteCreation->setWidget(4, QFormLayout::FieldRole, typeLabel);

        typeLabel_3 = new QLabel(centralWidget);
        typeLabel_3->setObjectName(QStringLiteral("typeLabel_3"));
        typeLabel_3->setGeometry(QRect(620, 560, 27, 20));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 40, 181, 341));
        PluriNotes->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PluriNotes);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 799, 28));
        menuPluriNotes = new QMenu(menuBar);
        menuPluriNotes->setObjectName(QStringLiteral("menuPluriNotes"));
        PluriNotes->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PluriNotes);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PluriNotes->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PluriNotes);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PluriNotes->setStatusBar(statusBar);

        menuBar->addAction(menuPluriNotes->menuAction());
        menuPluriNotes->addAction(actionNouvelle);
        menuPluriNotes->addAction(actionHopla);

        retranslateUi(PluriNotes);
        QObject::connect(menuBar, SIGNAL(triggered(QAction*)), PluriNotes, SLOT(formNote()));
        QObject::connect(newNote, SIGNAL(clicked()), PluriNotes, SLOT(formNote()));
        QObject::connect(save, SIGNAL(clicked()), PluriNotes, SLOT(saveNote()));
        QObject::connect(titleLineEdit, SIGNAL(textChanged(QString)), PluriNotes, SLOT(titleChanged()));
        QObject::connect(idLineEdit, SIGNAL(textEdited(QString)), PluriNotes, SLOT(idChanged()));
        QObject::connect(TypeComboBox, SIGNAL(currentTextChanged(QString)), PluriNotes, SLOT(typeChanged()));
        QObject::connect(cancel, SIGNAL(clicked()), PluriNotes, SLOT(cancelNote()));

        QMetaObject::connectSlotsByName(PluriNotes);
    } // setupUi

    void retranslateUi(QMainWindow *PluriNotes)
    {
        PluriNotes->setWindowTitle(QApplication::translate("PluriNotes", "PluriNotes", Q_NULLPTR));
        actionNouvelle->setText(QApplication::translate("PluriNotes", "Nouvelle", Q_NULLPTR));
        actionHopla->setText(QApplication::translate("PluriNotes", "Hopla", Q_NULLPTR));
        newNote->setText(QApplication::translate("PluriNotes", "New note", Q_NULLPTR));
        titleLabel_4->setText(QApplication::translate("PluriNotes", "contenu", Q_NULLPTR));
        titleLabel->setText(QApplication::translate("PluriNotes", "title", Q_NULLPTR));
        cancel->setText(QApplication::translate("PluriNotes", "Cancel", Q_NULLPTR));
        save->setText(QApplication::translate("PluriNotes", "Save", Q_NULLPTR));
        TypeComboBox->clear();
        TypeComboBox->insertItems(0, QStringList()
         << QApplication::translate("PluriNotes", "Document", Q_NULLPTR)
         << QApplication::translate("PluriNotes", "Task", Q_NULLPTR)
         << QApplication::translate("PluriNotes", "Article", Q_NULLPTR)
        );
        idLabel->setText(QApplication::translate("PluriNotes", "id", Q_NULLPTR));
        typeLabel->setText(QApplication::translate("PluriNotes", "type", Q_NULLPTR));
        typeLabel_3->setText(QString());
        menuPluriNotes->setTitle(QApplication::translate("PluriNotes", "Note", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PluriNotes: public Ui_PluriNotes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLURINOTES_H
