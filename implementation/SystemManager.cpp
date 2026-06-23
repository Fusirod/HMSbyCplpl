#include "SystemManager.h"
#include "Utils.h"
#include <iostream>
#include <cstdlib>

SystemManager::SystemManager(EmployeeManager* empMgr) {
    this->empManager = empMgr;
    this->currentUser = nullptr;
}

SystemManager::~SystemManager() {
    this->currentUser = nullptr;
}

bool SystemManager::login() {
    Utils::clearScreen();
    cout << "===== HE THONG QUAN LY BENH VIEN =====\n";
    cout << "--- DANG NHAP ---\n";
    cout << "Ten dang nhap: ";
    string user = Utils::readString();
    cout << "Mat khau: ";
    string pass = Utils::readString();

    currentUser = empManager->authenticate(user, pass);
    if (currentUser != nullptr) {
        cout << "Dang nhap thanh cong! Xin chao " << currentUser->name << "\n";
        Utils::pauseScreen();
        return true;
    } else {
        cout << "Sai ten dang nhap hoac mat khau!\n";
        Utils::pauseScreen();
        return false;
    }
}

void SystemManager::logout() {
    currentUser = nullptr;
    cout << "Da dang xuat thanh cong!\n";
    Utils::pauseScreen();
}

bool SystemManager::isLoggedIn() {
    return currentUser != nullptr;
}

Employee* SystemManager::getCurrentUser() {
    return currentUser;
}

void SystemManager::changePassword() {
    if (!isLoggedIn()) return;
    Utils::clearScreen();
    cout << "--- THAY DOI MAT KHAU ---\n";
    cout << "Nhap mat khau cu: ";
    string oldPass = Utils::readString();

    if (oldPass == currentUser->password) {
        cout << "Nhap mat khau moi: ";
        string newPass = Utils::readString();
        currentUser->password = newPass;
        cout << "Doi mat khau thanh cong!\n";
    } else {
        cout << "Mat khau cu khong chinh xac!\n";
    }
    Utils::pauseScreen();
}

void SystemManager::changeTheme() {
    Utils::clearScreen();
    cout << "--- THAY DOI GIAO DIEN CONSOLE ---\n";
    cout << "1. Nen den, chu trang (Mac dinh)\n";
    cout << "2. Nen trang, chu den\n";
    cout << "3. Nen xanh duong, chu trang\n";
    cout << "4. Nen den, chu xanh la (Matrix)\n";
    cout << "Chon (1-4): ";
    int choice = Utils::readInt();

    switch (choice) {
#ifdef _WIN32
        case 1: system("color 0F"); break;
        case 2: system("color F0"); break;
        case 3: system("color 1F"); break;
        case 4: system("color 0A"); break;
#endif
        default: cout << "Lua chon khong hop le.\n"; break;
    }
    
    cout << "Da thay doi giao dien!\n";
    Utils::pauseScreen();
}
