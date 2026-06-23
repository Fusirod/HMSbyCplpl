#include "TreatmentManager.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

TreatmentManager::TreatmentManager() {
    filename = "data/treatments.txt";
    loadFromFile();
}

TreatmentManager::~TreatmentManager() {
    saveToFile();
}

void TreatmentManager::loadFromFile() {
    treatments.clear();
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, pId, dId, diagnosis, pres, notes;
        
        getline(ss, id, '|');
        getline(ss, pId, '|');
        getline(ss, dId, '|');
        getline(ss, diagnosis, '|');
        getline(ss, pres, '|');
        getline(ss, notes, '|');

        Treatment t;
        t.id = id;
        t.patientId = pId;
        t.doctorId = dId;
        t.diagnosis = diagnosis;
        t.prescription = pres;
        t.notes = notes;
        treatments.push_back(t);
    }
    file.close();
}

void TreatmentManager::saveToFile() {
    ofstream file(filename);
    if (!file.is_open()) return;

    for (const auto& t : treatments) {
        file << t.id << "|" << t.patientId << "|" << t.doctorId << "|" 
             << t.diagnosis << "|" << t.prescription << "|" << t.notes << "\n";
    }
    file.close();
}

void TreatmentManager::addTreatment() {
    Utils::clearScreen();
    cout << "--- THEM HO SO DIEU TRI ---\n";
    Treatment t;
    t.id = Utils::generateId("DT", treatments.size());
    
    cout << "Ma dieu tri duoc cap: " << t.id << "\n";
    cout << "Nhap ma benh nhan: ";
    t.patientId = Utils::readString();
    
    cout << "Nhap ma bac si dieu tri: ";
    t.doctorId = Utils::readString();
    
    cout << "Nhap chan doan: ";
    t.diagnosis = Utils::readString();
    
    cout << "Nhap don thuoc: ";
    t.prescription = Utils::readString();
    
    cout << "Nhap ghi chu: ";
    t.notes = Utils::readString();
    
    treatments.push_back(t);
    saveToFile();
    cout << "Them ho so dieu tri thanh cong!\n";
    Utils::pauseScreen();
}

void TreatmentManager::editTreatment() {
    Utils::clearScreen();
    cout << "--- SUA HO SO DIEU TRI ---\n";
    cout << "Nhap ma dieu tri can sua: ";
    string id = Utils::readString();
    
    for (auto& t : treatments) {
        if (t.id == id) {
            cout << "Nhap chan doan moi (de trong de giu nguyen): ";
            string diag = Utils::readString();
            if (!diag.empty()) t.diagnosis = diag;
            
            cout << "Nhap don thuoc moi (de trong de giu nguyen): ";
            string pres = Utils::readString();
            if (!pres.empty()) t.prescription = pres;
            
            cout << "Nhap ghi chu moi (de trong de giu nguyen): ";
            string notes = Utils::readString();
            if (!notes.empty()) t.notes = notes;
            
            saveToFile();
            cout << "Cap nhat thanh cong!\n";
            Utils::pauseScreen();
            return;
        }
    }
    cout << "Khong tim thay ho so dieu tri voi ma " << id << "\n";
    Utils::pauseScreen();
}

void TreatmentManager::deleteTreatment() {
    Utils::clearScreen();
    cout << "--- XOA HO SO DIEU TRI ---\n";
    cout << "Nhap ma dieu tri can xoa: ";
    string id = Utils::readString();
    
    for (auto it = treatments.begin(); it != treatments.end(); ++it) {
        if (it->id == id) {
            treatments.erase(it);
            saveToFile();
            cout << "Xoa ho so dieu tri thanh cong!\n";
            Utils::pauseScreen();
            return;
        }
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
    for (const auto& t : treatments) {
        if (t.id.find(query) != string::npos || t.patientId.find(query) != string::npos || t.doctorId.find(query) != string::npos) {
            cout << t.id << " - BN: " << t.patientId << " - BS: " << t.doctorId 
                 << "\nChan doan: " << t.diagnosis << "\nDon thuoc: " << t.prescription << "\nGhi chu: " << t.notes << "\n-------------------\n";
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay ket qua phu hop.\n";
    Utils::pauseScreen();
}

void TreatmentManager::displayAllTreatments() {
    Utils::clearScreen();
    cout << "--- DANH SACH HO SO DIEU TRI ---\n";
    if (treatments.empty()) {
        cout << "Chua co du lieu.\n";
    } else {
        for (const auto& t : treatments) {
            cout << t.id << " | BN: " << t.patientId << " | BS: " << t.doctorId 
                 << " | Chan doan: " << t.diagnosis << " | Don thuoc: " << t.prescription << "\n";
        }
    }
    Utils::pauseScreen();
}
