#pragma once

#include <cstddef>
#include <utility>

namespace cls_08 {
    template<typename T>
    class list {
    public:
        list() : head(nullptr), tail(nullptr), count(0) {}

        list(const list& x) : head(nullptr), tail(nullptr), count(0) {
            node* start = x.head;
            while (start != nullptr) {
                this->push(start->value);
                start = start->prev;
            }
        }

        list(list&& x) : head(x.head), tail(x.tail), count(x.count) {
            x.head = x.tail = nullptr;
            x.count = 0;
        }

        list& operator=(const list& x) {
            this->~list();
            node* start = x.head;
            while (start != nullptr) {
                this->push(start->value);
                start = start->prev;
            }
            return *this;
        }

        list& operator=(list&& x) {
            this->~list();
            head  = x.head;
            tail  = x.tail;
            count = x.count;
            x.head = x.tail = nullptr;
            x.count = 0;
            return *this;
        }

        void push(const T& x) {
            if (!count) {
                head = new node;
                head->value = x;
                head->prev = nullptr;
                tail = head;
                ++count;
            } else {
                tail->prev = new node;
                tail = tail->prev;
                tail->value = x;
                tail->prev = nullptr;
                ++count;
            }
        }

        void push(T&& x) {
            if (!count) {
                head = new node;
                head->value = std::move(x);
                head->prev = nullptr;
                tail = head;
                ++count;
            } else {
                tail->prev = new node;
                tail = tail->prev;
                tail->value = std::move(x);
                tail->prev = nullptr;
                ++count;
            }
        }

        void pop() {
            if (count) {
                node* cur = head;
                head = head->prev;
                delete cur;
                --count;
            }

            if (head == nullptr) {
                tail = nullptr;
            }
        }

        T& front()       { return head->value; }
        T& front() const { return head->value; }

        std::size_t size() const { return count; }

        ~list() {
            while (count) {
                pop();
            }
        }
    private:
        struct node {
            T value;
            node *prev;
        };

        node* head;
        node* tail;
        std::size_t count;
    };

    template<class T>
    class queue {
    public:
        queue() = default;
        queue(const queue&) = default;
        queue(queue&&) = default;

        queue& operator=(const queue&) = default;
        queue& operator=(queue&&)      = default;

        T& front()       { return q.front(); }
        T& front() const { return q.front(); }

        void push(const T& x) { q.push(x); }
        void push(T&& x)      { q.push(std::move(x)); }

        void pop() { q.pop(); }

        std::size_t size() const { return q.size(); }
    private:
        list<T> q;
    };
}