#include "employee.hpp"

namespace Detail {
int employeeNo = 1000;
}

Employee::Employee(const std::string name, EmploymentLevel level)
    : _employeeNo{Detail::employeeNo++}, _level{level}, _status{EmploymentStatus::Employed}, _name{name} {}

// void Database::add(Employee &&employee) { _employees.push_back(employee); }
void Database::add(Employee employee) { _employees.push_back(employee); }
