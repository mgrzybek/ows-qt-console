/********************************************************************************
** Form generated from reading UI file 'connect.ui'
**
** Created: Tue May 8 20:15:56 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECT_H
#define UI_CONNECT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>

QT_BEGIN_NAMESPACE

class Ui_Connect
{
public:
    QGridLayout *gridLayout;
    QListView *Servers_List;
    QDialogButtonBox *Control_Buttons;

    void setupUi(QDialog *Connect)
    {
        if (Connect->objectName().isEmpty())
            Connect->setObjectName(QString::fromUtf8("Connect"));
        Connect->resize(351, 290);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Connect->sizePolicy().hasHeightForWidth());
        Connect->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(Connect);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Servers_List = new QListView(Connect);
        Servers_List->setObjectName(QString::fromUtf8("Servers_List"));

        gridLayout->addWidget(Servers_List, 0, 0, 1, 1);

        Control_Buttons = new QDialogButtonBox(Connect);
        Control_Buttons->setObjectName(QString::fromUtf8("Control_Buttons"));
        Control_Buttons->setOrientation(Qt::Horizontal);
        Control_Buttons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        Control_Buttons->setCenterButtons(false);

        gridLayout->addWidget(Control_Buttons, 1, 0, 1, 1);


        retranslateUi(Connect);
        QObject::connect(Control_Buttons, SIGNAL(accepted()), Connect, SLOT(accept()));
        QObject::connect(Control_Buttons, SIGNAL(rejected()), Connect, SLOT(reject()));

        QMetaObject::connectSlotsByName(Connect);
    } // setupUi

    void retranslateUi(QDialog *Connect)
    {
        Connect->setWindowTitle(QApplication::translate("Connect", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Connect: public Ui_Connect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECT_H
