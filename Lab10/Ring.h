/*
 * Created by Ivan on 18.11.2021.
 * BSUiR, 2021
 */

#pragma once

#include <iostream>

template<typename T, bool is_unique_ring>
class Ring {

public:
    class Node {
    public:
        T data;
        Node *next;

        explicit Node(T value) : data(value) {};

        ~Node() { delete next; }
    };

    class Iterator {
    private:
        friend class Ring;

        Node *ring_node_ptr;

    public:
        // Constructors
        Iterator() : ring_node_ptr(nullptr) {};

        explicit Iterator(Node *ptr) : ring_node_ptr(ptr) {};

        Iterator(const Iterator &it) : ring_node_ptr(it.ring_node_ptr) {};


        // Overload assign operator
        Iterator &operator=(const Iterator &it) {
            if (it != this) {
                ring_node_ptr = it.ring_node_ptr;
            }

            return *this;
        }

        // Overload boolean operators
        bool operator==(const Iterator &it) {
            return it.ring_node_ptr == ring_node_ptr;
        }

        bool operator!=(const Iterator &it) {
            return it.ring_node_ptr != ring_node_ptr;
        }

        // Move operators
        Iterator &operator++() {

            if (!ring_node_ptr) {
                throw std::runtime_error("Empty ring.");
            }

            if (!ring_node_ptr->next) {
                ring_node_ptr = enter;
            } else {
                ring_node_ptr = ring_node_ptr->next;
            }
            return *this;
        }

        T operator*() {
            if (!ring_node_ptr) {
                throw std::runtime_error("Empty ring.");
            }
            return ring_node_ptr->data;
        }
    };

private:
    Node *enter;
    Node *tail;

public:

    Ring(const Ring &) = delete;

    Ring &operator=(Ring &) = delete;


    // Constructors
    Ring() : enter(nullptr), tail(nullptr) {};

    virtual ~Ring() {
        delete enter;
        delete tail;
    }


    // Iterator functions
    Iterator begin() const {
        return Iterator(enter);
    }

    Iterator end() const {
        return Iterator(tail);
    }

    void push(Iterator &position, const T &value) {
        // If every value in container must bee unique
        if (is_unique_ring) {
            //
        }

        if (position == begin()) {
            auto new_head = new Node(value);
            new_head->next = enter;
            enter = new_head;
            return;
        }

        for (auto it = begin(); it != end(); ++it) {
            if (it.ring_node_ptr->next == position.ring_node_ptr) {
                auto new_ring_node = new Node(value);
                new_ring_node->next = it.ring_node_ptr->next;
                it.ring_node_ptr->next = new_ring_node;
                return;
            }
        }
    };

    friend class Iterator;
};