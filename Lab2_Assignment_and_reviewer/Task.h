//
// Created by Ivan on 07.09.2021.
//

#ifndef LAB2_ASSIGNMENT_AND_REVIEWER_TASK_H
#define LAB2_ASSIGNMENT_AND_REVIEWER_TASK_H

#include <iostream>
#include <string>

class Task {
public:
    using Id = int;
    using Name = std::string;
    using Result = int;

private:
    static Id total_id;
    Id id{};
    Name name;
    Result result{};

public:
    // Constructor's and destructor
    Task();

    Task(const Name &new_name, Result new_result);

    ~Task();

    // Getter's and setter's
    Id get_id() const;

    Name get_name() const;

    Result get_result() const;

    void set_name(const Name &new_name);

    void set_result(Result new_result);


    friend void show_info(const Task &task_to_show);

    friend class Verifier;

};


#endif //LAB2_ASSIGNMENT_AND_REVIEWER_TASK_H
