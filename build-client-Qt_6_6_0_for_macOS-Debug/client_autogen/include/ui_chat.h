/********************************************************************************
** Form generated from reading UI file 'chat.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAT_H
#define UI_CHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chat
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lnIPAddress;
    QLabel *label_2;
    QSpinBox *spnPort;
    QPushButton *btnConnect;
    QGroupBox *grpSendData;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    QLineEdit *lnMessage;
    QPushButton *btnSend;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QListWidget *lstConsole;
    QPushButton *btnClear;

    void setupUi(QDialog *chat)
    {
        if (chat->objectName().isEmpty())
            chat->setObjectName("chat");
        chat->resize(589, 388);
        chat->setStyleSheet(QString::fromUtf8("#lnIPAddress[state = \"0\"]{\n"
"\n"
"        background-color: rgb(234, 0, 0);\n"
"}\n"
"\n"
"#lnIPAddress[state = \"1\"]{\n"
"\n"
"        background-color: rgb(67, 135, 100);\n"
"}\n"
""));
        chat->setModal(true);
        centralwidget = new QWidget(chat);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setGeometry(QRect(30, 40, 529, 290));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName("formLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lnIPAddress = new QLineEdit(groupBox);
        lnIPAddress->setObjectName("lnIPAddress");
        lnIPAddress->setClearButtonEnabled(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, lnIPAddress);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        spnPort = new QSpinBox(groupBox);
        spnPort->setObjectName("spnPort");
        spnPort->setMinimum(0);
        spnPort->setMaximum(65535);

        formLayout->setWidget(1, QFormLayout::FieldRole, spnPort);

        btnConnect = new QPushButton(groupBox);
        btnConnect->setObjectName("btnConnect");

        formLayout->setWidget(2, QFormLayout::FieldRole, btnConnect);


        verticalLayout_2->addWidget(groupBox);

        grpSendData = new QGroupBox(centralwidget);
        grpSendData->setObjectName("grpSendData");
        grpSendData->setEnabled(false);
        formLayout_2 = new QFormLayout(grpSendData);
        formLayout_2->setObjectName("formLayout_2");
        label_3 = new QLabel(grpSendData);
        label_3->setObjectName("label_3");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        lnMessage = new QLineEdit(grpSendData);
        lnMessage->setObjectName("lnMessage");
        lnMessage->setClearButtonEnabled(true);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lnMessage);

        btnSend = new QPushButton(grpSendData);
        btnSend->setObjectName("btnSend");

        formLayout_2->setWidget(1, QFormLayout::FieldRole, btnSend);


        verticalLayout_2->addWidget(grpSendData);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        lstConsole = new QListWidget(centralwidget);
        lstConsole->setObjectName("lstConsole");

        verticalLayout->addWidget(lstConsole);

        btnClear = new QPushButton(centralwidget);
        btnClear->setObjectName("btnClear");

        verticalLayout->addWidget(btnClear);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(chat);
        QObject::connect(btnClear, &QPushButton::clicked, lstConsole, qOverload<>(&QListWidget::clear));

        QMetaObject::connectSlotsByName(chat);
    } // setupUi

    void retranslateUi(QDialog *chat)
    {
        chat->setWindowTitle(QCoreApplication::translate("chat", "Client", nullptr));
        groupBox->setTitle(QCoreApplication::translate("chat", "Connection information", nullptr));
        label->setText(QCoreApplication::translate("chat", "IP Address:", nullptr));
        lnIPAddress->setInputMask(QCoreApplication::translate("chat", "000.000.000.000;_", nullptr));
        lnIPAddress->setText(QCoreApplication::translate("chat", "127.0.0.1", nullptr));
        lnIPAddress->setProperty("state", QVariant(QString()));
        label_2->setText(QCoreApplication::translate("chat", "Port:", nullptr));
        btnConnect->setText(QCoreApplication::translate("chat", "Connect", nullptr));
        grpSendData->setTitle(QCoreApplication::translate("chat", "Send Data", nullptr));
        label_3->setText(QCoreApplication::translate("chat", "Message:", nullptr));
        lnMessage->setText(QString());
        lnMessage->setProperty("state", QVariant(QString()));
        btnSend->setText(QCoreApplication::translate("chat", "Send", nullptr));
        btnClear->setText(QCoreApplication::translate("chat", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chat: public Ui_chat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_H
