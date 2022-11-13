#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>

#include "doctest.h"
#include "employee.hpp"

Database database{};

TEST_CASE("Database") {
  /*    Any code here is part of the Suite and will be executed before each SUBCASE!!!   */
  SUBCASE("create") {
    Database *dbPtr = &database;
    CHECK_NE(dbPtr, nullptr);
  }
  SUBCASE("addGlobRef") {
    // Database database{};
    database.add(Employee{"Mats", EmploymentLevel::Minion});
    database.add(Employee{std::string{"Lars"}, EmploymentLevel::Master});
  }
  SUBCASE("add") {
    Employee mats{"Mats", EmploymentLevel::Master};
    database.add(mats);
    Employee lars{std::string{"Lars"}, EmploymentLevel::Minion};
    database.add(lars);
  }
  SUBCASE("fire") {
    int emplNo = database.add(Employee{"Mats", EmploymentLevel::Minion});
    CHECK_EQ(emplNo, 1004);
    Employee &empl = database.get(emplNo);
    CHECK_EQ(empl.getStatus(), EmploymentStatus::Employed);
    CHECK_EQ(empl._status, EmploymentStatus::Employed);
    empl.fire();
    CHECK_EQ(empl.getStatus(), EmploymentStatus::Terminated);
  }
  SUBCASE("promote") {
    int emplNo = database.add(Employee{"Mats", EmploymentLevel::Minion});
    CHECK_EQ(emplNo, 1005);
    Employee &empl = database.get(emplNo);
    CHECK_EQ(empl.getLevel(), EmploymentLevel::Minion);
    empl.changeLevel(Employee::LevelChange::Promote);
    CHECK_EQ(empl.getLevel(), EmploymentLevel::Master);
  }
  SUBCASE("demote") {
    int emplNo = database.add(Employee{"Mats", EmploymentLevel::Master});
    CHECK_EQ(emplNo, 1006);
    Employee &empl = database.get(emplNo);
    CHECK_EQ(empl.getLevel(), EmploymentLevel::Master);
    empl.changeLevel(Employee::LevelChange::Demote);
    CHECK_EQ(empl.getLevel(), EmploymentLevel::Minion);
  }
  SUBCASE("view all") {
    auto selection = database.list(EmployeeView::All);
    CHECK_EQ(selection[0]._employeeNo, 1000);
    CHECK_EQ(selection[1]._employeeNo, 1001);
    CHECK_EQ(selection[2]._employeeNo, 1002);
    CHECK_EQ(selection[3]._employeeNo, 1003);
    CHECK_EQ(selection[4]._employeeNo, 1004);
    CHECK_EQ(selection[5]._employeeNo, 1005);
    CHECK_EQ(selection[6]._employeeNo, 1006);
  }
  SUBCASE("view ex") {
    auto selection = database.list(EmployeeView::Ex);
    CHECK_EQ(selection[0]._employeeNo, 1004);
    selection[0].prettyPrint();
  }
  SUBCASE("view present") {
    auto selection = database.list(EmployeeView::Present);
    CHECK_EQ(selection[0]._employeeNo, 1000);
    CHECK_EQ(selection[1]._employeeNo, 1001);
    CHECK_EQ(selection[2]._employeeNo, 1002);
    CHECK_EQ(selection[3]._employeeNo, 1003);
    CHECK_EQ(selection[4]._employeeNo, 1005);
    CHECK_EQ(selection[5]._employeeNo, 1006);
  }
}

TEST_CASE("case") {
  SUBCASE("sub") {}
}