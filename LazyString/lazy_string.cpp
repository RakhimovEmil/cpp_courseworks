#include "lazy_string.hpp"
#include <cstring>
#include <stdexcept>

LazyString::LazyString(){}

LazyString::LazyString(const char* x) : buf(std::strlen(x)){
    std::strcpy(this->buf.getData(), x);
}

LazyString::LazyString(const SharedBuffer& x) : buf(x) {}

LazyString::LazyString(const LazyString& x) : buf(x.buf){}

LazyString& LazyString::operator=(const LazyString& copy) {
    this->buf = copy.buf;
    return *this;
}

std::size_t LazyString::getSize() const {
    return this->buf.getSize();
}

const char* LazyString::cStr() const {
    return this->buf.getData();
}

char* LazyString::cStr() {
    return this->buf.getData();
}

std::size_t LazyString::useCount() const {
    return this->buf.useCount();
}

char LazyString::at(std::size_t ind) {
    if (ind >= this->buf.getSize()) {
        throw std::out_of_range("your index must be in the size range");
    }

    return this->cStr()[ind];
}

CharWrapper LazyString::operator[](std::size_t ind) {
    return CharWrapper(&this->buf, ind, this->cStr());
}

LazyString& LazyString::operator+=(const LazyString& b) {
    std::size_t a_sz = this->getSize();
    std::size_t b_sz = b.getSize();

    char* copy = new char[a_sz + 1];
    std::strcpy(copy, this->cStr());

    if (this->useCount() != 1) {
        this->buf.useCount()--;
    } else {
        buf.~SharedBuffer();
    }

    this->buf = SharedBuffer(a_sz + b_sz);
    std::strcpy(this->buf.getData(), copy);
    std::strcpy(this->buf.getData() + a_sz, b.cStr());

    delete [] copy;

    return *this;
}

bool operator==(const LazyString& a, const LazyString& b) {
    return std::strcmp(a.cStr(), b.cStr()) == 0;
}

LazyString operator+(LazyString& a, LazyString b) {
    LazyString c(SharedBuffer(a.getSize() + b.getSize()));
    std::strcat(c.cStr(), a.cStr());
    std::strcat(c.cStr(), b.cStr());

    return c;
}

CharWrapper::CharWrapper(SharedBuffer* lz, std::size_t ind, char* arr) : cur_shared_buf(*lz),
                                                                         ind(ind),
                                                                         arr(arr) {}

//bool operator==(const CharWrapper& a, char b) {
//    return a.cur_shared_buf.getData()[a.ind] == b;
//}
//
//bool operator==(char b, const CharWrapper& a) {
//    return a == b;
//}

bool operator==(const CharWrapper& a, const CharWrapper& b) {
    return a.cur_shared_buf.getData()[a.ind] == b.cur_shared_buf.getData()[b.ind];
}

bool operator!=(const CharWrapper& a, const CharWrapper& b) {
    return !(a == b);
}


bool operator<(const CharWrapper& a, const CharWrapper& b) {
    return a.cur_shared_buf.getData()[a.ind] < b.cur_shared_buf.getData()[b.ind];
}

bool operator<=(const CharWrapper& a, const CharWrapper& b) {
    return a.cur_shared_buf.getData()[a.ind] <= b.cur_shared_buf.getData()[b.ind];
}

bool operator>(const CharWrapper& a, const CharWrapper& b) {
    return !(a <= b);
}

bool operator>=(const CharWrapper& a, const CharWrapper& b) {
    return !(a < b);
}

CharWrapper& CharWrapper::operator=(char a) {
    if (this->cur_shared_buf.useCount() != 1) {
        this->cur_shared_buf.useCount()--;

        std::size_t cur_size = this->cur_shared_buf.getSize();
        char* copy = new char[cur_size + 1]{};
        std::strcpy(copy,  this->cur_shared_buf.getData());

        this->cur_shared_buf = SharedBuffer(cur_size);
        std::strcpy(this->cur_shared_buf.getData(), copy);
        delete [] copy;
    }

    this->cur_shared_buf.getData()[this->ind] = a;
    this->arr[this->ind] = a;
    return *this;
}

CharWrapper& CharWrapper::operator++() {
    if (this->cur_shared_buf.useCount() != 1) {
        this->cur_shared_buf.useCount()--;

        std::size_t cur_size = this->cur_shared_buf.getSize();
        char* copy = new char[cur_size + 1]{};
        std::strcpy(copy,  this->cur_shared_buf.getData());

        this->cur_shared_buf = SharedBuffer(cur_size);
        std::strcpy(this->cur_shared_buf.getData(), copy);

        delete [] copy;
    }

    this->cur_shared_buf.getData()[this->ind]++;
    return *this;
}

CharWrapper CharWrapper::operator++(int) {
    if (this->cur_shared_buf.useCount() != 1) {
        this->cur_shared_buf.useCount()--;

        std::size_t cur_size = this->cur_shared_buf.getSize();
        char* copy = new char[cur_size + 1]{};
        std::strcpy(copy,  this->cur_shared_buf.getData());

        this->cur_shared_buf = SharedBuffer(cur_size);
        std::strcpy(this->cur_shared_buf.getData(), copy);

        delete [] copy;
    }

    this->cur_shared_buf.getData()[this->ind]++;
    return *this;
}



