#include "AppointmentManager.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

AppointmentManager::AppointmentManager() {
    filename = "data/appointments.txt";
    loadFromFile();
}

AppointmentManager::~AppointmentManager() {
    saveToFile();
}

void AppointmentManager::loadFromFile() {
    appointments.clear();
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, pId, dId, date, time, status;
        
        getline(ss, id, '|');
        getline(ss, pId, '|');
        getline(ss, dId, '|');
        getline(ss, date, '|');
        getline(ss, time, '|');
        getline(ss, status, '|');

        Appointment a;
        a.id = id;
        a.patientId = pId;
        a.doctorId = dId;
        a.date = date;
        a.time = time;
        a.status = status;
        appointments.push_back(a);
    }
    file.close();
}

void AppointmentManager::saveToFile() {
    ofstream file(filename);
    if (!file.is_open()) return;

    for (const auto& a : appointments) {
        file << a.id << "|" << a.patientId << "|" << a.doctorId << "|" 
             << a.date << "|" << a.time << "|" << a.status << "\n";
    }
    file.close();
}

void AppointmentManager::addAppointment() {
    Utils::clearScreen();
    cout << "--- THEM LICH KHAM MOI ---\n";
    Appointment a;
    a.id = Utils::generateId("LK", appointments.size());
    
    cout << "Ma lich kham duoc cap: " << a.id << "\n";
    cout << "Nhap ma benh nhan: ";
    a.patientId = Utils::readString();
    
    cout << "Nhap ma bac si: ";
    a.doctorId = Utils::readString();
    
    cout << "Nhap ngay kham (DD/MM/YYYY): ";
    a.date = Utils::readString();
    
    cout << "Nhap gio kham (HH:MM): ";
    a.time = Utils::readString();
    
    a.status = "Scheduled";
    
    appointments.push_back(a);
    saveToFile();
    cout << "Them lich kham thanh cong!\n";
    Utils::pauseScreen();
}

void AppointmentManager::editAppointment() {
    Utils::clearScreen();
    cout << "--- SUA LICH KHAM ---\n";
    cout << "Nhap ma lich kham can sua: ";
    string id = Utils::readString();
    
    for (auto& a : appointments) {
        if (a.id == id) {
            cout << "Thong tin: BN " << a.patientId << " - BS " << a.doctorId << " luc " << a.time << " " << a.date << "\n";
            
            cout << "Nhap ma bac si moi (de trong de giu nguyen): ";
            string bs = Utils::readString();
            if (!bs.empty()) a.doctorId = bs;
            
            cout << "Nhap ngay kham moi (de trong de giu nguyen): ";
            string date = Utils::readString();
            if (!date.empty()) a.date = date;
            
            cout << "Nhap gio kham moi (de trong de giu nguyen): ";
            string time = Utils::readString();
            if (!time.empty()) a.time = time;
            
            cout << "Nhap trang thai (Scheduled/Completed/Cancelled) (de trong de giu nguyen): ";
            string status = Utils::readString();
            if (!status.empty()) a.status = status;
            
            saveToFile();
            cout << "Cap nhat thanh cong!\n";
            Utils::pauseScreen();
            return;
        }
    }
    cout << "Khong tim thay lich kham voi ma " << id << "\n";
    Utils::pauseScreen();
}

void AppointmentManager::deleteAppointment() {
    Utils::clearScreen();
    cout << "--- XOA LICH KHAM ---\n";
    cout << "Nhap ma lich kham can xoa: ";
    string id = Utils::readString();
    
    for (auto it = appointments.begin(); it != appointments.end(); ++it) {
        if (it->id == id) {
            appointments.erase(it);
            saveToFile();
            cout << "Xoa lich kham thanh cong!\n";
            Utils::pauseScreen();
            return;
        }
    }
    cout << "Khong tim thay lich kham voi ma " << id << "\n";
    Utils::pauseScreen();
}

void AppointmentManager::searchAppointment() {
    Utils::clearScreen();
    cout << "--- TIM KIEM LICH KHAM ---\n";
    cout << "Nhap ma lich kham, ma benh nhan hoac ma bac si: ";
    string query = Utils::readString();
    
    bool found = false;
    for (const auto& a : appointments) {
        if (a.id.find(query) != string::npos || a.patientId.find(query) != string::npos || a.doctorId.find(query) != string::npos) {
            cout << a.id << " - BN: " << a.patientId << " - BS: " << a.doctorId 
                 << " - Thoi gian: " << a.time << " " << a.date << " - Trang thai: " << a.status << "\n";
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay ket qua phu hop.\n";
    Utils::pauseScreen();
}

void AppointmentManager::displayAllAppointments() {
    Utils::clearScreen();
    cout << "--- DANH SACH LICH KHAM ---\n";
    if (appointments.empty()) {
        cout << "Chua co du lieu.\n";
    } else {
        for (const auto& a : appointments) {
            cout << a.id << " | BN: " << a.patientId << " | BS: " << a.doctorId 
                 << " | Ngay: " << a.date << " | Gio: " << a.time << " | TT: " << a.status << "\n";
        }
    }
    Utils::pauseScreen();
}
