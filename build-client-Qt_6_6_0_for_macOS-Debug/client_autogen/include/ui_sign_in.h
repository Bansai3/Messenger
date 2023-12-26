/********************************************************************************
** Form generated from reading UI file 'sign_in.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGN_IN_H
#define UI_SIGN_IN_H

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

class Ui_sign_in
{
public:
    QGroupBox *groupBox;
    QPushButton *signIn;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *logIn;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *password;
    QPushButton *back;

    void setupUi(QDialog *sign_in)
    {
        if (sign_in->objectName().isEmpty())
            sign_in->setObjectName("sign_in");
        sign_in->resize(400, 300);
        groupBox = new QGroupBox(sign_in);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(50, 20, 301, 231));
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(18);
        groupBox->setFont(font);
        groupBox->setAlignment(Qt::AlignCenter);
        signIn = new QPushButton(groupBox);
        signIn->setObjectName("signIn");
        signIn->setGeometry(QRect(160, 180, 100, 31));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(30, 50, 233, 81));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Times New Roman")});
        font1.setPointSize(16);
        label->setFont(font1);

        horizontalLayout->addWidget(label);

        logIn = new QLineEdit(layoutWidget);
        logIn->setObjectName("logIn");

        horizontalLayout->addWidget(logIn);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        label_2->setFont(font1);

        horizontalLayout_2->addWidget(label_2);

        password = new QLineEdit(layoutWidget);
        password->setObjectName("password");

        horizontalLayout_2->addWidget(password);


        verticalLayout->addLayout(horizontalLayout_2);

        back = new QPushButton(groupBox);
        back->setObjectName("back");
        back->setGeometry(QRect(30, 181, 100, 31));

        retranslateUi(sign_in);

        QMetaObject::connectSlotsByName(sign_in);
    } // setupUi

    void retranslateUi(QDialog *sign_in)
    {
        sign_in->setWindowTitle(QCoreApplication::translate("sign_in", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("sign_in", "Sign in", nullptr));
        signIn->setText(QCoreApplication::translate("sign_in", "sign in", nullptr));
        label->setText(QCoreApplication::translate("sign_in", "Login", nullptr));
        logIn->setText(QCoreApplication::translate("sign_in", "123hellothere", nullptr));
        label_2->setText(QCoreApplication::translate("sign_in", "Password", nullptr));
        password->setText(QCoreApplication::translate("sign_in", "2228redblue", nullptr));
        back->setText(QCoreApplication::translate("sign_in", "back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sign_in: public Ui_sign_in {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGN_IN_H
