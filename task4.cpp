#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int MAX_TASKS = 10;

void displayMenu() {
    cout<<"\n======= To-Do List =======\n";
    cout<<"1. Add Task\n";
    cout<<"2. View Tasks\n";
    cout<<"3. Delete Task\n";
    cout<<"4. Exit\n";
    cout<<"==========================\n";
    cout<<"Enter your choice: ";
}

void addTask(string tasks[], int&taskCount) {
    if (taskCount < MAX_TASKS) {
        string task;
        cout<<"Enter task: ";
        cin.ignore();
        getline(cin,task);
        tasks[taskCount] = task;
        taskCount++;
        cout<<"Task added successfully!\n";
    } else {
        cout<<"Task limit reached. Delete tasks to add more.\n";
    }
}

void viewTasks(const string tasks[], int taskCount) {
    cout<<"\n======= Tasks =======\n";
    for (int i=0; i<taskCount; ++i) {
        cout<<i+1 <<". "<<tasks[i]<<"\n";
    }
    cout<<"=====================\n";
}

void deleteTask(string tasks[], int& taskCount) {
    if (taskCount > 0) {
        viewTasks(tasks, taskCount);
        int taskNumber;
        cout<<"Enter the task number to delete: ";
        cin>>taskNumber;

        if (taskNumber>=1 && taskNumber<=taskCount) {
            for (int i =taskNumber-1; i<taskCount-1; ++i) {
                tasks[i] = tasks[i + 1];
            }
            taskCount--;
            cout<<"Task deleted successfully!\n";
        } else {
            cout<<"Invalid task number.\n";
        }
    } else {
        cout<<"No tasks to delete.\n";
    }
}

void writeTasksToFile(const string tasks[], int taskCount) {
    ofstream file("tasks.txt");
    for (int i=0; i<taskCount; ++i) {
        file<<tasks[i] << "\n";
    }
    file.close();
}

void readTasksFromFile(std::string tasks[], int& taskCount) {
    ifstream file("tasks.txt");
    string task;
    taskCount = 0;

    while(getline(file, task)&&taskCount < MAX_TASKS) {
        tasks[taskCount++] = task;
    }

    file.close();
}

int main() {
    string tasks[MAX_TASKS];
    int taskCount = 0;
    int choice;

    // Load tasks from file
    readTasksFromFile(tasks, taskCount);

    do {
        displayMenu();
        cin>>choice;

        switch (choice) {
            case 1:
                addTask(tasks, taskCount);
                break;
            case 2:
                viewTasks(tasks, taskCount);
                break;
            case 3:
                deleteTask(tasks, taskCount);
                break;
            case 4:
                // Save tasks to file before exiting
                writeTasksToFile(tasks, taskCount);
                cout<<"Exiting program. Goodbye!\n";
                break;
            default:
                cout<<"Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
