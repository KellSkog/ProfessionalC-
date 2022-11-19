#include "employee.hpp"

#include <iostream>

constexpr int EmployeeBaseNo = 1000;
namespace Detail {
int employeeNo = EmployeeBaseNo;
int count = 0;
}  // namespace Detail

HR::Employee::Employee(const std::string name, EmploymentLevel level)
    : _employeeNo{Detail::employeeNo++}, _level{level}, _status{EmploymentStatus::Employed}, _name{name} {}

Database::Database() : _employees{} {}
Database::~Database() {}
// void Database::add(Employee &&employee) { _employees.push_back(employee); }
int Database::add(const HR::Employee &employee) {
  _employees.push_back(employee);
  return employee._employeeNo;
}
HR::Employee &Database::get(const int emplNo) { return _employees[emplNo - EmployeeBaseNo]; }

std::vector<HR::Employee> Database::list(EmployeeView selector) {
  std::vector<HR::Employee> selection{};
  bool addThisEmployee = false;
  for (auto &empl : _employees) {
    switch (selector) {
      case EmployeeView::All:
        addThisEmployee = true;
        break;
      case EmployeeView::Ex:
        if (empl.getStatus() == EmploymentStatus::Terminated) {
          addThisEmployee = true;
        }
        break;
      case EmployeeView::Present:
        if (empl.getStatus() == EmploymentStatus::Employed) {
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

void HR::Employee::fire() { _status = EmploymentStatus::Terminated; }
void HR::Employee::changeLevel(Employee::LevelChange change) {
  switch (change) {
    case Employee::LevelChange::Promote:
      _level = EmploymentLevel::Master;
      break;
    case Employee::LevelChange::Demote:
      _level = EmploymentLevel::Minion;
  }
}

void HR::Employee::prettyPrint() {
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
EmploymentStatus HR::Employee::getStatus() { return _status; }
EmploymentLevel HR::Employee::getLevel() { return _level; }
#else
EmploymentStatus HR::Employee::getStatus() { return EmploymentStatus::Undefined; }
EmploymentLevel HR::Employee::getLevel() { return EmploymentLevel::Undefined; }
#endif