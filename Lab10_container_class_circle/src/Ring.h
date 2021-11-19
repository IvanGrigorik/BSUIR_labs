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

        friend std::ostream &operator<<(std::ostream &os, const Ring_node &node) {
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

        bool operator==(const iterator &iterator_to_compare) const {
            return iterator_to_compare.ring_node == ring_node;
        }

        bool operator!=(const iterator &iterator_to_compare) const {
            return iterator_to_compare.ring_node != ring_node;
        }

        Ring_node get_data() {
            return *ring_node;
        };

        iterator &operator++() {

            ring_node = ring_node->next;
            return *this;
        }

        T &operator*() const {
            return ring_node->value;
        }

        bool is_valid_iterator() const {
            return ring_node != nullptr;
        }
    };

private:

    Ring_node *enter{};

    bool is_ring_empty{};

    iterator enter_iterator{};
    iterator pre_enter_iterator{};


public:


    Ring();

    explicit Ring(T value);

    ~Ring() = default;

    bool is_empty() {
        return is_ring_empty;
    };

    void add_front(T value);

    void add_back(T value);

    void print();

    iterator find(T find_value) {
        for (auto it = begin(); it != end(); ++it) {
            if (it.ring_node->value == find_value) {
                return it;
            }
        }

        if (end().ring_node->value == find_value) {
            return end();
        } else {
            std::cout << "No such element in ring";

            return iterator(nullptr);
        }
    }

    void delete_element(const iterator &it) {

        if (!it.is_valid_iterator()) {
            throw std::runtime_error("Invalid iterator");
        }

        // If we have one element in ring
        if (it.ring_node->next == it.ring_node) {


            delete enter;

            enter_iterator.ring_node = nullptr;
            pre_enter_iterator.ring_node = nullptr;

            is_ring_empty = true;


            return;
        }

        if (it.ring_node == enter) {

            auto temp = enter;

            enter = enter->next;

            enter_iterator.ring_node = enter;
            pre_enter_iterator.ring_node->next = enter;

            delete temp;
            return;
        }

        auto runner_it = enter_iterator;

        for (; runner_it != end(); ++runner_it) {

            if (runner_it.ring_node->next == it.ring_node) {

                auto delete_ptr = it.ring_node;

                runner_it.ring_node->next = it.ring_node->next;

                if (it.ring_node == pre_enter_iterator.ring_node) {
                    pre_enter_iterator = runner_it;
                }

                delete delete_ptr;
                return;
            }
        }


        std::cout << "No such element in ring";
    }

    iterator begin() {
        return iterator(enter);
    }

    iterator end() {
        return pre_enter_iterator;
    }
};

/*
 * Заходим в цикл.
 * Чтобы первое условие проверки всегда выполнялось мы сравниваем наш итератор с итератором, указатель которого раен нулю.
 * После первого вызова .end() теперь возвращает итератор с нужным нам указателем.
 *
 * В методе .end()
 *
 * if(temp == tail){
 *  temp = head->next;
 * }
 *
 */



/* Создать две головы. Вторая замыкает кольцо. Указатель второй головы ссылается на nullptr. */

#include <ostream>
#include "Ring.inl"