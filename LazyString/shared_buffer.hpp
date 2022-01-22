#pragma once
#include <cstddef>

class SharedBuffer {
    char* arr = nullptr;
    std::size_t size_of_arr{};
    std::size_t* count_of_users = nullptr;

public:
    SharedBuffer();
    explicit SharedBuffer(std::size_t);
    SharedBuffer(const SharedBuffer&);

    SharedBuffer& operator=(const SharedBuffer&);

    std::size_t getSize() const;
    char* getData();
    const char* getData() const;
    const std::size_t& useCount() const;
    std::size_t& useCount();

    ~SharedBuffer();
};