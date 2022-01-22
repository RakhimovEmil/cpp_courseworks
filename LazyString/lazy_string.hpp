#pragma once
#include "shared_buffer.hpp"

class CharWrapper;

class LazyString {
    SharedBuffer buf;

public:
    LazyString();
    LazyString(const char*);
    LazyString(const SharedBuffer&);
    LazyString(const LazyString&);

    LazyString& operator=(const LazyString&);

    std::size_t getSize() const;
    const char* cStr() const;
    char* cStr();
    std::size_t useCount() const;

    char at(std::size_t);
    CharWrapper operator[](std::size_t);

    friend bool operator==(const LazyString&, const LazyString&);
    LazyString& operator+=(const LazyString&);
};


bool operator==(const LazyString&, const LazyString&);
LazyString operator+(LazyString&, LazyString);

class CharWrapper {
    SharedBuffer cur_shared_buf;
    std::size_t ind {};
    char* arr = nullptr;

public:
    CharWrapper(SharedBuffer*, std::size_t, char*);

    CharWrapper& operator=(char);

    friend bool operator==(const CharWrapper&, const CharWrapper&);
    friend bool operator!=(const CharWrapper&, const CharWrapper&);

    friend bool operator<(const CharWrapper&, const CharWrapper&);
    friend bool operator<=(const CharWrapper&, const CharWrapper&);

    friend bool operator>(const CharWrapper&, const CharWrapper&);
    friend bool operator>=(const CharWrapper&, const CharWrapper&);

    CharWrapper& operator++();
    CharWrapper  operator++(int);
};

bool operator==(const CharWrapper&, char);
bool operator==(char, const CharWrapper&);
bool operator==(const CharWrapper&, const CharWrapper&);
bool operator!=(const CharWrapper&, const CharWrapper&);