#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)  // 初始化 ui 对象
{
    ui->setupUi(this);  // 设置 UI

    // 连接信号和槽
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addTask()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteTask()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask()
{
    QString task = ui->taskInput->text().trimmed();
    if (!task.isEmpty()) {
        ui->taskList->addItem(task);
        ui->taskInput->clear();
    } else {
        QMessageBox::warning(this, "Warning", "Task cannot be empty.");
    }
}

void MainWindow::deleteTask()
{
    QListWidgetItem *item = ui->taskList->currentItem();
    if (item) {
        delete item;
    } else {
        QMessageBox::warning(this, "Warning", "Please select a task to delete.");
    }
}
