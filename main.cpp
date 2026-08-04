#include <iostream>
using namespace std;
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>

struct Task
{
	int id;
	string title;
	string description;
	bool completed;
	string createdAt;
};

void addTask(vector<Task>& tasks)
{
	Task newTask;
	string tit, des;
	cout << "Введите название: "; 
	cin >> tit;
	cout << endl;
	cout << "Введите описание: ";
	cin >> des;

	newTask.title = tit;
	newTask.description = des;
	newTask.id = tasks.size() + 1;
	newTask.completed = false;

	time_t now = time(nullptr);
	tm* local = localtime(&now);
	char buffer[11];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d", local);
	newTask.createdAt = buffer;

	tasks.push_back(newTask);
	cout << "Задание добавлено" << endl;
}

void showTasks(vector<Task>& tasks)
{
	if (tasks.empty() == 1)
	{
		cout << "Нет задач" << endl;
		return;
	}
	for (auto& task : tasks)
	{
		cout << "ID: " << task.id << ", название: " << task.title << ", выполнение: " << (task.completed ? "Да" : "Нет") << ", дата: " << task.createdAt << endl;
	}
}

void completeTask(vector<Task>& tasks)
{
	int num = 0;
	cout << "Введите id выполненного задания: ";
	cin >> num;
	for (auto& task : tasks)
	{
		if (num == task.id)
		{
			task.completed = true;
			break;
		}
	}
}

void saveToFile(vector <Task>& tasks)
{
	ofstream file("tasks.txt");
	if (!file.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
		return;
	}
	for (auto& task : tasks)
	{
		file << task.id << "|" 
			<< task.title << "|"
			<< task.description << "|"
			<< task.completed << "|"
			<< task.createdAt << endl;
	}
	file.close();
	cout << "Задачи сохранены" << endl;
}

vector <string> split(string fullLine, char symbol)
{
	vector <string> parts;
	int start = 0;
	int end = 0;

	while (true)
	{
		end = fullLine.find(symbol);
		if (end == string::npos) {
			break;
		}
		parts.push_back(fullLine.substr(start, end - start));
		start = end + 1;
	}
	parts.push_back(fullLine.substr(start));
	return parts;
}

void loadFromFile(vector<Task>& tasks) {
	ifstream file("task.txt");
	if (!file.is_open()) {
		cout << "Ошибка открытия файла" << endl;
		return;
	}

	tasks.clear();
	string line;

	while (getline(file, line)) {
		vector<string> parts = split(line, '|');

		if (parts.size() != 5) {
			continue;   
		}

		Task task;
		task.id = stoi(parts[0]);
		task.title = parts[1];
		task.description = parts[2];
		task.completed = stoi(parts[3]);
		task.createdAt = parts[4];

		tasks.push_back(task);
	}

	cout << "Загружено " << tasks.size() << " задач" << endl;
}

void editText(vector<Task>& tasks)
{
	int choose = 0;
	int change = 0;
	string tit;
	string dis;
	cout << "Введите id заадчи, которую хотите поменять: ";
	cin >> choose;
	for (auto& task : tasks)
	{
		if (task.id == choose)
		{
			cout << "ID: " << task.id << ", название: " << task.title << ", выполнение: " << (task.completed ? "Да" : "Нет") << endl;
			cout << "Что хотете поменять в данной заадче" << endl
				<< "1. Название" << endl
				<< "2. Описание" << endl;
			cin >> change;
			switch (change)
			{
			case 1:
				cout << "Введите новое название: ";
				getline(cin, tit);
				task.title = tit;
				break;
			case 2:
				cout << "Введите новое описание: ";
				getline(cin, dis);
				task.description = dis;
				break;
			default:
				cout << "Ошибка выбора" << endl;
			}
			return;
		}
	}
	cout << "Данная задача не надо" << endl;
}

void deleteTask(vector<Task>& tasks)
{
	int choose = 0;
	cout << "Введите id заадчи, которую хотите поменять: ";
	cin >> choose;
	for (int i = 0; i < tasks.size(); i ++)
	{
		if (tasks[i].id == choose)
		{
			tasks.erase(tasks.begin() + i);
			return;
		}
	}
	cout << "Данная задача не надо" << endl;
}

void showPendingTasks(vector<Task>& tasks)
{
	for (auto& task : tasks)
	{
		if (task.completed = "no")
		{
			cout << "ID: " << task.id << ", название: " << task.title << ", выполнение: " << (task.completed ? "Да" : "Нет") << ", дата: " << task.createdAt << endl;
		}
	}
}

int main() {
	vector<Task> tasks;
	loadFromFile(tasks);
	int choose = 0;
	while (choose != 9)
	{
		cout << "1. Add task" << endl <<
			"2. Complete task" << endl <<
			"3. Show all tasks" << endl <<
			"4. Сохранить данные в файл" << endl <<
			"5. Выгрузить данные из файла" << endl <<
			"6. Показать невыполненные задачи" << endl <<
			"7. Редактировать задачу" << endl <<
			"8. Удалить задачу" << endl <<
			"9. Exit";
		cin >> choose;
		switch (choose) {
		case 1:
			addTask(tasks);
			break;
		case 2:
			completeTask(tasks);
			break;
		case 3:
			showTasks(tasks);
			break;
		case 4:
			saveToFile(tasks);
			break;
		case 5:
			loadFromFile(tasks);
			break;
		case 6: 
			showPendingTasks(tasks);
			break;
		case 7: 
			editText(tasks); 
			break;
		case 8: 
			deleteTask(tasks); 
			break;
		case 9:
			saveToFile(tasks);
			cout << "Досвидания" << endl;
			return 0;
		default:
			cout << "Неверный выбор";
		}
	}
}