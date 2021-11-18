/*
 * Created by Ivan on 18.11.2021.
 * BSUiR, 2021
 */

#pragma once

template<class T>
class Ring {

private:
    class Ring_node {
    public:
        Ring_node *next;
        T value{};

        explicit Ring_node(T new_value);

        Ring_node() = default;

        ~Ring_node() = default;
    };

public:
    class iterator {
        friend class Ring<T>;

        Ring_node *ring_node;

    public:
        // Constructors
        iterator() = default;

        explicit iterator(Ring_node *new_ring_node);

        iterator(const iterator &new_iterator);

        // Operators
        iterator &operator=(const iterator &iterator_to_copy) {
            // Check for self-implemented
            if (&iterator_to_copy != this) {
                ring_node = iterator_to_copy.ring_node;
            }
            return *this;
        }

        iterator &operator==(const iterator &iterator_to_compare) {
            return iterator_to_compare.ring_node == ring_node;
        }

        iterator &operator!=(const iterator &iterator_to_compare) {
            return iterator_to_compare.ring_node != ring_node;
        }

        iterator &operator++() {
            ring_node = ring_node->next;
            return *this;
        }

        T &operator*() const {
            return ring_node->value;
        }
    };

private:
    Ring_node *enter;
    bool is_begin_called{};


public:

    Ring();

    explicit Ring(T value);

    ~Ring();

/*    iterator iterator_head() {
        return enter;
    }

    iterator iterator_tail() {
        return pre_enter_iterator;
    }*/

    bool is_empty() {
        return enter->next == enter;
    };

    void add_front(T value);

    void add_back(T value);

    void print();

    void begin();

    void end();
};

/*
 * Заходим в цикл.
 * Чтобы первое условие проверки всегда выполнялось мы сравниваем наш итератор с итератором, указатель которого раен нулю.
 * После первого вызова .end() теперь возвращает итератор с нужным нам указателем.
 *
 * В методе .end()
 */
#include "Ring.inl"