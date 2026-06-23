#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "EmployeeManager.h"
#include <string>

using namespace std;

struct SystemManager {
private:
    Employee* currentUser;
    EmployeeManager* empManager;

public:
    SystemManager(EmployeeManager* empMgr);
    ~SystemManager();

    bool login();
    void logout();
    bool isLoggedIn();
    Employee* getCurrentUser();

    void changePassword();
    void changeTheme(); // Thay doi mau sac console (Window)
};

#endif // SYSTEM_MANAGER_H
