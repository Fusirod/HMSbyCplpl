#include "EmployeeManager.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

EmployeeManager::EmployeeManager() {
    filename = "employees.txt";
    loadFromFile();
    
    // Create default admin if list is empty
    if (employees.empty()) {
        Employee admin;
        admin.id = "AD001";
        admin.name = "System Admin";
        admin.role = "Admin";
        admin.phone = "0000000000";
        admin.department = "IT";
        admin.username = "admin";
        admin.password = "admin";
        employees.push_back(admin);
        saveToFile();
    }
}

EmployeeManager::~EmployeeManager() {
    saveToFile();
}

void EmployeeManager::loadFromFile() {
    employees.clear();
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
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

        Employee e;
        e.id = id;
        e.name = name;
        e.role = role;
        e.phone = phone;
        e.department = dept;
        e.username = user;
        e.password = pass;
        employees.push_back(e);
    }
    file.close();
}

void EmployeeManager::saveToFile() {
    ofstream file(filename);
    if (!file.is_open()) return;

    for (const auto& e : employees) {
        file << e.id << "|" << e.name << "|" << e.role << "|" 
             << e.phone << "|" << e.department << "|" 
             << e.username << "|" << e.password << "\n";
    }
    file.close();
}

void EmployeeManager::addEmployee() {
    Utils::clearScreen();
    cout << "--- THEM NHAN VIEN MOI ---\n";
    Employee e;
    e.id = Utils::generateId("NV", employees.size());
    
    cout << "Ma nhan vien duoc cap: " << e.id << "\n";
    cout << "Nhap ten nhan vien: ";
    e.name = Utils::readString();
    
    cout << "Nhap vai tro (Doctor/Nurse/Admin): ";
    e.role = Utils::readString();
    
    cout << "Nhap so dien thoai: ";
    e.phone = Utils::readString();
    
    cout << "Nhap khoa (Department): ";
    e.department = Utils::readString();
    
    cout << "Nhap ten dang nhap: ";
    e.username = Utils::readString();
    
    cout << "Nhap mat khau: ";
    e.password = Utils::readString();
    
    employees.push_back(e);
    saveToFile();
    cout << "Them nhan vien thanh cong!\n";
    Utils::pauseScreen();
}

void EmployeeManager::editEmployee() {
    Utils::clearScreen();
    cout << "--- SUA THONG TIN NHAN VIEN ---\n";
    cout << "Nhap ma nhan vien can sua: ";
    string id = Utils::readString();
    
    for (auto& e : employees) {
        if (e.id == id) {
            cout << "Thong tin hien tai: " << e.name << " - " << e.role << "\n";
            cout << "Nhap ten moi (de trong de giu nguyen): ";
            string name = Utils::readString();
            if (!name.empty()) e.name = name;
            
            cout << "Nhap vai tro moi (de trong de giu nguyen): ";
            string role = Utils::readString();
            if (!role.empty()) e.role = role;
            
            cout << "Nhap SDT moi (de trong de giu nguyen): ";
            string phone = Utils::readString();
            if (!phone.empty()) e.phone = phone;
            
            cout << "Nhap khoa moi (de trong de giu nguyen): ";
            string dept = Utils::readString();
            if (!dept.empty()) e.department = dept;
            
            saveToFile();
            cout << "Cap nhat thanh cong!\n";
            Utils::pauseScreen();
            return;
        }
    }
    cout << "Khong tim thay nhan vien voi ma " << id << "\n";
    Utils::pauseScreen();
}

void EmployeeManager::deleteEmployee() {
    Utils::clearScreen();
    cout << "--- XOA NHAN VIEN ---\n";
    cout << "Nhap ma nhan vien can xoa: ";
    string id = Utils::readString();
    
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if (it->id == id) {
            if (it->username == "admin") {
                cout << "Khong the xoa tai khoan quan tri he thong mac din!\n";
                Utils::pauseScreen();
                return;
            }
            employees.erase(it);
            saveToFile();
            cout << "Xoa nhan vien thanh cong!\n";
            Utils::pauseScreen();
            return;
        }
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
    for (const auto& e : employees) {
        if (e.id.find(query) != string::npos || e.name.find(query) != string::npos || e.role.find(query) != string::npos) {
            cout << e.id << " - " << e.name << " - Vai tro: " << e.role 
                 << " - Khoa: " << e.department << " - SDT: " << e.phone << "\n";
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay ket qua phu hop.\n";
    Utils::pauseScreen();
}

void EmployeeManager::displayAllEmployees() {
    Utils::clearScreen();
    cout << "--- DANH SACH NHAN VIEN ---\n";
    if (employees.empty()) {
        cout << "Chua co du lieu.\n";
    } else {
        for (const auto& e : employees) {
            cout << e.id << " | " << e.name << " | Vai tro: " << e.role 
                 << " | SDT: " << e.phone << " | Khoa: " << e.department << "\n";
        }
    }
    Utils::pauseScreen();
}

Employee* EmployeeManager::authenticate(const string& username, const string& password) {
    for (auto& e : employees) {
        if (e.username == username && e.password == password) {
            return &e;
        }
    }
    return nullptr;
}

Employee* EmployeeManager::getEmployeeById(const string& id) {
    for (auto& e : employees) {
        if (e.id == id) return &e;
    }
    return nullptr;
}

bool EmployeeManager::employeeExists(const string& id) {
    return getEmployeeById(id) != nullptr;
}
