#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Structure to store a task and its status
struct Task {
    string description;
    bool completed;

    Task(string desc) : description(desc), completed(false) {}
};

// Function declarations
void addTask(vector<Task>& tasks);
void viewTasks(const vector<Task>& tasks);
void markTaskAsCompleted(vector<Task>& tasks);
void removeTask(vector<Task>& tasks);

int main() {
    vector<Task> tasks;
    int choice;

    do {
        // Display menu options
        cout << "\nTo-Do List Manager\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Remove Task\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Ignore newline left in input buffer after cin

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                markTaskAsCompleted(tasks);
                break;
            case 4:
                removeTask(tasks);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

// Function to add a new task
void addTask(vector<Task>& tasks) {
    string taskDescription;
    cout << "Enter the task description: ";
    getline(cin, taskDescription);
    tasks.push_back(Task(taskDescription));
    cout << "Task added successfully!\n";
}

// Function to view all tasks
void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks in the list.\n";
        return;
    }

    cout << "\nTo-Do List:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". " << tasks[i].description << " ["
             << (tasks[i].completed ? "Completed" : "Pending") << "]\n";
    }
}

// Function to mark a task as completed
void markTaskAsCompleted(vector<Task>& tasks) {
    int taskNumber;
    viewTasks(tasks); // Display the tasks first
    if (tasks.empty()) return;

    cout << "Enter the task number to mark as completed: ";
    cin >> taskNumber;

    if (taskNumber < 1 || taskNumber > tasks.size()) {
        cout << "Invalid task number!\n";
    } else {
        tasks[taskNumber - 1].completed = true;
        cout << "Task marked as completed.\n";
    }
}

// Function to remove a task from the list
void removeTask(vector<Task>& tasks) {
    int taskNumber;
    viewTasks(tasks); // Display the tasks first
    if (tasks.empty()) return;

    cout << "Enter the task number to remove: ";
    cin >> taskNumber;

    if (taskNumber < 1 || taskNumber > tasks.size()) {
        cout << "Invalid task number!\n";
    } else {
        tasks.erase(tasks.begin() + taskNumber - 1);
        cout << "Task removed successfully!\n";
    }
}
