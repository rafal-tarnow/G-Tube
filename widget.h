#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_pushButton_selectDownloadDir_clicked();

    void on_pushButton_startDownload_clicked();

private:
    void executeCommand();

private:
    QString videoURL;
    QString downloadDirecotry;
    QProcess *process;
    Ui::Widget *ui;
};
#endif // WIDGET_H
