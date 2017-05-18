/********************************************************************************
** Form generated from reading UI file 'plurinotes.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
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
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *pushButton;
    QWidget *formWidget;
    QFormLayout *noteCreation;
    QPlainTextEdit *contentTextEdit;
    QLabel *titleLabel_4;
    QLineEdit *idLineEdit;
    QLabel *idLabel;
    QComboBox *TypeComboBox;
    QLabel *typeLabel;
    QLineEdit *titleLineEdit;
    QLabel *titleLabel;
    QPushButton *cancel;
    QPushButton *save;
    QLabel *typeLabel_3;
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
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(10, 30, 181, 351));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 179, 349));
        scrollArea->setWidget(scrollAreaWidgetContents);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 0, 181, 32));
        formWidget = new QWidget(centralWidget);
        formWidget->setObjectName(QStringLiteral("formWidget"));
        formWidget->setGeometry(QRect(210, 30, 301, 351));
        noteCreation = new QFormLayout(formWidget);
        noteCreation->setSpacing(6);
        noteCreation->setContentsMargins(11, 11, 11, 11);
        noteCreation->setObjectName(QStringLiteral("noteCreation"));
        contentTextEdit = new QPlainTextEdit(formWidget);
        contentTextEdit->setObjectName(QStringLiteral("contentTextEdit"));

        noteCreation->setWidget(7, QFormLayout::FieldRole, contentTextEdit);

        titleLabel_4 = new QLabel(formWidget);
        titleLabel_4->setObjectName(QStringLiteral("titleLabel_4"));

        noteCreation->setWidget(6, QFormLayout::FieldRole, titleLabel_4);

        idLineEdit = new QLineEdit(formWidget);
        idLineEdit->setObjectName(QStringLiteral("idLineEdit"));

        noteCreation->setWidget(5, QFormLayout::FieldRole, idLineEdit);

        idLabel = new QLabel(formWidget);
        idLabel->setObjectName(QStringLiteral("idLabel"));

        noteCreation->setWidget(4, QFormLayout::FieldRole, idLabel);

        TypeComboBox = new QComboBox(formWidget);
        TypeComboBox->setObjectName(QStringLiteral("TypeComboBox"));

        noteCreation->setWidget(3, QFormLayout::FieldRole, TypeComboBox);

        typeLabel = new QLabel(formWidget);
        typeLabel->setObjectName(QStringLiteral("typeLabel"));

        noteCreation->setWidget(2, QFormLayout::FieldRole, typeLabel);

        titleLineEdit = new QLineEdit(formWidget);
        titleLineEdit->setObjectName(QStringLiteral("titleLineEdit"));

        noteCreation->setWidget(1, QFormLayout::FieldRole, titleLineEdit);

        titleLabel = new QLabel(formWidget);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        noteCreation->setWidget(0, QFormLayout::FieldRole, titleLabel);

        cancel = new QPushButton(formWidget);
        cancel->setObjectName(QStringLiteral("cancel"));

        noteCreation->setWidget(8, QFormLayout::FieldRole, cancel);

        save = new QPushButton(formWidget);
        save->setObjectName(QStringLiteral("save"));

        noteCreation->setWidget(9, QFormLayout::FieldRole, save);

        typeLabel_3 = new QLabel(centralWidget);
        typeLabel_3->setObjectName(QStringLiteral("typeLabel_3"));
        typeLabel_3->setGeometry(QRect(620, 560, 27, 20));
        PluriNotes->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PluriNotes);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 799, 22));
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
        QObject::connect(menuBar, SIGNAL(triggered(QAction*)), PluriNotes, SLOT(createNote()));
        QObject::connect(pushButton, SIGNAL(clicked()), PluriNotes, SLOT(createNote()));
        QObject::connect(cancel, SIGNAL(clicked()), formWidget, SLOT(hide()));

        QMetaObject::connectSlotsByName(PluriNotes);
    } // setupUi

    void retranslateUi(QMainWindow *PluriNotes)
    {
        PluriNotes->setWindowTitle(QApplication::translate("PluriNotes", "PluriNotes", Q_NULLPTR));
        actionNouvelle->setText(QApplication::translate("PluriNotes", "Nouvelle", Q_NULLPTR));
        actionHopla->setText(QApplication::translate("PluriNotes", "Hopla", Q_NULLPTR));
        pushButton->setText(QApplication::translate("PluriNotes", "Nouvelle note", Q_NULLPTR));
        titleLabel_4->setText(QApplication::translate("PluriNotes", "contenu", Q_NULLPTR));
        idLabel->setText(QApplication::translate("PluriNotes", "id", Q_NULLPTR));
        TypeComboBox->clear();
        TypeComboBox->insertItems(0, QStringList()
         << QApplication::translate("PluriNotes", "Document", Q_NULLPTR)
         << QApplication::translate("PluriNotes", "Task", Q_NULLPTR)
         << QApplication::translate("PluriNotes", "Article", Q_NULLPTR)
        );
        typeLabel->setText(QApplication::translate("PluriNotes", "type", Q_NULLPTR));
        titleLabel->setText(QApplication::translate("PluriNotes", "title", Q_NULLPTR));
        cancel->setText(QApplication::translate("PluriNotes", "Cancel", Q_NULLPTR));
        save->setText(QApplication::translate("PluriNotes", "Save", Q_NULLPTR));
        typeLabel_3->setText(QString());
        menuPluriNotes->setTitle(QApplication::translate("PluriNotes", "Note", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PluriNotes: public Ui_PluriNotes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLURINOTES_H
