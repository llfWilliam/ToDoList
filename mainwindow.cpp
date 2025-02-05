#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)//-------------------------------------------------------------初始化 ui 对象
{
    ui->setupUi(this);//-----------------------------------------------------------------设置 UI
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(onButtonAddPressed())); //-----------------连接信号和槽，当addButton发出了click信号以后执行槽函数addtask
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteTask()));//------------同上

    // 初始化优先级选择框
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::sortTasks() {
    std::sort(tasks.begin(), tasks.end());  // 根据优先级排序
}

void MainWindow::refreshTaskList() {
    ui->taskList->clear();  // 清空现有列表
    for (const Task &task : tasks) {
        QString taskDisplay = task.name + " - " + categoryToString(task.category) + " - " + priorityToString(task.priority);
        ui->taskList->addItem(taskDisplay);  // 将任务添加到列表控件
    }
}

QString MainWindow::categoryToString(Category category) {
    switch (category) {
        case Category::Work: return "工作";
        case Category::Personal: return "个人";
        case Category::Study: return "学习";
    }
    return "";
}

QString MainWindow::priorityToString(Priority priority) {
    switch (priority) {
        case Priority::High: return "高";
        case Priority::Medium: return "中";
        case Priority::Low: return "低";
    }
    return "";
}

void MainWindow::onButtonAddPressed() {
    QString taskName = ui->taskInput->text().trimmed();
    if (taskName.isEmpty()) {
        return;  // 如果任务名称为空，直接返回
    }

    // 获取用户选择的优先级和分类
    Category category = static_cast<Category>(ui->categoryComboBox->currentIndex());
    Priority priority = static_cast<Priority>(ui->priorityComboBox->currentIndex());

    // 创建新的任务
    Task task(taskName, category, priority);

    // 将任务添加到任务列表
    tasks.append(task);

    // 清空输入框
    ui->taskInput->clear();

    // 重新排序并刷新列表
    sortTasks();
    refreshTaskList();
}
void MainWindow::deleteTask()//----------------------------------------------------------构造删除任务函数
{
    QListWidgetItem *item = ui->taskList->currentItem();
    if (item) {
        delete item;
    } else {
        QMessageBox::warning(this, "警告", "请选择一个事项来进行删除。");
    }
}
