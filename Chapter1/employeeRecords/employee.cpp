#include "employee.hpp"

#include <iostream>

constexpr int EmployeeBaseNo = 1000;
namespace Detail {
int employeeNo = EmployeeBaseNo;
int count = 0;
}  // namespace Detail

Employee::Employee(const std::string name, EmploymentLevel level)
    : _employeeNo{Detail::employeeNo++}, _level{level}, _status{EmploymentStatus::Employed}, _name{name} {}

Database::Database() : _employees{} {}
Database::~Database() {}
// void Database::add(Employee &&employee) { _employees.push_back(employee); }
int Database::add(const Employee &employee) {
  _employees.push_back(employee);
  return employee._employeeNo;
}
Employee &Database::get(const int emplNo) { return _employees[emplNo - EmployeeBaseNo]; }

std::vector<Employee> Database::list(EmployeeView selector) {
  std::vector<Employee> selection{};
  bool addThisEmployee = false;
  for (auto &empl : _employees) {
    switch (selector) {
      case EmployeeView::All:
        addThisEmployee = true;
        break;
      case EmployeeView::Ex:
        if (empl._status == EmploymentStatus::Terminated) {
          addThisEmployee = true;
        }
        break;
      case EmployeeView::Present:
        if (empl._status == EmploymentStatus::Employed) {
          addThisEmployee = true;
        }
    }
    if (addThisEmployee) {
      selection.push_back(empl);
    }
    addThisEmployee = false;
  }
  return selection;
}

void Employee::fire() { _status = EmploymentStatus::Terminated; }
void Employee::changeLevel(Employee::LevelChange change) {
  switch (change) {
    case Employee::LevelChange::Promote:
      _level = EmploymentLevel::Master;
      break;
    case Employee::LevelChange::Demote:
      _level = EmploymentLevel::Minion;
  }
}

void Employee::prettyPrint() {
  std::cout << "Employee No: ---- " << _employeeNo << "\n";
  std::cout << "Employee Name: -- " << _name << "\n";
  std::cout << "Employee Status:  ";
  switch (_status) {
    case EmploymentStatus::Employed:
      std::cout << "Currently Employed\n";
      break;
    case EmploymentStatus::Terminated:
      std::cout << "Currently Not Employed\n";
      break;
    default:;
  }
  std::cout << "Employee Level: - ";
  switch (_level) {
    case EmploymentLevel::Minion:
      std::cout << "Mere minion\n";
      break;
    case EmploymentLevel::Master:
      std::cout << "To be obeyed\n";
      break;
    default:;
  }
}

#ifdef WITH_TEST_PROBE
EmploymentStatus Employee::getStatus() { return _status; }
EmploymentLevel Employee::getLevel() { return _level; }
#else
EmploymentStatus Employee::getStatus() { return EmploymentStatus::Undefined; }
EmploymentLevel Employee::getLevel() { return EmploymentLevel::Undefined; }
#endif