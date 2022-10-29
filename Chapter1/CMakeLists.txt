set(CPP_COMPILE_OPTIONS -std=c++20 -Werror -W -Wall -Wextra -Wpedantic)

add_executable(chapter1 src/main.cpp)
target_include_directories(chapter1 PUBLIC inc)
target_compile_options(chapter1 PRIVATE ${CPP_COMPILE_OPTIONS})

add_executable ( test_chapter1 test/main.cpp)
target_include_directories(chapter1 PUBLIC inc)
target_compile_options(chapter1 PRIVATE ${CPP_COMPILE_OPTIONS})