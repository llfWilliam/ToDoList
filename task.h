#ifndef TASK_H
#define TASK_H
#include <QString>


enum class Priority {
    High,
    Medium,
    Low
};

enum class Category {
    Work,
    Personal,
    Study
};

class Task {
public:
    QString name;
    Category category;
    Priority priority;

    Task(const QString &name, Category category, Priority priority)
        : name(name), category(category), priority(priority) {}

    // 为了排序，我们需要比较任务的优先级
    bool operator<(const Task &other) const {
        return priority < other.priority;
    }
};
#endif // TASK_H
