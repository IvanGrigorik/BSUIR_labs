//
// Created by Ivan on 07.09.2021.
//

#ifndef LAB2_ASSIGNMENT_AND_REVIEWER_TASK_H
#define LAB2_ASSIGNMENT_AND_REVIEWER_TASK_H

#include <iostream>
#include <string>

using namespace std;

class Task {
public:

private:
    static int total_id;
    int id{};
    string name;
    int result{};

public:
    // Constructor's and destructor
    Task();

    Task(const string &new_name, int new_result);

    ~Task();

    // Getter
    int get_result() const;


    friend void show_info(const Task &task_to_show);

    friend class Verifier;

};


#endif //LAB2_ASSIGNMENT_AND_REVIEWER_TASK_H
