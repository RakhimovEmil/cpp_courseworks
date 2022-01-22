#include "lazy_string.hpp"

#include <cassert>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <string>

static void test_lazy_string() {
    {
        LazyString s1;
        LazyString const &ref = s1;

        assert(s1.getSize() == 0);
        assert(ref.getSize() == 0);
        assert(s1.cStr()[0] == '\0');
        assert(ref.cStr()[0] == '\0');

        assert(s1.useCount() == 1);
    }

    {
        LazyString s1 = "Hello world";
        assert(s1.useCount() == 1);
        LazyString const s2 = s1;
        assert(s1.useCount() == 2);

        assert(s2.getSize() == s1.getSize());
        assert(s1.cStr() == s2.cStr());

        assert(s1.getSize() == sizeof("Hello world") - 1);
        assert(std::strcmp(s1.cStr(), "Hello world") == 0);
    }

    {
        LazyString s1;
        for (size_t i = 0; i < 10; ++i) {
            s1 += "A";
        }

        assert(s1.getSize() == 10);
        assert(std::strcmp(s1.cStr(), "AAAAAAAAAA") == 0);
    }

    {
        LazyString s = "Hello";
        LazyString s_concat = s + " with suffix";
        assert(std::strstr(s_concat.cStr(), s.cStr()) == s_concat.cStr());

        assert(strlen(s.cStr()) + 12 == strlen(s_concat.cStr()));
    }

    {
        std::string str{"Hello, world!"};
        LazyString lazy_str{str.c_str()};

        for (size_t i = 0; i < str.size(); ++i) {
            assert(str[i] == lazy_str.at(i));
        }
    }

    {
        LazyString s = "Hello";
        assert(s.at(1) == 'e');

        bool caught = false;
        try {
            (void) s.at(10);
        } catch (const std::out_of_range &e) {
            caught = true;
        } catch (...) {
            std::cout << "expected std::out_of_range exception!" << std::endl;
            assert(false);
        }

        if (!caught) {
            std::cout << "expected exception!" << std::endl;
        }
        assert(caught);
    }
}

int main() {
    test_lazy_string();
}