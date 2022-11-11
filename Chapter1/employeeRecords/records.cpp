/*
 * The feature set for this program includes the following abilities:
 * ➤➤ To add and fire employees
 * ➤➤ To promote and demote employees
 * ➤➤ To view all employees, past and present
 * ➤➤ To view all current employees
 * ➤➤ To view all former employees */
#include <iostream>

#include "employee.hpp"

int main() {
  int selection;

  std::cout << "Please select:\n";
  std::cout << "1. Add new employee\n";
  std::cout << "2. Fire existing employee\n";
  std::cout << "3. Promote an employee\n";
  std::cout << "4. Demote an employee\n";
  std::cout << "6. View all employee past and present\n";
  std::cout << "7. View all current employees\n";
  std::cout << "8. View all former employees\n";

  std::cin >> selection;
}