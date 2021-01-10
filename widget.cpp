#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDebug>
#include <QDir>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    process = new QProcess(this);
    ui->plainTextEdit->setReadOnly(true);
    ui->lineEdit->setClearButtonEnabled(true);


    connect(process, &QProcess::readyReadStandardOutput, [=](){
        ui->plainTextEdit->setStyleSheet("QPlainTextEdit {background-color: black; color: green;}");
        ui->plainTextEdit->appendPlainText(process->readAllStandardOutput()); });
    connect(process, &QProcess::readyReadStandardError, [=](){
        ui->plainTextEdit->setStyleSheet("QPlainTextEdit {background-color: black; color: red;}");
        ui->plainTextEdit->appendPlainText(process->readAllStandardError()); });
    //connect(process, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), this, &Widget::close);
    connect(ui->lineEdit, &QLineEdit::returnPressed, [=](){ process->write(ui->lineEdit->text().toLatin1() + "\n"); ui->lineEdit->clear(); });

}

void Widget::on_pushButton_startDownload_clicked()
{
    executeCommand();
}

void Widget::executeCommand()
{
    videoURL = ui->lineEdit_videoURL->text();

    QStringList arguments;
    arguments << "-o";
    if(ui->checkBox_autonumber->isChecked())
    {
        arguments << (downloadDirecotry + "%(autonumber)s-%(title)s-%(id)s.%(ext)s");
    }
    else
    {
        arguments << (downloadDirecotry + "%(title)s-%(id)s.%(ext)s");
    }

    arguments << videoURL;

    if(ui->checkBox_aria2c->isChecked())
    {
        arguments << "--external-downloader";
        arguments << "aria2c";
        arguments << "--external-downloader-args";
        arguments << "-x 16 -s 16 -k 1M";
    }

    process->start("youtube-dl", arguments);
}

Widget::~Widget()
{
    process->close();
    delete process;

    delete ui;
}



void Widget::on_pushButton_selectDownloadDir_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setOption(QFileDialog::ShowDirsOnly, false);
    dialog.exec();

    QDir dir = dialog.directory();
    downloadDirecotry = dir.path() + "/";
    qDebug() << downloadDirecotry << endl;

    ui->label_downloadDir->setText("DOWNLOAD DIR: " + downloadDirecotry);
}


