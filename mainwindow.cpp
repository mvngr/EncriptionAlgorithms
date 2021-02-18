#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

#include "transpositioncipher.h"
#include "magicsquarecipher.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->algorithm->addItem("Шифр Цезаря", QVariant::fromValue(Algorithms::TranspositionCipherFlag));
    ui->algorithm->addItem("Магический квадрат", QVariant::fromValue(Algorithms::MagicsquareCipherFlag));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_base_message_textEdited(const QString &arg1)
{
    MagicSquareCipher c({
                            {8, 1, 6},
                            {3, 5, 7},
                            {4, 9, 2}
                        });
    ui->encrypt_message->setText(c.encrypt(arg1));
    ui->error->setText(c.errorString());
}
