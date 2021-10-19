//
// Created by Ivan on 19.10.2021.
//

#ifndef LAB8_MULTIPLICITY_EXCEPTIONS_MULTIPLICITY_INL
#define LAB8_MULTIPLICITY_EXCEPTIONS_MULTIPLICITY_INL

#include <exception>
#include <iostream>

using namespace std;

template<class T>
class Set {
private:
    static const int SIZE = 10;
    T info_array[SIZE];
    int index{};

public:

    // Constructors and destructor
    Set() : info_array (), index (0) {};

    Set(const Set<T> const &to_copy);

    ~Set() { delete[] info_array; };


    // Methods
    void add(T new_obj);

    void show() const;

    bool is_full() const;

    bool is_empty() const;

    // Operations
    bool operator==(const Set<T> &another_set) const;

    bool operator!=(const Set<T> &another_set) const;

    // Example: (1, 2, 3, 4) + (2, 3, 4, 5) = (3, 5, 7, 9)
    Set<T> operator+(const Set<T> &another_set) const;
};



class Set_ex : public exception {
private:
    string error_message{};

public:
    explicit Set_ex(string message) : error_message (move (message)) {};

    const char *what() const noexcept override {
        return error_message.c_str ();
    }
};


#include "Set.inl"

#endif //LAB8_MULTIPLICITY_EXCEPTIONS_MULTIPLICITY_INL
