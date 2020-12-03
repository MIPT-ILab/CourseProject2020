 #include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->myableWidget;
}

void MainWindow::clearTable(){
    for (auto c : constructors)
        delete c;
    constructors.clear();
    ui->tabWidget->clear();
}

bool MainWindow::getJsonDoc(){
    QString inputPath = QFileDialog::getOpenFileName(this, "Открыть файл", "", "*.json");

    if (inputPath.isEmpty())
        return false;

    QFile json_file(inputPath);

    if (!json_file.exists()) {
        QMessageBox::warning(
            this,
            tr(APP_NAME),
            tr("File doesn't exist!") );
        return false;
    }

    json_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString json_string = json_file.readAll();
    json_file.close();

    document = QJsonDocument::fromJson(json_string.toUtf8());

    if (document.isNull()){
        QMessageBox::warning(
            this,
            tr(APP_NAME),
            tr("Wrong format!") );
        return false;
    }

    return true;
}

void MainWindow::on_upload_log_triggered() {

    if (!getJsonDoc())
        return;

    clearTable();

    QJsonArray tests = document.array();
    int i = 1;
    for (const auto t : tests) { 
        QJsonArray test;
        test = t.toArray();
        QWidget* tab = new QWidget();
        TableConstructor *constructor = new TableConstructor(test, tab);
        constructors.push_back(constructor);
        ui->tabWidget->addTab(tab, "test " + QString::number(i));
        ++i;
    }
}

void MainWindow::on_exit_triggered()
{
    clearTable();
    QApplication::quit();
}

void MainWindow::on_about_triggered()
{
    QMessageBox::information(
        this,
        tr("Vizualizer"),
        tr(MainWindow::about_text) );
}
