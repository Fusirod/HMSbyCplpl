#include "PatientManager.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

PatientManager::PatientManager() {
    filename = "data/patients.txt";
    loadFromFile();
}

PatientManager::~PatientManager() {
    saveToFile();
}

void PatientManager::loadFromFile() {
    patients.clear();
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, name, ageStr, gender, phone, address, medicalHistory;
        
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, ageStr, '|');
        getline(ss, gender, '|');
        getline(ss, phone, '|');
        getline(ss, address, '|');
        getline(ss, medicalHistory, '|');

        Patient p;
        p.id = id;
        p.name = name;
        p.age = stoi(ageStr);
        p.gender = gender;
        p.phone = phone;
        p.address = address;
        p.medicalHistory = medicalHistory;
        patients.push_back(p);
    }
    file.close();
}

void PatientManager::saveToFile() {
    ofstream file(filename);
    if (!file.is_open()) return;

    for (const auto& p : patients) {
        file << p.id << "|" << p.name << "|" << p.age << "|" 
             << p.gender << "|" << p.phone << "|" << p.address << "|" 
             << p.medicalHistory << "\n";
    }
    file.close();
}

void PatientManager::addPatient() {
    Utils::clearScreen();
    cout << "--- THEM BENH NHAN MOI ---\n";
    Patient p;
    p.id = Utils::generateId("BN", patients.size());
    
    cout << "Ma benh nhan duoc cap: " << p.id << "\n";
    cout << "Nhap ten benh nhan: ";
    p.name = Utils::readString();
    
    cout << "Nhap tuoi: ";
    p.age = Utils::readInt();
    
    cout << "Nhap gioi tinh (Nam/Nu): ";
    p.gender = Utils::readString();
    
    cout << "Nhap so dien thoai: ";
    p.phone = Utils::readString();
    
    cout << "Nhap dia chi: ";
    p.address = Utils::readString();
    
    cout << "Nhap tien su benh: ";
    p.medicalHistory = Utils::readString();
    
    patients.push_back(p);
    saveToFile();
    cout << "Them benh nhan thanh cong!\n";
    Utils::pauseScreen();
}

void PatientManager::editPatient() {
    Utils::clearScreen();
    cout << "--- SUA THONG TIN BENH NHAN ---\n";
    cout << "Nhap ma benh nhan can sua: ";
    string id = Utils::readString();
    
    for (auto& p : patients) {
        if (p.id == id) {
            cout << "Thong tin hien tai: " << p.name << " - Tuoi: " << p.age << "\n";
            cout << "Nhap ten moi (de trong de giu nguyen): ";
            string name = Utils::readString();
            if (!name.empty()) p.name = name;
            
            cout << "Nhap tuoi moi (nhap 0 de giu nguyen): ";
            int age = Utils::readInt();
            if (age != 0) p.age = age;
            
            cout << "Nhap gioi tinh moi (de trong de giu nguyen): ";
            string gender = Utils::readString();
            if (!gender.empty()) p.gender = gender;
            
            cout << "Nhap SDT moi (de trong de giu nguyen): ";
            string phone = Utils::readString();
            if (!phone.empty()) p.phone = phone;
            
            cout << "Nhap dia chi moi (de trong de giu nguyen): ";
            string address = Utils::readString();
            if (!address.empty()) p.address = address;
            
            cout << "Nhap tien su benh moi (de trong de giu nguyen): ";
            string med = Utils::readString();
            if (!med.empty()) p.medicalHistory = med;
            
            saveToFile();
            cout << "Cap nhat thanh cong!\n";
            Utils::pauseScreen();
            return;
        }
    }
    cout << "Khong tim thay benh nhan voi ma " << id << "\n";
    Utils::pauseScreen();
}

void PatientManager::deletePatient() {
    Utils::clearScreen();
    cout << "--- XOA BENH NHAN ---\n";
    cout << "Nhap ma benh nhan can xoa: ";
    string id = Utils::readString();
    
    for (auto it = patients.begin(); it != patients.end(); ++it) {
        if (it->id == id) {
            patients.erase(it);
            saveToFile();
            cout << "Xoa benh nhan thanh cong!\n";
            Utils::pauseScreen();
            return;
        }
    }
    cout << "Khong tim thay benh nhan voi ma " << id << "\n";
    Utils::pauseScreen();
}

void PatientManager::searchPatient() {
    Utils::clearScreen();
    cout << "--- TIM KIEM BENH NHAN ---\n";
    cout << "Nhap ten hoac ma benh nhan: ";
    string query = Utils::readString();
    
    bool found = false;
    for (const auto& p : patients) {
        if (p.id.find(query) != string::npos || p.name.find(query) != string::npos) {
            cout << p.id << " - " << p.name << " - Tuoi: " << p.age 
                 << " - SDT: " << p.phone << " - Tien su benh: " << p.medicalHistory << "\n";
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay ket qua phu hop.\n";
    Utils::pauseScreen();
}

void PatientManager::displayAllPatients() {
    Utils::clearScreen();
    cout << "--- DANH SACH BENH NHAN ---\n";
    if (patients.empty()) {
        cout << "Chua co du lieu.\n";
    } else {
        for (const auto& p : patients) {
            cout << p.id << " | " << p.name << " | Tuoi: " << p.age 
                 << " | Gioi tinh: " << p.gender << " | SDT: " << p.phone 
                 << " | Dia chi: " << p.address << " | Tien su: " << p.medicalHistory << "\n";
        }
    }
    Utils::pauseScreen();
}

Patient* PatientManager::getPatientById(const string& id) {
    for (auto& p : patients) {
        if (p.id == id) return &p;
    }
    return nullptr;
}

bool PatientManager::patientExists(const string& id) {
    return getPatientById(id) != nullptr;
}
