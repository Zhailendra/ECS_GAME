/*
** PROJECT, 2024
** CPP_POOL
** File description:
** Node.hpp
*/

#pragma once

#include <iostream>


namespace game {

template <typename T>

    class Node {
        public:
            explicit Node(T elem) : elem(elem), next(nullptr) {};
            ~Node() = default;

            T elem;
            Node *next;
        protected:
        private:
    };

template <typename T>

    class List {
        public:
            List() : _head(nullptr), _length(0) {};
            ~List() {
                deleteList();
            };

            void addNode(T elem);
            void InsertNode(T elem, int pos);

            void deleteNode(T elem);
            void deleteList();

            bool searchNode(T elem);

            void displayList();

        protected:
            int _length;
        private:
            Node<T> *_head;
    };

    template <typename T>

    void List<T>::addNode(T elem) {
        Node<T> *newNode = new Node<T>(elem);
        Node<T> *tmp = _head;
        _length++;

        if (_head == nullptr) {
            _head = newNode;
            return;
        }
        while (tmp->next != nullptr) {
            tmp = tmp->next;
        }
        tmp->next = newNode;
    }

    template<typename T>
    void List<T>::InsertNode(T elem, int pos) {
        Node<T> *newNode = new Node<T>(elem);
        Node<T> *tmp = _head;
        Node<T> *prev = nullptr;

        if (pos < 0) {
            std::cout << "Invalid position" << std::endl;
            return;
        }

        if (pos == 0) {
            std::cout << "The element " << elem << " is inserted at the beginning" << std::endl;
            newNode->next = _head;
            _head = newNode;
            return;
        }
        for (int i = 0; tmp != nullptr && i < pos; i++) {
            prev = tmp;
            tmp = tmp->next;
        }
        if (tmp == nullptr) {
            std::cout << "The element " << elem << " is inserted at the end" << std::endl;
            prev->next = newNode;
            return;
        }
        std::cout << "The element " << elem << " is inserted at the position " << pos << std::endl;
        prev->next = newNode;
        newNode->next = tmp;
    }

    template <typename T>

    void List<T>::deleteNode(T elem) {
        Node<T> *tmp = _head;
        Node<T> *prev = nullptr;

        if (tmp != nullptr && tmp->elem == elem) {
            std::cout << "The first element " << elem << " is deleted" << std::endl;
            _head = tmp->next;
            delete tmp;
            return;
        }
        while (tmp != nullptr && tmp->elem != elem) {
            prev = tmp;
            tmp = tmp->next;
        }
        if (tmp == nullptr) {
            std::cout << "Element not found" << std::endl;
            return;
        }
        prev->next = tmp->next;
        std::cout<< "Element " << elem << " is deleted" << std::endl;
        delete tmp;
    }

    template<typename T>
    void List<T>::deleteList() {
        Node<T> *tmp = _head;
        Node<T> *next = nullptr;

        while (tmp != nullptr) {
            next = tmp->next;
            _length--;
            delete tmp;
            tmp = next;
        }
        _head = nullptr;
    }

    template <typename T>

    bool List<T>::searchNode(T elem) {
        Node<T> *tmp = _head;

        while (tmp != nullptr) {
            if (tmp->elem == elem) {
                std::cout << "Element " << elem << " is found" << std::endl;
                return true;
            }
            tmp = tmp->next;
        }
        std::cout << "Element " << elem << " is not found" << std::endl;
        return false;
    }

    template <typename T>
    void List<T>::displayList() {
        Node<T> *tmp = _head;

        while (tmp != nullptr) {
            std::cout << tmp->elem << " ";
            tmp = tmp->next;
        }

        if (_length == 0) {
            std::cout << "The list is empty" << std::endl;
        } else {
            std::cout << std::endl;
        }
    }
}

