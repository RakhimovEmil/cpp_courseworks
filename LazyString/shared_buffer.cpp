#include "shared_buffer.hpp"
#include <cstring>
#include <cstddef>

SharedBuffer::SharedBuffer(std::size_t sz) : arr(new char[sz + 1]{}), // один символ для '\0'
                                             size_of_arr(sz),
                                             count_of_users(new std::size_t{1}) {}

SharedBuffer::SharedBuffer() : arr(new char[1]{}),
                               size_of_arr(0),
                               count_of_users(new std::size_t{1}) {}

SharedBuffer::SharedBuffer(const SharedBuffer& copy) : arr(copy.arr),
                                                       size_of_arr(copy.size_of_arr),
                                                       count_of_users(copy.count_of_users) {
    (*this->count_of_users)++;
}

SharedBuffer& SharedBuffer::operator=(const SharedBuffer& copy) {
    if (this->arr == copy.arr) {
        return *this;
    }

    if (this->count_of_users != nullptr && *this->count_of_users == 1) {
        delete [] arr;
        delete count_of_users;
    } else if (this->count_of_users != nullptr) {
        (*this->count_of_users)--;
    }

    this->arr = copy.arr;
    this->size_of_arr = copy.size_of_arr;
    this->count_of_users = copy.count_of_users;

    (*this->count_of_users)++;

    return *this;
}

std::size_t SharedBuffer::getSize() const {
    return this->size_of_arr;
}

char* SharedBuffer::getData() {
    return this->arr;
}

const char* SharedBuffer::getData() const {
    return static_cast<const char*>(this->arr);
}

const std::size_t& SharedBuffer::useCount() const {
    return *this->count_of_users;
}

std::size_t& SharedBuffer::useCount() {
    return *this->count_of_users;
}

SharedBuffer::~SharedBuffer() {
    (*this->count_of_users)--;

    if (*this->count_of_users == 0) {
        delete [] this->arr;
        delete this->count_of_users;
        this->count_of_users = nullptr;
    }
}

