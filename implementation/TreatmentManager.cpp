#include "TreatmentManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

TreatmentManager::TreatmentManager() {
    filename = "data/treatments.txt";
    treatmentCount = 0;
    loadFromFile();
}

TreatmentManager::~TreatmentManager() {
    saveToFile();
}

int TreatmentManager::findIndexById(const string& id) {
    for (int i = 0; i < treatmentCount; ++i) {
        if (id == ids[i]) return i;
    }
    return -1;
}

void TreatmentManager::removeAt(int index) {
    for (int i = index; i < treatmentCount - 1; ++i) {
        strcpy(ids[i], ids[i + 1]);
        strcpy(patientIds[i], patientIds[i + 1]);
        strcpy(doctorIds[i], doctorIds[i + 1]);
        strcpy(diagnoses[i], diagnoses[i + 1]);
        strcpy(prescriptions[i], prescriptions[i + 1]);
        strcpy(notes[i], notes[i + 1]);
    }
    --treatmentCount;
}

void TreatmentManager::loadFromFile() {
    treatmentCount = 0;
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (treatmentCount < Utils::MAX_RECORDS && getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, pId, dId, diagnosis, pres, note;
        
        getline(ss, id, '|');
        getline(ss, pId, '|');
        getline(ss, dId, '|');
        getline(ss, diagnosis, '|');
        getline(ss, pres, '|');
        getline(ss, note, '|');

        Utils::copyText(ids[treatmentCount], id, Utils::MAX_ID_LENGTH);
        Utils::copyText(patientIds[treatmentCount], pId, Utils::MAX_ID_LENGTH);
        Utils::copyText(doctorIds[treatmentCount], dId, Utils::MAX_ID_LENGTH);
        Utils::copyText(diagnoses[treatmentCount], diagnosis, Utils::MAX_LONG_TEXT_LENGTH);
        Utils::copyText(prescriptions[treatmentCount], pres, Utils::MAX_LONG_TEXT_LENGTH);
        Utils::copyText(notes[treatmentCount], note, Utils::MAX_LONG_TEXT_LENGTH);
        ++treatmentCount;
    }
    file.close();
}

void TreatmentManager::saveToFile() {
    ofstream file(filename);
    if (!file.is_open()) return;

    for (int i = 0; i < treatmentCount; ++i) {
        file << ids[i] << "|" << patientIds[i] << "|" << doctorIds[i] << "|"
             << diagnoses[i] << "|" << prescriptions[i] << "|" << notes[i] << "\n";
    }
    file.close();
}

void TreatmentManager::addTreatment() {
    Utils::clearScreen();
    cout << "--- THEM HO SO DIEU TRI ---\n";
    if (treatmentCount >= Utils::MAX_RECORDS) {
        cout << "Danh sach ho so dieu tri da day!\n";
        Utils::pauseScreen();
        return;
    }

    string generatedId = Utils::generateId("DT", treatmentCount);
    Utils::copyText(ids[treatmentCount], generatedId, Utils::MAX_ID_LENGTH);
    
    cout << "Ma dieu tri duoc cap: " << ids[treatmentCount] << "\n";
    cout << "Nhap ma benh nhan: ";
    Utils::copyText(patientIds[treatmentCount], Utils::readString(), Utils::MAX_ID_LENGTH);
    
    cout << "Nhap ma bac si dieu tri: ";
    Utils::copyText(doctorIds[treatmentCount], Utils::readString(), Utils::MAX_ID_LENGTH);
    
    cout << "Nhap chan doan: ";
    Utils::copyText(diagnoses[treatmentCount], Utils::readString(), Utils::MAX_LONG_TEXT_LENGTH);
    
    cout << "Nhap don thuoc: ";
    Utils::copyText(prescriptions[treatmentCount], Utils::readString(), Utils::MAX_LONG_TEXT_LENGTH);
    
    cout << "Nhap ghi chu: ";
    Utils::copyText(notes[treatmentCount], Utils::readString(), Utils::MAX_LONG_TEXT_LENGTH);
    
    ++treatmentCount;
    saveToFile();
    cout << "Them ho so dieu tri thanh cong!\n";
    Utils::pauseScreen();
}

void TreatmentManager::editTreatment() {
    Utils::clearScreen();
    cout << "--- SUA HO SO DIEU TRI ---\n";
    cout << "Nhap ma dieu tri can sua: ";
    string id = Utils::readString();
    int index = findIndexById(id);
    
    if (index != -1) {
        cout << "Nhap chan doan moi (de trong de giu nguyen): ";
        string diag = Utils::readString();
        if (!diag.empty()) Utils::copyText(diagnoses[index], diag, Utils::MAX_LONG_TEXT_LENGTH);
        
        cout << "Nhap don thuoc moi (de trong de giu nguyen): ";
        string pres = Utils::readString();
        if (!pres.empty()) Utils::copyText(prescriptions[index], pres, Utils::MAX_LONG_TEXT_LENGTH);
        
        cout << "Nhap ghi chu moi (de trong de giu nguyen): ";
        string note = Utils::readString();
        if (!note.empty()) Utils::copyText(notes[index], note, Utils::MAX_LONG_TEXT_LENGTH);
        
        saveToFile();
        cout << "Cap nhat thanh cong!\n";
        Utils::pauseScreen();
        return;
    }
    cout << "Khong tim thay ho so dieu tri voi ma " << id << "\n";
    Utils::pauseScreen();
}

void TreatmentManager::deleteTreatment() {
    Utils::clearScreen();
    cout << "--- XOA HO SO DIEU TRI ---\n";
    cout << "Nhap ma dieu tri can xoa: ";
    string id = Utils::readString();
    int index = findIndexById(id);
    
    if (index != -1) {
        removeAt(index);
        saveToFile();
        cout << "Xoa ho so dieu tri thanh cong!\n";
        Utils::pauseScreen();
        return;
    }
    cout << "Khong tim thay ho so dieu tri voi ma " << id << "\n";
    Utils::pauseScreen();
}

void TreatmentManager::searchTreatment() {
    Utils::clearScreen();
    cout << "--- TIM KIEM HO SO DIEU TRI ---\n";
    cout << "Nhap ma dieu tri, ma benh nhan hoac ma bac si: ";
    string query = Utils::readString();
    
    bool found = false;
    for (int i = 0; i < treatmentCount; ++i) {
        if (Utils::containsText(ids[i], query) || Utils::containsText(patientIds[i], query) || Utils::containsText(doctorIds[i], query)) {
            cout << ids[i] << " - BN: " << patientIds[i] << " - BS: " << doctorIds[i]
                 << "\nChan doan: " << diagnoses[i] << "\nDon thuoc: " << prescriptions[i] << "\nGhi chu: " << notes[i] << "\n-------------------\n";
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay ket qua phu hop.\n";
    Utils::pauseScreen();
}

void TreatmentManager::displayAllTreatments() {
    Utils::clearScreen();
    cout << "--- DANH SACH HO SO DIEU TRI ---\n";
    if (treatmentCount == 0) {
        cout << "Chua co du lieu.\n";
    } else {
        for (int i = 0; i < treatmentCount; ++i) {
            cout << ids[i] << " | BN: " << patientIds[i] << " | BS: " << doctorIds[i]
                 << " | Chan doan: " << diagnoses[i] << " | Don thuoc: " << prescriptions[i] << "\n";
        }
    }
    Utils::pauseScreen();
}
