#ifndef EMPLOYEE_MANAGER_H
#define EMPLOYEE_MANAGER_H

#include "models.h"
#include <vector>
#include <string>

using namespace std;

struct EmployeeManager {
private:
    vector<Employee> employees;
    string filename;

    void loadFromFile();
    void saveToFile();

public:
    EmployeeManager();
    ~EmployeeManager();

    void addEmployee();
    void editEmployee();
    void deleteEmployee();
    void searchEmployee();
    void displayAllEmployees();
    
    Employee* authenticate(const string& username, const string& password);
    Employee* getEmployeeById(const string& id);
    bool employeeExists(const string& id);
};

#endif // EMPLOYEE_MANAGER_H
