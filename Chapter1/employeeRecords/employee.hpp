#include <string>
#include <vector>

enum class EmploymentStatus {
  Undefined,
  Employed,
  Terminated,
};
enum class EmploymentLevel {
  Undefined,
  Minion,
  Master,
};
enum class EmployeeView {
  All,
  Present,
  Ex,
};

class Employee;
class Database {
 public:
  Database();
  ~Database();
  /** Adds the employee to the database
   * @Param an employee reference
   * @return employee number
   */
  int add(const Employee &employee);

  /** Gets the employee from the database
   * @Param an employee number
   * @return reference to the employee
   */
  Employee &get(const int emplNo);

  /** Collect requested employees
   * @Param selection
   * @Return vector of selected employees
   */
  std::vector<Employee> list(EmployeeView selector);

 private:
  std::vector<Employee> _employees;
};

class Employee {
 public:
  enum LevelChange { Promote, Demote };

  Employee(std::string name, EmploymentLevel level);
  friend int Database::add(const Employee &employee);
  void fire();
  EmploymentStatus getStatus();
  EmploymentLevel getLevel();
  void changeLevel(Employee::LevelChange change);
  void prettyPrint();

#ifndef WITH_TEST_PROBE
 private:
#endif
  int _employeeNo;
  EmploymentLevel _level;
  EmploymentStatus _status;
  std::string _name;
};
