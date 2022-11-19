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

namespace HR {
class Employee;
}
class Database {
 public:
  Database();
  ~Database();
  /** Adds the employee to the database
   * @Param an employee reference
   * @return employee number
   */
  int add(const HR::Employee &employee);

  /** Gets the employee from the database
   * @Param an employee number
   * @return reference to the employee
   */
  HR::Employee &get(const int emplNo);

  /** Collect requested employees
   * @Param selection
   * @Return vector of selected employees
   */
  std::vector<HR::Employee> list(EmployeeView selector);

 private:
  std::vector<HR::Employee> _employees;
};

/**Exercise 1-1:
 * Modify the Employee structure from the beginning of this chapter by putting it
 * in a namespace called HR. What modifications do you have to make to the code in main() to
 * work with this new implementation? Additionally, modify the code to use C++20 designated
 * initializers.
 * Ans -> Add HR:: in front of every Employee, add using in test suite */
namespace HR {
class Employee {
 public:
  enum LevelChange { Promote, Demote };

  Employee(std::string name, EmploymentLevel level);
  friend int Database::add(const HR::Employee &employee);
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
}  // namespace HR