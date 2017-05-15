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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
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
    QMenuBar *menuBar;
    QMenu *menuPluriNotes;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PluriNotes)
    {
        if (PluriNotes->objectName().isEmpty())
            PluriNotes->setObjectName(QStringLiteral("PluriNotes"));
        PluriNotes->resize(786, 467);
        actionNouvelle = new QAction(PluriNotes);
        actionNouvelle->setObjectName(QStringLiteral("actionNouvelle"));
        actionHopla = new QAction(PluriNotes);
        actionHopla->setObjectName(QStringLiteral("actionHopla"));
        centralWidget = new QWidget(PluriNotes);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        PluriNotes->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PluriNotes);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 786, 22));
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

        QMetaObject::connectSlotsByName(PluriNotes);
    } // setupUi

    void retranslateUi(QMainWindow *PluriNotes)
    {
        PluriNotes->setWindowTitle(QApplication::translate("PluriNotes", "PluriNotes", Q_NULLPTR));
        actionNouvelle->setText(QApplication::translate("PluriNotes", "Nouvelle", Q_NULLPTR));
        actionHopla->setText(QApplication::translate("PluriNotes", "Hopla", Q_NULLPTR));
        menuPluriNotes->setTitle(QApplication::translate("PluriNotes", "Note", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PluriNotes: public Ui_PluriNotes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLURINOTES_H
