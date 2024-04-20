#pragma once



template <class T>
class MyForwardList {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& data)
            : data(data), next(nullptr)
        {}
    };

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    size_t size_ = 0;


    void clearDatas() {
        while (head_ != nullptr) {
            auto next = head_->next;

            delete head_;
            head_ = next;
        }

        size_ = 0;
    };


public:
    MyForwardList() = default;

    ~MyForwardList() {
        clearDatas();
    }

    MyForwardList(const MyForwardList& other) {
        Node* oCurrent = other.head_;
        
        while (oCurrent != nullptr) {
            push_back(oCurrent->data);

            oCurrent = oCurrent->next;
        }
    }

    MyForwardList(MyForwardList&& other) noexcept
        : head_(other.head_), 
        tail_(other.tail_), 
        size_(other.size_)
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    MyForwardList& operator=(const MyForwardList& other) {
        if (this == &other) {
            return *this;
        }

        clearDatas();

        Node* oCurrent = other.head_;

        while (oCurrent != nullptr) {
            Node* newNode = new Node(oCurrent->data);

            if (head_ == nullptr) {
                head_ = newNode;
                tail_ = head_;
            }
            else {
                tail_->next = newNode;
                tail_ = tail_->next;
            }

            oCurrent = oCurrent->next;
        }
        size_ = other.size_;

        return *this;
    }

    MyForwardList& operator=(MyForwardList&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        clearDatas(); 

        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;

        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;

        return *this;
    }

    MyForwardList(const std::initializer_list<T> list) {
        for (const auto& el : list) {
            push_back(el);
        }
    }

    size_t size() {
        return size_;
    }

    bool is_empty() const {
        return size_ == 0;
    }

    void push_front(const T& data) {
        Node* newNode = new Node(data);

        if (head_ == nullptr) {
            head_ = newNode;
        } else {
            newNode->next = head_;
            head_ = newNode;
        }

        ++size_;
    }

    void push_back(const T& data) {
        Node* newNode = new Node(data);

        if (head_ == nullptr) {
            head_ = newNode;
            tail_ = head_;
        } else {
            tail_->next = newNode;
            tail_ = tail_->next;
        }

        ++size_;
    }

    void remove(const T& data) {
        while (head_ != nullptr && head_->data == data) {
            Node* next = head_->next;

            delete head_;
            head_ = next;

            --size_;
        }

        if (head_ == nullptr) {
            tail_ = nullptr;

            return;
        }

        Node* prev = head_;
        Node* current = head_->next;

        while (current != nullptr) {
            if (current->data == data) {
                if (current == tail_) {
                    tail_ = prev;
                }

                prev->next = current->next;

                delete current;
                current = prev->next;

                --size_;
            } else {
                current = current->next;
            }
        }
    }

    class Iterator {
    public:
        Iterator() : node(nullptr) {}
        Iterator(Node* node) : node(node) {}


        T& operator*() {
            return node->data;
        }


        Iterator& operator++() {
            node = node->next;

            return *this;
        }


        bool operator!=(const Iterator& other) const {
            if (node == nullptr && other.node == nullptr) {
                return false;
            }
            if (node == nullptr || other.node == nullptr) {
                return true;
            }

            return node->data != other.node->data;
        }


        bool is_null() const {
            return node == nullptr;
        }


    private:
        Node* node;

        void assertNode() const {
            if (node == nullptr) {
                throw std::logic_error("Node is nullptr");
            }
        }
    };

    Iterator begin() const {
        return Iterator(head_);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    Iterator find(const T& data) const {
        Node* current = head_;

        while (current != nullptr) {
            if (current->data == data) {
                return Iterator(current);
            }

            current = current->next;
        }

        return Iterator(nullptr);
    }

    bool operator==(const MyForwardList& other) const
    {
        if (size_ != other.size_) {
            return false;
        }

        Node* current  = head_;
        Node* oCurrent = other.head_;

        while (current != nullptr) {
            if (current->data != oCurrent->data) {
                return false;
            }

            current = current->next;
            oCurrent = oCurrent->next;
        }

        return true;
    }
};