# An Employee Records System
# A program to manage a company’s employee records needs to be flexible and have useful features.
# The feature set for this program includes the following abilities:
# ➤➤ To add and fire employees
# ➤➤ To promote and demote employees
# ➤➤ To view all employees, past and present
# ➤➤ To view all current employees
# ➤➤ To view all former employees
# The design for this program divides the code into three parts. The Employee class encapsulates the
# information describing a single employee. The Database class manages all the employees of the com-
# pany. Finally, a separate UserInterface file provides the interactivity of the program.

set(CPP_COMPILE_OPTIONS -std=c++20 -Werror -W -Wall -Wextra -Wpedantic)
set(CPP_TEST_OPTIONS -g -O0 -std=c++20 -W -Wall -Wextra -Wpedantic)

add_executable(employeeRecords records.cpp employee.cpp)
target_compile_options(employeeRecords PRIVATE -fmodules-ts ${CPP_COMPILE_OPTIONS})

add_executable(test_employeeRecords test_employee.cpp employee.cpp)
target_compile_options(test_employeeRecords PRIVATE ${CPP_TEST_OPTIONS})
target_compile_definitions(test_employeeRecords PRIVATE WITH_TEST_PROBE=1)