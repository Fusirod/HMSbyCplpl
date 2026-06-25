#include "PatientManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

PatientManager::PatientManager() {
    filename = "data/patients.txt";
    patientCount = 0;
    loadFromFile();
}

PatientManager::~PatientManager() {
    saveToFile();
}

int PatientManager::findIndexById(const string& id) {
    for (int i = 0; i < patientCount; ++i) {
        if (id == ids[i]) return i;
    }
    return -1;
}

void PatientManager::removeAt(int index) {
    for (int i = index; i < patientCount - 1; ++i) {
        strcpy(ids[i], ids[i + 1]);
        strcpy(names[i], names[i + 1]);
        ages[i] = ages[i + 1];
        strcpy(genders[i], genders[i + 1]);
        strcpy(phones[i], phones[i + 1]);
        strcpy(addresses[i], addresses[i + 1]);
        strcpy(medicalHistories[i], medicalHistories[i + 1]);
    }
    --patientCount;
}

void PatientManager::loadFromFile() {
    patientCount = 0;
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (patientCount < Utils::MAX_RECORDS && getline(file, line)) {
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

        Utils::copyText(ids[patientCount], id, Utils::MAX_ID_LENGTH);
        Utils::copyText(names[patientCount], name, Utils::MAX_TEXT_LENGTH);
        ages[patientCount] = stoi(ageStr);
        Utils::copyText(genders[patientCount], gender, Utils::MAX_TEXT_LENGTH);
        Utils::copyText(phones[patientCount], phone, Utils::MAX_TEXT_LENGTH);
        Utils::copyText(addresses[patientCount], address, Utils::MAX_TEXT_LENGTH);
        Utils::copyText(medicalHistories[patientCount], medicalHistory, Utils::MAX_LONG_TEXT_LENGTH);
        ++patientCount;
    }
    file.close();
}

void PatientManager::saveToFile() {
    ofstream file(filename);
    if (!file.is_open()) return;

    for (int i = 0; i < patientCount; ++i) {
        file << ids[i] << "|" << names[i] << "|" << ages[i] << "|"
             << genders[i] << "|" << phones[i] << "|" << addresses[i] << "|"
             << medicalHistories[i] << "\n";
    }
    file.close();
}

void PatientManager::addPatient() {
    Utils::clearScreen();
    cout << "--- THEM BENH NHAN MOI ---\n";
    if (patientCount >= Utils::MAX_RECORDS) {
        cout << "Danh sach benh nhan da day!\n";
        Utils::pauseScreen();
        return;
    }

    string generatedId = Utils::generateId("BN", patientCount);
    Utils::copyText(ids[patientCount], generatedId, Utils::MAX_ID_LENGTH);
    
    cout << "Ma benh nhan duoc cap: " << ids[patientCount] << "\n";
    cout << "Nhap ten benh nhan: ";
    Utils::copyText(names[patientCount], Utils::readString(), Utils::MAX_TEXT_LENGTH);
    
    cout << "Nhap tuoi: ";
    ages[patientCount] = Utils::readInt();
    
    cout << "Nhap gioi tinh (Nam/Nu): ";
    Utils::copyText(genders[patientCount], Utils::readString(), Utils::MAX_TEXT_LENGTH);
    
    cout << "Nhap so dien thoai: ";
    Utils::copyText(phones[patientCount], Utils::readString(), Utils::MAX_TEXT_LENGTH);
    
    cout << "Nhap dia chi: ";
    Utils::copyText(addresses[patientCount], Utils::readString(), Utils::MAX_TEXT_LENGTH);
    
    cout << "Nhap tien su benh: ";
    Utils::copyText(medicalHistories[patientCount], Utils::readString(), Utils::MAX_LONG_TEXT_LENGTH);
    
    ++patientCount;
    saveToFile();
    cout << "Them benh nhan thanh cong!\n";
    Utils::pauseScreen();
}

void PatientManager::editPatient() {
    Utils::clearScreen();
    cout << "--- SUA THONG TIN BENH NHAN ---\n";
    cout << "Nhap ma benh nhan can sua: ";
    string id = Utils::readString();
    int index = findIndexById(id);
    
    if (index != -1) {
        cout << "Thong tin hien tai: " << names[index] << " - Tuoi: " << ages[index] << "\n";
        cout << "Nhap ten moi (de trong de giu nguyen): ";
        string name = Utils::readString();
        if (!name.empty()) Utils::copyText(names[index], name, Utils::MAX_TEXT_LENGTH);
        
        cout << "Nhap tuoi moi (nhap 0 de giu nguyen): ";
        int age = Utils::readInt();
        if (age != 0) ages[index] = age;
        
        cout << "Nhap gioi tinh moi (de trong de giu nguyen): ";
        string gender = Utils::readString();
        if (!gender.empty()) Utils::copyText(genders[index], gender, Utils::MAX_TEXT_LENGTH);
        
        cout << "Nhap SDT moi (de trong de giu nguyen): ";
        string phone = Utils::readString();
        if (!phone.empty()) Utils::copyText(phones[index], phone, Utils::MAX_TEXT_LENGTH);
        
        cout << "Nhap dia chi moi (de trong de giu nguyen): ";
        string address = Utils::readString();
        if (!address.empty()) Utils::copyText(addresses[index], address, Utils::MAX_TEXT_LENGTH);
        
        cout << "Nhap tien su benh moi (de trong de giu nguyen): ";
        string med = Utils::readString();
        if (!med.empty()) Utils::copyText(medicalHistories[index], med, Utils::MAX_LONG_TEXT_LENGTH);
        
        saveToFile();
        cout << "Cap nhat thanh cong!\n";
        Utils::pauseScreen();
        return;
    }
    cout << "Khong tim thay benh nhan voi ma " << id << "\n";
    Utils::pauseScreen();
}

void PatientManager::deletePatient() {
    Utils::clearScreen();
    cout << "--- XOA BENH NHAN ---\n";
    cout << "Nhap ma benh nhan can xoa: ";
    string id = Utils::readString();
    int index = findIndexById(id);
    
    if (index != -1) {
        removeAt(index);
        saveToFile();
        cout << "Xoa benh nhan thanh cong!\n";
        Utils::pauseScreen();
        return;
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
    for (int i = 0; i < patientCount; ++i) {
        if (Utils::containsText(ids[i], query) || Utils::containsText(names[i], query)) {
            cout << ids[i] << " - " << names[i] << " - Tuoi: " << ages[i]
                 << " - SDT: " << phones[i] << " - Tien su benh: " << medicalHistories[i] << "\n";
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay ket qua phu hop.\n";
    Utils::pauseScreen();
}

void PatientManager::displayAllPatients() {
    Utils::clearScreen();
    cout << "--- DANH SACH BENH NHAN ---\n";
    if (patientCount == 0) {
        cout << "Chua co du lieu.\n";
    } else {
        for (int i = 0; i < patientCount; ++i) {
            cout << ids[i] << " | " << names[i] << " | Tuoi: " << ages[i]
                 << " | Gioi tinh: " << genders[i] << " | SDT: " << phones[i]
                 << " | Dia chi: " << addresses[i] << " | Tien su: " << medicalHistories[i] << "\n";
        }
    }
    Utils::pauseScreen();
}

int PatientManager::getPatientIndexById(const string& id) {
    return findIndexById(id);
}

bool PatientManager::patientExists(const string& id) {
    return getPatientIndexById(id) != -1;
}
