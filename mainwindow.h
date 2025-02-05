#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QComboBox>
#include <task.h>
#include <QVector>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void deleteTask();
    void onButtonAddPressed();

private:
    Ui::MainWindow *ui;
    QVector<Task> tasks;
    void sortTasks();
    void refreshTaskList();
    QString categoryToString(Category category);
    QString priorityToString(Priority priority);
};


#endif // MAINWINDOW_H
