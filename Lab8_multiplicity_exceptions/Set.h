//
// Created by Ivan on 19.10.2021.
//

#ifndef LAB8_MULTIPLICITY_EXCEPTIONS_MULTIPLICITY_INL
#define LAB8_MULTIPLICITY_EXCEPTIONS_MULTIPLICITY_INL

#include <exception>
#include <iostream>
#include "menu_functions.h"

template<class T>
class Set {
private:
    static const int SIZE = 3;
    T info_array[SIZE];
    int max_index = -1;

public:

    // Constructors and destructor
    Set();

    Set(const Set<T> &to_copy);

    void clear();

    // Methods
    void add(T new_obj);

    void show() const;

    void search() const;

    void delete_element();

    bool is_full() const;

    bool is_empty() const;

    // Overloads operators
    bool operator==(const Set<T> &another_set) const;

    bool operator!=(const Set<T> &another_set) const;

    // Example: (1, 2, 3, 4) + (2, 3, 4, 5) = (3, 5, 7, 9)
    Set<T> operator+(const Set<T> &another_set) const;
};

class Set_ex : public std::exception {
private:
    std::string error_message{};

public:
    explicit Set_ex(std::string message) : error_message (move (message)) {};

    const char *what() const noexcept override {
        return error_message.c_str ();
    }
};

#include "Set.inl"

#endif //LAB8_MULTIPLICITY_EXCEPTIONS_MULTIPLICITY_INL
