#pragma once
#include <iostream>


template <class T>
class MyForwardList {
public:
    MyForwardList() = default;


    ~MyForwardList() {
        clearDatas();
    }


    MyForwardList(const MyForwardList& other) {
        m_head = nullptr;
        m_size = 0;
        Node* oCurrent = other.m_head;

        while (oCurrent != nullptr) {
            Node* newNode = new Node(oCurrent->value);

            if (m_head == nullptr) {
                m_head = newNode;
                m_tail = m_head;
            } else {
                m_tail->next = newNode;
                m_tail = newNode;
            }

            oCurrent = oCurrent->next;
            ++m_size;
        }
    }


    MyForwardList(const MyForwardList&& other) 
        : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size)
    {
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }


    MyForwardList& operator=(const MyForwardList& other) {
        if (this == &other) {
            return *this;
        }

        clearDatas();

        Node* oCurrent = other.m_head;

        while (oCurrent != nullptr) {
            Node* newNode = new Node(oCurrent->value);

            if (m_head == nullptr) {
                m_head = newNode;
                m_tail = m_head;
            }
            else {
                m_tail->next = newNode;
                m_tail = newNode;
            }

            oCurrent = oCurrent->next;
        }
        m_size = other.m_size;

        return *this;
    }


    MyForwardList& operator=(const MyForwardList&& other) {
        if (this == &other) {
            return *this;
        }

        clearDatas();

        m_head = std::move(other.m_head);
        m_tail = std::move(other.m_tail);
        m_size = other.m_size;
        other.m_size = 0;

        return *this;
    }


    MyForwardList(const std::initializer_list<T> list) {
        for (const auto& el : list) {
            Node* newNode = new Node(el);

            if (m_head == nullptr) {
                m_head = newNode;
                m_tail = m_head;
            } else {
                m_tail->next = newNode;
                m_tail = newNode;
            }

            ++m_size;
        }
    }


    size_t size() {
        return m_size;
    }


    void insert(const T& value) {
        Node* newNode = new Node(value);

        if (m_head == nullptr) {
            m_head = newNode;
            m_tail = m_head;
        } else {
            m_tail->next = newNode;
            m_tail = newNode;
        }

        ++m_size;
    }


    void remove(const T& value) {
        while (m_head != nullptr && m_head->value == value) {
            Node* next = m_head->next;

            delete m_head;
            m_head = next;

            --m_size;
        }

        if (m_head == nullptr) {
            m_tail = nullptr;

            return;
        }

        Node* prev = m_head;
        Node* current = m_head->next;

        while (current != nullptr) {
            if (current->value == value) {
                prev->next = current->next;

                delete current;
                current = prev->next;

                --m_size;

                if (current == m_tail) {
                    m_tail = prev;
                }
            } else {
                current = current->next;
            }
        }
    }


    T* find(const T& value) const {
        Node* current = m_head;

        while (current != nullptr) {
            if (current->value == value) {
                return &current->value;
            }
        }

        return nullptr;
    }


    bool operator==(const MyForwardList& other) const
    {
        if (m_size != other.m_size) {
            return false;
        }

        Node* current  = m_head;
        Node* oCurrent = other.m_head;

        while (current != nullptr) {
            if (current->value != oCurrent->value) {
                return false;
            }

            current = current->next;
            oCurrent = oCurrent->next;
        }

        return true;
    }



private:
    struct Node {
        T value;
        Node* next;

        Node(const T& value) 
            : value(value), next(nullptr) 
        {}
    };

    Node* m_head = nullptr;
    Node* m_tail = nullptr;
    size_t m_size = 0;


    void clearDatas() {
        while (m_head != nullptr) {
            Node* next = m_head->next;

            delete m_head;
            m_head = next;
        }

        m_size = 0;
    };
};