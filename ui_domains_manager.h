/********************************************************************************
** Form generated from reading UI file 'domains_manager.ui'
**
** Created: Tue May 8 21:10:01 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOMAINS_MANAGER_H
#define UI_DOMAINS_MANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_Domains_Manager
{
public:
    QGridLayout *gridLayout;
    QPushButton *Delete_Server_Button;
    QDialogButtonBox *Control_Buttons;
    QPushButton *New_Server_Button;
    QTableView *Saved_Servers_List;

    void setupUi(QDialog *Domains_Manager)
    {
        if (Domains_Manager->objectName().isEmpty())
            Domains_Manager->setObjectName(QString::fromUtf8("Domains_Manager"));
        Domains_Manager->setWindowModality(Qt::ApplicationModal);
        Domains_Manager->resize(865, 351);
        gridLayout = new QGridLayout(Domains_Manager);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Delete_Server_Button = new QPushButton(Domains_Manager);
        Delete_Server_Button->setObjectName(QString::fromUtf8("Delete_Server_Button"));

        gridLayout->addWidget(Delete_Server_Button, 1, 1, 1, 1);

        Control_Buttons = new QDialogButtonBox(Domains_Manager);
        Control_Buttons->setObjectName(QString::fromUtf8("Control_Buttons"));
        Control_Buttons->setOrientation(Qt::Horizontal);
        Control_Buttons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(Control_Buttons, 1, 3, 1, 1);

        New_Server_Button = new QPushButton(Domains_Manager);
        New_Server_Button->setObjectName(QString::fromUtf8("New_Server_Button"));

        gridLayout->addWidget(New_Server_Button, 1, 2, 1, 1);

        Saved_Servers_List = new QTableView(Domains_Manager);
        Saved_Servers_List->setObjectName(QString::fromUtf8("Saved_Servers_List"));

        gridLayout->addWidget(Saved_Servers_List, 0, 0, 1, 4);


        retranslateUi(Domains_Manager);
        QObject::connect(Control_Buttons, SIGNAL(accepted()), Domains_Manager, SLOT(accept()));
        QObject::connect(Control_Buttons, SIGNAL(rejected()), Domains_Manager, SLOT(reject()));

        QMetaObject::connectSlotsByName(Domains_Manager);
    } // setupUi

    void retranslateUi(QDialog *Domains_Manager)
    {
        Domains_Manager->setWindowTitle(QApplication::translate("Domains_Manager", "Dialog", 0, QApplication::UnicodeUTF8));
        Delete_Server_Button->setText(QApplication::translate("Domains_Manager", "Delete Server", 0, QApplication::UnicodeUTF8));
        New_Server_Button->setText(QApplication::translate("Domains_Manager", "New Server", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Domains_Manager: public Ui_Domains_Manager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOMAINS_MANAGER_H
