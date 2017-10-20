#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <memory>
#include "mirageexception.h"

template<typename T>
class LinkedList {
    struct Node {
            T value;
            std::shared_ptr<LinkedList<T>::Node> next;
            Node(T value, std::shared_ptr<LinkedList<T>::Node> next): value(value), next(next) {
            }
    };
    std::shared_ptr<Node> m_head;
public:

    LinkedList(): m_head(nullptr) {
    }

    inline bool empty() {
        return m_head.get() == nullptr;
    }

    T& first() {
        if(m_head == nullptr) throw MirageException("Called first on empty list!");
        return m_head->value;
    }

    T& last() {
        if(m_head == nullptr) throw MirageException("Called last on empty list!");
        Node* it = m_head.get();
        while(it->next.get() != nullptr) it = it->next.get();
        return it->value;
    }

    template<typename TransformFunction>
    LinkedList<T> map(TransformFunction transform) {
        LinkedList<T> mapped;
        Node* it = m_head.get();
        while(it != nullptr) {
            mapped.push_back(transform(it->value));
            it = it->next.get();
        }
        return mapped;
    }

    LinkedList<T> rest() {
        LinkedList<T> rest;
        rest.m_head = m_head->next;
        return rest;
    }

    void push_front(T value) {
        auto head = std::make_shared<Node>(value, std::move(m_head));
        m_head = head;
    }

    void push_back(T value) {
        Node* it = m_head.get();
        if(it == nullptr) {
            push_front(value);
            return;
        }
        while(it->next.get() != nullptr) it = it->next.get();
        it->next = std::make_shared<Node>(value, nullptr);
    }

    std::size_t count() {
        std::size_t count = 0;
        Node* it = m_head.get();
        while(it != nullptr) {
            count++;
            it = it->next.get();
        }
        return count;
    }
};

#endif // LINKEDLIST_H
