#include <iostream>
#include <string>
#include <vector>

struct Task {
    int id;
    std::string title;
    std::string description;
    bool completed;
};

void addTask(std::vector<Task>& tasks, const std::string& title, const std::string& description) {
    int newId = tasks.size() + 1;
    tasks.push_back({ newId, title, description, false });
    std::cout << "Task added!" << std::endl;
}

void completeTask(std::vector<Task>& tasks, int id) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task.completed = true;
            std::cout << "Task " << id << " completed!" << std::endl;
            return;
        }
    }
    std::cout << "Task not found!" << std::endl;
}

void showTasks(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks." << std::endl;
        return;
    }
    for (const auto& task : tasks) {
        std::cout << "ID: " << task.id
            << ", Title: " << task.title
            << ", Completed: " << (task.completed ? "Yes" : "No")
            << std::endl;
    }
}

int main() {
    std::vector<Task> tasks;

    addTask(tasks, "Купить хлеб", "Вечером после работы");
    addTask(tasks, "Позвонить маме", "Напомнить о встрече");
    showTasks(tasks);

    completeTask(tasks, 1);
    showTasks(tasks);

    return 0;
}