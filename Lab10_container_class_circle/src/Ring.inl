/*
 * Created by SiFfi on 18.11.2021.
 * BSUiR, 2021
 */

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
    is_ring_empty = true;

    enter = new Ring_node;
    enter->next = enter;

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

        enter = add_node;
        enter_iterator = iterator(enter);
    } else if (is_ring_empty) {

        enter = new Ring_node(value);

        is_ring_empty = false;

        enter->next = enter;

        pre_enter_iterator.ring_node = enter;
        enter_iterator.ring_node = enter;
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

        enter = new Ring_node(value);
        is_ring_empty = false;

        enter->next = enter;

        pre_enter_iterator.ring_node = enter;
        enter_iterator.ring_node = enter;
    }

}

template<class T>
void Ring<T>::print() {

    if (is_ring_empty) {
        std::cout << "Ring empty" << std::endl;
        return;
    }

    for (auto temp = enter_iterator; temp != end(); ++temp) {
        std::cout << temp.ring_node->value << ' ' << std::endl;
    }

    std::cout << pre_enter_iterator.ring_node->value << std::endl;

}
