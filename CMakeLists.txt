cmake_minimum_required (VERSION 3.8)

project(clw-09)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX") # CMake already contains W3 in its flags
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif()

#add_executable(unique_ptr_test unique_ptr/test.cpp)
#add_executable(queue_test queue/test.cpp)
#add_executable(json_test json_value/test.cpp)
#add_executable(lazy_string_test LazyString/test_lazy_string.cpp)
#add_executable(lazy_string_test LazyString/test_shared_buffer.cpp)
#add_executable(lazy_string_test LazyString/test_access_operator.cpp)