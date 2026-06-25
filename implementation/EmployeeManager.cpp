#include "EmployeeManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

EmployeeManager::EmployeeManager() {
    filename = "data/employees.txt";
    employeeCount = 0;
    loadFromFile();
    
    if (employeeCount == 0) {
        Utils::copyText(ids[0], "AD001", Utils::MAX_ID_LENGTH);
        Utils::copyText(names[0], "System Admin", Utils::MAX_TEXT_LENGTH);
        Utils::copyText(roles[0], "Admin", Utils::MAX_TEXT_LENGTH);
        Utils::copyText(phones[0], "0000000000", Utils::MAX_TEXT_LENGTH);
        Utils::copyText(departments[0], "IT", Utils::MAX_TEXT_LENGTH);
        Utils::copyText(usernames[0], "admin", Utils::MAX_TEXT_LENGTH);
        Utils::copyText(passwords[0], "admin", Utils::MAX_TEXT_LENGTH);
        employeeCount = 1;
        saveToFile();
    }
}

EmployeeManager::~EmployeeManager() {
    saveToFile();
}

int EmployeeManager::findIndexById(const string& id) {
    for (int i = 0; i < employeeCount; ++i) {
        if (id == ids[i]) return i;
    }
    return -1;
}

void EmployeeManager::removeAt(int index) {
    for (int i = index; i < employeeCount - 1; ++i) {
        strcpy(ids[i], ids[i + 1]);
        strcpy(names[i], names[i + 1]);
        strcpy(roles[i], roles[i + 1]);
        strcpy(phones[i], phones[i + 1]);
        strcpy(departments[i], departments[i + 1]);
        strcpy(usernames[i], usernames[i + 1]);
        strcpy(passwords[i], passwords[i + 1]);
    }
    --employeeCount;
}

void EmployeeManager::loadFromFile() {
    employeeCount = 0;
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (employeeCount < Utils::MAX_RECORDS && getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, name, role, phone, dept, user, pass;
        
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, role, '|');
        getline(ss, phone, '|');
        getline(ss, dept, '|');
        getline(ss, user, '|');
        getline(ss, pass, '|');

        Utils::copyText(ids[employeeCount], id, Utils::MAX_ID_LENGTH);
        Utils::copyText(names[employeeCount], name, Utils::MAX_TEXT_LENGTH);
        Utils::copyText(roles[employeeCount], role, Utils::MAX_TEXT_LENGTH);
        Utils::copyText(phones[employeeCount], phone, Utils::MAX_TEXT_LENGTH);
        Utils::copyText(departments[employeeCount], dept, Utils::MAX_TEXT_LENGTH);
        Utils::copyText(usernames[employeeCount], user, Utils::MAX_TEXT_LENGTH);
        Utils::copyText(passwords[employeeCount], pass, Utils::MAX_TEXT_LENGTH);
        ++employeeCount;
    }
    file.close();
}

void EmployeeManager::saveToFile() {
    ofstream file(filename);
    if (!file.is_open()) return;

    for (int i = 0; i < employeeCount; ++i) {
        file << ids[i] << "|" << names[i] << "|" << roles[i] << "|"
             << phones[i] << "|" << departments[i] << "|"
             << usernames[i] << "|" << passwords[i] << "\n";
    }
    file.close();
}

void EmployeeManager::addEmployee() {
    Utils::clearScreen();
    cout << "--- THEM NHAN VIEN MOI ---\n";
    if (employeeCount >= Utils::MAX_RECORDS) {
        cout << "Danh sach nhan vien da day!\n";
        Utils::pauseScreen();
        return;
    }

    string generatedId = Utils::generateId("NV", employeeCount);
    Utils::copyText(ids[employeeCount], generatedId, Utils::MAX_ID_LENGTH);
    
    cout << "Ma nhan vien duoc cap: " << ids[employeeCount] << "\n";
    cout << "Nhap ten nhan vien: ";
    Utils::copyText(names[employeeCount], Utils::readString(), Utils::MAX_TEXT_LENGTH);
    
    cout << "Nhap vai tro (Doctor/Nurse/Admin): ";
    Utils::copyText(roles[employeeCount], Utils::readString(), Utils::MAX_TEXT_LENGTH);
    
    cout << "Nhap so dien thoai: ";
    Utils::copyText(phones[employeeCount], Utils::readString(), Utils::MAX_TEXT_LENGTH);
    
    cout << "Nhap khoa (Department): ";
    Utils::copyText(departments[employeeCount], Utils::readString(), Utils::MAX_TEXT_LENGTH);
    
    cout << "Nhap ten dang nhap: ";
    Utils::copyText(usernames[employeeCount], Utils::readString(), Utils::MAX_TEXT_LENGTH);
    
    cout << "Nhap mat khau: ";
    Utils::copyText(passwords[employeeCount], Utils::readString(), Utils::MAX_TEXT_LENGTH);
    
    ++employeeCount;
    saveToFile();
    cout << "Them nhan vien thanh cong!\n";
    Utils::pauseScreen();
}

void EmployeeManager::editEmployee() {
    Utils::clearScreen();
    cout << "--- SUA THONG TIN NHAN VIEN ---\n";
    cout << "Nhap ma nhan vien can sua: ";
    string id = Utils::readString();
    int index = findIndexById(id);
    
    if (index != -1) {
        cout << "Thong tin hien tai: " << names[index] << " - " << roles[index] << "\n";
        cout << "Nhap ten moi (de trong de giu nguyen): ";
        string name = Utils::readString();
        if (!name.empty()) Utils::copyText(names[index], name, Utils::MAX_TEXT_LENGTH);
        
        cout << "Nhap vai tro moi (de trong de giu nguyen): ";
        string role = Utils::readString();
        if (!role.empty()) Utils::copyText(roles[index], role, Utils::MAX_TEXT_LENGTH);
        
        cout << "Nhap SDT moi (de trong de giu nguyen): ";
        string phone = Utils::readString();
        if (!phone.empty()) Utils::copyText(phones[index], phone, Utils::MAX_TEXT_LENGTH);
        
        cout << "Nhap khoa moi (de trong de giu nguyen): ";
        string dept = Utils::readString();
        if (!dept.empty()) Utils::copyText(departments[index], dept, Utils::MAX_TEXT_LENGTH);
        
        saveToFile();
        cout << "Cap nhat thanh cong!\n";
        Utils::pauseScreen();
        return;
    }
    cout << "Khong tim thay nhan vien voi ma " << id << "\n";
    Utils::pauseScreen();
}

void EmployeeManager::deleteEmployee() {
    Utils::clearScreen();
    cout << "--- XOA NHAN VIEN ---\n";
    cout << "Nhap ma nhan vien can xoa: ";
    string id = Utils::readString();
    int index = findIndexById(id);
    
    if (index != -1) {
        if (strcmp(usernames[index], "admin") == 0) {
            cout << "Khong the xoa tai khoan quan tri he thong mac din!\n";
            Utils::pauseScreen();
            return;
        }
        removeAt(index);
        saveToFile();
        cout << "Xoa nhan vien thanh cong!\n";
        Utils::pauseScreen();
        return;
    }
    cout << "Khong tim thay nhan vien voi ma " << id << "\n";
    Utils::pauseScreen();
}

void EmployeeManager::searchEmployee() {
    Utils::clearScreen();
    cout << "--- TIM KIEM NHAN VIEN ---\n";
    cout << "Nhap ten, ma hoac vai tro: ";
    string query = Utils::readString();
    
    bool found = false;
    for (int i = 0; i < employeeCount; ++i) {
        if (Utils::containsText(ids[i], query) || Utils::containsText(names[i], query) || Utils::containsText(roles[i], query)) {
            cout << ids[i] << " - " << names[i] << " - Vai tro: " << roles[i]
                 << " - Khoa: " << departments[i] << " - SDT: " << phones[i] << "\n";
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay ket qua phu hop.\n";
    Utils::pauseScreen();
}

void EmployeeManager::displayAllEmployees() {
    Utils::clearScreen();
    cout << "--- DANH SACH NHAN VIEN ---\n";
    if (employeeCount == 0) {
        cout << "Chua co du lieu.\n";
    } else {
        for (int i = 0; i < employeeCount; ++i) {
            cout << ids[i] << " | " << names[i] << " | Vai tro: " << roles[i]
                 << " | SDT: " << phones[i] << " | Khoa: " << departments[i] << "\n";
        }
    }
    Utils::pauseScreen();
}

int EmployeeManager::authenticate(const string& username, const string& password) {
    for (int i = 0; i < employeeCount; ++i) {
        if (username == usernames[i] && password == passwords[i]) {
            return i;
        }
    }
    return -1;
}

int EmployeeManager::getEmployeeIndexById(const string& id) {
    return findIndexById(id);
}

bool EmployeeManager::employeeExists(const string& id) {
    return getEmployeeIndexById(id) != -1;
}

const char* EmployeeManager::getEmployeeName(int index) {
    if (index < 0 || index >= employeeCount) return "";
    return names[index];
}

const char* EmployeeManager::getEmployeePassword(int index) {
    if (index < 0 || index >= employeeCount) return "";
    return passwords[index];
}

void EmployeeManager::updateEmployeePassword(int index, const string& newPassword) {
    if (index < 0 || index >= employeeCount) return;
    Utils::copyText(passwords[index], newPassword, Utils::MAX_TEXT_LENGTH);
    saveToFile();
}
