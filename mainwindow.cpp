#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "crypt.h"
#include "cimageqt.h"

int nb_cesar;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_crypt_clicked()
{
    QString qs_crypt;
    QString qs_decrypt;
    std::string string_crypt;
    std::string string_decrypt;


    qs_crypt = ui->textEdit_crypt->toPlainText();
    string_crypt = qs_crypt.toLocal8Bit().constData();
    string_decrypt = code(string_crypt, nb_cesar);
    qs_decrypt = QString::fromStdString(string_decrypt);
    ui->textEdit_decrypt->setText(qs_decrypt);
}


void MainWindow::on_pushButton_parcourir_clicked()
{
    QString qs_fileName;
    std::string string_fileName;

    ui->pushButton_crypt->setEnabled(true);
    ui->pushButton_decrypt->setEnabled(true);

    qs_fileName = QFileDialog::getOpenFileName(this, tr("Selectionner un fichier"),
                                                     "",
                                                     tr("Images (*.bmp)"));

    string_fileName = qs_fileName.toLocal8Bit().constData();

    CImageQT import(string_fileName);

    nb_cesar = int(import(0,0));
}

void MainWindow::on_pushButton_decrypt_clicked()
{
    QString qs_crypt;
    QString qs_decrypt;
    std::string string_crypt;
    std::string string_decrypt;


    qs_decrypt = ui->textEdit_decrypt->toPlainText();
    string_decrypt = qs_decrypt.toLocal8Bit().constData();
    string_crypt = decode(string_decrypt, nb_cesar);
    qs_crypt = QString::fromStdString(string_crypt);
    ui->textEdit_crypt->setText(qs_crypt);
}
