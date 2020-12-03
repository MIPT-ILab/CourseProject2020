#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <tableconstructor.h>
#include <QMainWindow>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <mytablewidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    const char* about_text = "This app uses Andrey Karpiza logs to visualize cpu pipiline.\n"
                             "Made by Alex Kulsha\n"
                             "BSUIR, group 853506";
    const char* APP_NAME = "Vizualizer";
    QJsonDocument document;
    QVector<TableConstructor*> constructors;
    void clearTable();
    bool getJsonDoc();
    MyTableWidget *myableWidget;

private slots:

    void on_upload_log_triggered();
    void on_exit_triggered();
    void on_about_triggered();
};

#endif // MAINWINDOW_H
