#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)//-------------------------------------------------------------初始化 ui 对象
{
    ui->setupUi(this);//-----------------------------------------------------------------设置 UI
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addTask())); //-----------------连接信号和槽，当addButton发出了click信号以后执行槽函数addtask
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteTask()));//------------同上
    ui->categoryComboBox->addItem("工作");
    ui->categoryComboBox->addItem("个人");
    ui->categoryComboBox->addItem("学习");

    // 初始化优先级选择框
    ui->priorityComboBox->addItem("高");
    ui->priorityComboBox->addItem("中");
    ui->priorityComboBox->addItem("低");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void sortTasks() {
    std::sort(tasks.begin(), tasks.end());  // 根据优先级排序
}

void refreshTaskList() {
    ui->taskListWidget->clear();  // 清空现有列表
    for (const Task &task : tasks) {
        QString taskDisplay = task.name + " - " + categoryToString(task.category) + " - " + priorityToString(task.priority);
        ui->taskListWidget->addItem(taskDisplay);  // 将任务添加到列表控件
    }
}

QString categoryToString(Category category) {
    switch (category) {
        case Category::Work: return "工作";
        case Category::Personal: return "个人";
        case Category::Study: return "学习";
    }
    return "";
}

QString priorityToString(Priority priority) {
    switch (priority) {
        case Priority::High: return "高";
        case Priority::Medium: return "中";
        case Priority::Low: return "低";
    }
    return "";
}

void onButtonAddPressed() {
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
