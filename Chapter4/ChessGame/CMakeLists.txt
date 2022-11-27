set(CPP_COMPILE_OPTIONS -std=c++20 -Werror -W -Wall -Wextra -Wpedantic)
set(CPP_TEST_OPTIONS -std=c++20 -W -Wall -Wextra -Wpedantic)

add_executable(chessGame src/main.cpp src/chessGame.cpp)
target_include_directories(chessGame PUBLIC inc)
target_compile_options(chessGame PRIVATE ${CPP_COMPILE_OPTIONS})# -x c++-system-header)

add_executable ( test_chessGame test/test_chessGame.cpp src/chessGame.cpp)
target_include_directories(test_chessGame PUBLIC inc)
target_compile_options(test_chessGame PRIVATE ${CPP_TEST_OPTIONS})