#ifndef EMPLOYEE_MANAGER_H
#define EMPLOYEE_MANAGER_H

#include "Utils.h"
#include <string>

using namespace std;

class EmployeeManager {
private:
    int employeeCount;
    char ids[Utils::MAX_RECORDS][Utils::MAX_ID_LENGTH];
    char names[Utils::MAX_RECORDS][Utils::MAX_TEXT_LENGTH];
    char roles[Utils::MAX_RECORDS][Utils::MAX_TEXT_LENGTH];
    char phones[Utils::MAX_RECORDS][Utils::MAX_TEXT_LENGTH];
    char departments[Utils::MAX_RECORDS][Utils::MAX_TEXT_LENGTH];
    char usernames[Utils::MAX_RECORDS][Utils::MAX_TEXT_LENGTH];
    char passwords[Utils::MAX_RECORDS][Utils::MAX_TEXT_LENGTH];
    string filename;

    void loadFromFile();
    void saveToFile();
    int findIndexById(const string& id);
    void removeAt(int index);

public:
    EmployeeManager();
    ~EmployeeManager();

    void addEmployee();
    void editEmployee();
    void deleteEmployee();
    void searchEmployee();
    void displayAllEmployees();
    
    int authenticate(const string& username, const string& password);
    int getEmployeeIndexById(const string& id);
    bool employeeExists(const string& id);
    const char* getEmployeeName(int index);
    const char* getEmployeePassword(int index);
    void updateEmployeePassword(int index, const string& newPassword);
};

#endif // EMPLOYEE_MANAGER_H
