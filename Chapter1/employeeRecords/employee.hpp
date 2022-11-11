#include <string>
#include <vector>

class Employee {
 public:
  enum EmploymentStatus { Employed, Terminated };
  enum EmploymentLevel { Minion, Master };
  Employee(std::string name,
           EmploymentLevel
               level);  // : _employeeNo{Detail::employeeNo++}, _status{EmploymentStatus::Employed}, _name{name} {}

 private:
  int _employeeNo;
  EmploymentLevel _level;
  EmploymentStatus _status;
  std::vector<std::string> _name;
};

class Database {
 public:
  // void add(Employee &&employee);
  void add(Employee employee);

 private:
  std::vector<Employee> _employees;
};