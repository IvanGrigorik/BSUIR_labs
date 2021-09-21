//
// Created by Ivan on 07.09.2021.
//

#include "Verifier.h"

bool Verifier::set_result (Task &task, int new_result) {
    if (new_result > 100) {
        cout << "Invalid input of the new result!";
        return false;
    }
    task.result = new_result;
    return true;
}
