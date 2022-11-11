#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>

#include "doctest.h"
#include "employee.hpp"

using Level = Employee::EmploymentLevel;
using Status = Employee::EmploymentStatus;
TEST_CASE("Database") {
  Database database{};
  SUBCASE("create") {
    Database *dbPtr = &database;
    CHECK_NE(dbPtr, nullptr);
  }
  SUBCASE("addGlobRef") {
    database.add(Employee{"Mats", Level{Level::Minion}});
    database.add(Employee{std::string{"Lars"}, Level{Level::Master}});
  }
  SUBCASE("add") {
    Employee mats{"Mats", Level{Level::Master}};
    database.add(mats);
    Employee lars{std::string{"Lars"}, Level{Level::Minion}};
    database.add(lars);
  }
}

TEST_CASE("case") {
  SUBCASE("sub") {}
}