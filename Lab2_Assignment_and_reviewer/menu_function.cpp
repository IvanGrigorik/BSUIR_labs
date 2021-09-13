//
// Created by Ivan on 09.09.2021.
//

#include "menu_function.h"


int get_menu_choice () {
    system("cls");
    cout << "Enter what you want to enter: " <<
         endl << "1) Add new task " <<
         endl << "2) Show tasks with a specific percentage" <<
         endl << "3) Show all tasks" <<
         endl << "0) Exit" <<
         endl << ">> ";

    int choice;
    get_int(choice, 3);
    return choice;
}

void get_int (int &y, int max_size) {
    int x;
    while (true) {
        cin >> x;

        if (cin.fail() || cin.peek() != '\n' || x < 0 || x > max_size) {
            cout << "Invalid input, try again" << endl << ">>";
            cin.clear();
            cin.ignore(32768, '\n');
        } else {
            y = x;
            return;
        }
    }
}

void add_task (list<Task> &tasks) {
    cout << "Enter name: ";
    string new_name;
    cin >> new_name;
    tasks.emplace_back(new_name);

    cout << "Enter new result: ";
    int new_result;
    do{
        get_int(new_result, 100);
    }while(Verifier::set_result(tasks.back(), new_result));
}

void show_tasks (const list<Task> &tasks) {
    for (auto &task: tasks)
        show_info(task);
    system("pause > 0");
}

void show_specific_tasks (const list<Task> &tasks) {
    cout << "Enter percentage: ";
    int percent;
    cin >> percent;
    for (auto &task: tasks) {
        if (task.get_result() == percent)
            show_info(task);
    }
    system("pause > 0");
}