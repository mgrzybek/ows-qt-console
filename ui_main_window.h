/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created: Tue May 8 20:15:56 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Main_Window
{
public:
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionManage;
    QWidget *centralWidget;
    QTreeView *treeView;
    QTabWidget *tabWidget;
    QWidget *overview_tab;
    QTableView *jobs_view;
    QWidget *template_tab;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuDomains;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Main_Window)
    {
        if (Main_Window->objectName().isEmpty())
            Main_Window->setObjectName(QString::fromUtf8("Main_Window"));
        Main_Window->resize(1184, 731);
        actionConnect = new QAction(Main_Window);
        actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
        actionDisconnect = new QAction(Main_Window);
        actionDisconnect->setObjectName(QString::fromUtf8("actionDisconnect"));
        actionManage = new QAction(Main_Window);
        actionManage->setObjectName(QString::fromUtf8("actionManage"));
        centralWidget = new QWidget(Main_Window);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        treeView = new QTreeView(centralWidget);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(10, 10, 256, 671));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(280, 10, 881, 661));
        overview_tab = new QWidget();
        overview_tab->setObjectName(QString::fromUtf8("overview_tab"));
        jobs_view = new QTableView(overview_tab);
        jobs_view->setObjectName(QString::fromUtf8("jobs_view"));
        jobs_view->setGeometry(QRect(10, 180, 851, 311));
        tabWidget->addTab(overview_tab, QString());
        template_tab = new QWidget();
        template_tab->setObjectName(QString::fromUtf8("template_tab"));
        tabWidget->addTab(template_tab, QString());
        Main_Window->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Main_Window);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1184, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuDomains = new QMenu(menuBar);
        menuDomains->setObjectName(QString::fromUtf8("menuDomains"));
        Main_Window->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Main_Window);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Main_Window->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Main_Window);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Main_Window->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuDomains->menuAction());
        menuDomains->addAction(actionConnect);
        menuDomains->addAction(actionDisconnect);
        menuDomains->addSeparator();
        menuDomains->addAction(actionManage);

        retranslateUi(Main_Window);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Main_Window);
    } // setupUi

    void retranslateUi(QMainWindow *Main_Window)
    {
        Main_Window->setWindowTitle(QApplication::translate("Main_Window", "Main_Window", 0, QApplication::UnicodeUTF8));
        actionConnect->setText(QApplication::translate("Main_Window", "Connect", 0, QApplication::UnicodeUTF8));
        actionDisconnect->setText(QApplication::translate("Main_Window", "Disconnect", 0, QApplication::UnicodeUTF8));
        actionManage->setText(QApplication::translate("Main_Window", "Manage", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(overview_tab), QApplication::translate("Main_Window", "Overview", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(template_tab), QApplication::translate("Main_Window", "Template", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("Main_Window", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("Main_Window", "Edit", 0, QApplication::UnicodeUTF8));
        menuDomains->setTitle(QApplication::translate("Main_Window", "Domains", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Main_Window: public Ui_Main_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
