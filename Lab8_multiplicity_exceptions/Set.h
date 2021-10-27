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
    static const int SIZE{3};
    T info_array[SIZE]{};
    int max_index{-1};

public:

    // Constructors and destructor
    Set() = default;

    void clear();

    // Methods
    void add(T new_obj);

    void show() const;

    void search() const;

    void delete_element();

    bool is_full() const;

    bool is_empty() const;

    //  void add(const Set<T> &another_set);

    // Overloads operators
    bool operator==(const Set<T> &another_set) const;

    bool operator!=(const Set<T> &another_set) const;

    // Example: (1, 2, 3, 4) + (2, 3, 4, 5) = (3, 5, 7, 9)
    friend Set<T> operator+(const Set<T> &set1, const Set<T> &set2) {

        set1.show ();
        set2.show ();

        Set<T> new_set;
        new_set.max_index = (set1.max_index > set2.max_index) ? set1.max_index : set2.max_index;

        for (int i = 0; i <= new_set.max_index; i++) {
            new_set.info_array[i] = set1.info_array[i] + set2.info_array[i];
        }

        return new_set;
    }
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
