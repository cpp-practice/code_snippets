project(simple_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wsign-compare")

include_directories(include)
add_executable(foo example/foo.cpp include/simple_test.h)
