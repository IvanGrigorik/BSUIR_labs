/*
 * Created by SiFi on 18.11.2021.
 * BSUiR, 2021
 */

#include "Ring.h"

// Constructor for Ring node in circle class

template<class T>
Ring<T>::Ring_node::Ring_node(T new_value) {
    value = new_value;
}




// Iterator fields
template<class T>
Ring<T>::iterator::iterator(Ring::Ring_node *new_ring_node) {
    ring_node = new_ring_node;
}

template<class T>
Ring<T>::iterator::iterator(const Ring::iterator &new_iterator) {
    ring_node = new_iterator.ring_node;
}



// Ring fields
// Constructors and destructor

template<class T>
Ring<T>::Ring() {
    enter = new Ring_node;
    enter->next = enter;

    is_ring_empty = true;

    enter_iterator = iterator(enter);
    pre_enter_iterator = iterator(enter);
}

template<class T>
Ring<T>::Ring(const T value) {
    is_ring_empty = false;

    enter = new Ring_node;
    enter->value = value;
    enter->next = enter;

    enter_iterator = iterator(enter);
    pre_enter_iterator = iterator(enter);
}


// Methods

template<class T>
void Ring<T>::add_front(T value) {
    auto *add_node = new Ring_node(value);

    if (!is_ring_empty) {
        add_node->next = enter;
        pre_enter_iterator.ring_node->next = add_node;

        enter_iterator = iterator(add_node);
        enter = add_node;
    } else if (is_ring_empty) {
        enter->value = value;
        is_ring_empty = false;
    }
}

template<class T>
void Ring<T>::add_back(T value) {
    auto *add_node = new Ring_node(value);

    if (!is_ring_empty) {
        pre_enter_iterator.ring_node->next = add_node;
        add_node->next = enter;

        pre_enter_iterator = iterator(add_node);
        enter_iterator = iterator(add_node->next);
    } else if (is_ring_empty) {
        enter->value = value;
        is_ring_empty = false;
    }
}

template<class T>
void Ring<T>::print() {

    for (auto temp = enter; temp->next != enter; temp = temp->next) {
        std::cout << temp->value << ' ';
    }
    std::cout << pre_enter_iterator.ring_node->value;
}

template<class T>
void Ring<T>::find(T find_value) {


}
