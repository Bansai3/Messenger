#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "sign_in.h"
#include "sign_up.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLabelText(QLabel * label, QString message)
{
    label->setText(message);
}


void MainWindow::on_pushButton_clicked()
{
    hide();
    signInWindow = new sign_in(this);
    signInWindow->setMainWindow(this);
    signInWindow->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    hide();
    signUpWindow = new sign_up(this);
    signUpWindow->setMainWindow(this);
    signUpWindow->show();
}

