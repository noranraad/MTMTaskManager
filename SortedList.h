#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {
    class Exception : public std::out_of_range {
    public:
        Exception() : std::out_of_range("SortedList iterator out of range"){}
    };

    template <typename T>
    class SortedList {
        struct Node {
            T data;
            Node* next = nullptr;
            Node(const T& value, Node* nextNode) : data(value), next(nextNode){}
        };

        Node<T>* head = nullptr;

    public:
        SortedList() = default;

        SortedList& insert(const T& elem) {
            Node* newNode = new Node<T>{elem, nullptr};

            if (head == nullptr || elem > head->data) {
                newNode->next = head;
                head = newNode;
                return *this;
            }

            Node* curr = head;

            while (curr->next != nullptr &&
                   !(elem > curr->next->data)) {
                curr = curr->next;
                   }

            newNode->next = curr->next;
            curr->next = newNode;

            return *this;
        }

        SortedList(const SortedList& other):head(nullptr) {
            const Node<T>* curr = other.head;
            while (curr != nullptr) {
                insert(curr->data);
                curr = curr->next;
            }
        }

        SortedList& operator=(const SortedList& other) {
            if (this == &other) {
                return *this;
            }

            SortedList temp(other);

            Node* tempHead = head;
            head = temp.head;
            temp.head = tempHead;

            return *this;
        }

        ~SortedList() {
            while (head != nullptr) {
                Node* nodeToDelete = head;
                head = head->next;
                delete nodeToDelete;
            }
        }

        

        class ConstIterator;
        typedef const char* constIterator;
        constIterator begin() const;
        constIterator end() const;

        int length() const {
            const Node<T>* curr = head;
            int cnt = 0;
            while (curr != nullptr) {
                cnt++;
                curr = curr->next;
            }
            return cnt;
        }


        /**
         *
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. SortedList() - creates an empty list.
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~SortedList() - destructor
         *
         * iterator:
         * 5. class ConstIterator;
         * 6. begin method
         * 7. end method
         *
         * functions:
         * 8. insert - inserts a new element to the list
         * 9. remove - removes an element from the list
         * 10. length - returns the number of elements in the list
         * 11. filter - returns a new list with elements that satisfy a given condition
         * 12. apply - returns a new list with elements that were modified by an operation
         */

    };

    template <class T>
    class SortedList<T>::ConstIterator {
        SortedList<T>* sortedList;
        int index;

    public:

        ConstIterator() : sortedList(nullptr), index(0) {}

        ConstIterator& operator++() {
            index--;
            if (index > SortedList<T>::length || index < 0) throw Exception();
            return *this;
        }

        bool operator!=(const ConstIterator& other) const{
            if (index > SortedList<T>::length || index < 0) throw Exception();
            return this->index != other.index;
        }

        T* operator*() const{
            if (index > SortedList<T>::length || index < 0) throw Exception();
            return sortedList->head->data[index];
        }

    /**
     * the class should support the following public interface:
     * if needed, use =defualt / =delete
     *
     * constructors and destructor:
     * 1. a ctor(or ctors) your implementation needs
     * 2. copy constructor
     * 3. operator= - assignment operator
     * 4. ~ConstIterator() - destructor
     *
     * operators:
     * 5. operator* - returns the element the iterator points to
     * 6. operator++ - advances the iterator to the next element
     * 7. operator!= - returns true if the iterator points to a different element
     *
     */
    };
}

