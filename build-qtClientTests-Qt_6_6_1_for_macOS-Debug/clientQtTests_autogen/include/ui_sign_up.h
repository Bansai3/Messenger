/********************************************************************************
** Form generated from reading UI file 'sign_up.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGN_UP_H
#define UI_SIGN_UP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sign_up
{
public:
    QGroupBox *groupBox;
    QPushButton *signUp;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *name;
    QLineEdit *nameText;
    QHBoxLayout *horizontalLayout_2;
    QLabel *surname;
    QLineEdit *surnameText;
    QHBoxLayout *horizontalLayout_3;
    QLabel *login;
    QLineEdit *loginText;
    QHBoxLayout *horizontalLayout_4;
    QLabel *password;
    QLineEdit *passwordText;
    QPushButton *back;

    void setupUi(QDialog *sign_up)
    {
        if (sign_up->objectName().isEmpty())
            sign_up->setObjectName("sign_up");
        sign_up->resize(400, 300);
        groupBox = new QGroupBox(sign_up);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(30, 10, 331, 261));
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(18);
        groupBox->setFont(font);
        groupBox->setAlignment(Qt::AlignCenter);
        signUp = new QPushButton(groupBox);
        signUp->setObjectName("signUp");
        signUp->setGeometry(QRect(190, 200, 100, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Times New Roman")});
        font1.setPointSize(16);
        signUp->setFont(font1);
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(30, 40, 271, 131));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        name = new QLabel(layoutWidget);
        name->setObjectName("name");
        name->setFont(font1);

        horizontalLayout->addWidget(name);

        nameText = new QLineEdit(layoutWidget);
        nameText->setObjectName("nameText");

        horizontalLayout->addWidget(nameText);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        surname = new QLabel(layoutWidget);
        surname->setObjectName("surname");
        surname->setFont(font1);

        horizontalLayout_2->addWidget(surname);

        surnameText = new QLineEdit(layoutWidget);
        surnameText->setObjectName("surnameText");

        horizontalLayout_2->addWidget(surnameText);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        login = new QLabel(layoutWidget);
        login->setObjectName("login");
        login->setFont(font1);

        horizontalLayout_3->addWidget(login);

        loginText = new QLineEdit(layoutWidget);
        loginText->setObjectName("loginText");

        horizontalLayout_3->addWidget(loginText);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        password = new QLabel(layoutWidget);
        password->setObjectName("password");
        password->setFont(font1);

        horizontalLayout_4->addWidget(password);

        passwordText = new QLineEdit(layoutWidget);
        passwordText->setObjectName("passwordText");

        horizontalLayout_4->addWidget(passwordText);


        verticalLayout->addLayout(horizontalLayout_4);

        back = new QPushButton(groupBox);
        back->setObjectName("back");
        back->setGeometry(QRect(40, 200, 100, 31));

        retranslateUi(sign_up);

        QMetaObject::connectSlotsByName(sign_up);
    } // setupUi

    void retranslateUi(QDialog *sign_up)
    {
        sign_up->setWindowTitle(QCoreApplication::translate("sign_up", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("sign_up", "Sign up", nullptr));
        signUp->setText(QCoreApplication::translate("sign_up", "sign up", nullptr));
        name->setText(QCoreApplication::translate("sign_up", "Name", nullptr));
        nameText->setText(QCoreApplication::translate("sign_up", "Vladislav", nullptr));
        surname->setText(QCoreApplication::translate("sign_up", "Surname", nullptr));
        surnameText->setText(QCoreApplication::translate("sign_up", "Pushkin", nullptr));
        login->setText(QCoreApplication::translate("sign_up", "Login", nullptr));
        loginText->setText(QCoreApplication::translate("sign_up", "123hellothere", nullptr));
        password->setText(QCoreApplication::translate("sign_up", "Password", nullptr));
        passwordText->setText(QCoreApplication::translate("sign_up", "2228redblue", nullptr));
        back->setText(QCoreApplication::translate("sign_up", "back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sign_up: public Ui_sign_up {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGN_UP_H
