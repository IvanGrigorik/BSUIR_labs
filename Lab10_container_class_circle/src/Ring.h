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

        friend std::ostream &operator<<(std::ostream &os, const Ring_node &node){
            os << node.value;
            return os;
        }
    };

public:
    class iterator {
        friend class Ring<T>;

        Ring_node *ring_node;

    public:
        // Constructors
        iterator() : ring_node(nullptr) {};

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

        bool operator==(const iterator &iterator_to_compare) {
            return iterator_to_compare.ring_node == ring_node;
        }

        bool operator!=(const iterator &iterator_to_compare) {
            return iterator_to_compare.ring_node != ring_node;
        }

        Ring_node get_data(){
            return *ring_node;
        };

        iterator &operator++() {
            ring_node = ring_node->next;
            return *this;
        }

        T &operator*() const {
            return ring_node->value;
        }
    };

private:
    Ring_node *enter{nullptr};
    bool is_ring_empty{};

    iterator enter_iterator;
    iterator pre_enter_iterator;


public:

    Ring();

    explicit Ring(T value);

    ~Ring() = default;

    bool is_empty() {
        return enter->next == enter;
    };

    void add_front(T value);

    void add_back(T value);

    void print();

    void find(T find_value);

    iterator begin() {
        return iterator(enter);
    }

    iterator end() {

        Ring_node *temp = enter;
        while (temp->next != enter) {
            temp = temp->next;
        }

        return iterator(temp);
    }
};

/*
 * Заходим в цикл.
 * Чтобы первое условие проверки всегда выполнялось мы сравниваем наш итератор с итератором, указатель которого раен нулю.
 * После первого вызова .end() теперь возвращает итератор с нужным нам указателем.
 *
 * В методе .end()
 */
#include <ostream>
#include "Ring.inl"