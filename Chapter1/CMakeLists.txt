set(CPP_COMPILE_OPTIONS -std=c++20 -Werror -W -Wall -Wextra -Wpedantic)
set(CPP_TEST_OPTIONS -std=c++20 -W -Wall -Wextra -Wpedantic)

add_executable(chapter1 src/main.cpp src/crashCourse.cpp)
target_include_directories(chapter1 PUBLIC inc)
target_compile_options(chapter1 PRIVATE -fmodules-ts ${CPP_COMPILE_OPTIONS})# -x c++-system-header)

add_executable ( test_chapter1 test/main.cpp src/crashCourse.cpp)
target_include_directories(test_chapter1 PUBLIC inc)
target_compile_options(test_chapter1 PRIVATE ${CPP_TEST_OPTIONS})