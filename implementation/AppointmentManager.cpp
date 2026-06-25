#include "AppointmentManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

AppointmentManager::AppointmentManager() {
    filename = "data/appointments.txt";
    appointmentCount = 0;
    loadFromFile();
}

AppointmentManager::~AppointmentManager() {
    saveToFile();
}

int AppointmentManager::findIndexById(const string& id) {
    for (int i = 0; i < appointmentCount; ++i) {
        if (id == ids[i]) return i;
    }
    return -1;
}

void AppointmentManager::removeAt(int index) {
    for (int i = index; i < appointmentCount - 1; ++i) {
        strcpy(ids[i], ids[i + 1]);
        strcpy(patientIds[i], patientIds[i + 1]);
        strcpy(doctorIds[i], doctorIds[i + 1]);
        strcpy(dates[i], dates[i + 1]);
        strcpy(times[i], times[i + 1]);
        strcpy(statuses[i], statuses[i + 1]);
    }
    --appointmentCount;
}

void AppointmentManager::loadFromFile() {
    appointmentCount = 0;
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (appointmentCount < Utils::MAX_RECORDS && getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, pId, dId, date, time, status;
        
        getline(ss, id, '|');
        getline(ss, pId, '|');
        getline(ss, dId, '|');
        getline(ss, date, '|');
        getline(ss, time, '|');
        getline(ss, status, '|');

        Utils::copyText(ids[appointmentCount], id, Utils::MAX_ID_LENGTH);
        Utils::copyText(patientIds[appointmentCount], pId, Utils::MAX_ID_LENGTH);
        Utils::copyText(doctorIds[appointmentCount], dId, Utils::MAX_ID_LENGTH);
        Utils::copyText(dates[appointmentCount], date, Utils::MAX_TEXT_LENGTH);
        Utils::copyText(times[appointmentCount], time, Utils::MAX_TEXT_LENGTH);
        Utils::copyText(statuses[appointmentCount], status, Utils::MAX_TEXT_LENGTH);
        ++appointmentCount;
    }
    file.close();
}

void AppointmentManager::saveToFile() {
    ofstream file(filename);
    if (!file.is_open()) return;

    for (int i = 0; i < appointmentCount; ++i) {
        file << ids[i] << "|" << patientIds[i] << "|" << doctorIds[i] << "|"
             << dates[i] << "|" << times[i] << "|" << statuses[i] << "\n";
    }
    file.close();
}

void AppointmentManager::addAppointment() {
    Utils::clearScreen();
    cout << "--- THEM LICH KHAM MOI ---\n";
    if (appointmentCount >= Utils::MAX_RECORDS) {
        cout << "Danh sach lich kham da day!\n";
        Utils::pauseScreen();
        return;
    }

    string generatedId = Utils::generateId("LK", appointmentCount);
    Utils::copyText(ids[appointmentCount], generatedId, Utils::MAX_ID_LENGTH);
    
    cout << "Ma lich kham duoc cap: " << ids[appointmentCount] << "\n";
    cout << "Nhap ma benh nhan: ";
    Utils::copyText(patientIds[appointmentCount], Utils::readString(), Utils::MAX_ID_LENGTH);
    
    cout << "Nhap ma bac si: ";
    Utils::copyText(doctorIds[appointmentCount], Utils::readString(), Utils::MAX_ID_LENGTH);
    
    cout << "Nhap ngay kham (DD/MM/YYYY): ";
    Utils::copyText(dates[appointmentCount], Utils::readString(), Utils::MAX_TEXT_LENGTH);
    
    cout << "Nhap gio kham (HH:MM): ";
    Utils::copyText(times[appointmentCount], Utils::readString(), Utils::MAX_TEXT_LENGTH);
    
    Utils::copyText(statuses[appointmentCount], "Scheduled", Utils::MAX_TEXT_LENGTH);
    
    ++appointmentCount;
    saveToFile();
    cout << "Them lich kham thanh cong!\n";
    Utils::pauseScreen();
}

void AppointmentManager::editAppointment() {
    Utils::clearScreen();
    cout << "--- SUA LICH KHAM ---\n";
    cout << "Nhap ma lich kham can sua: ";
    string id = Utils::readString();
    int index = findIndexById(id);
    
    if (index != -1) {
        cout << "Thong tin: BN " << patientIds[index] << " - BS " << doctorIds[index]
             << " luc " << times[index] << " " << dates[index] << "\n";
        
        cout << "Nhap ma bac si moi (de trong de giu nguyen): ";
        string bs = Utils::readString();
        if (!bs.empty()) Utils::copyText(doctorIds[index], bs, Utils::MAX_ID_LENGTH);
        
        cout << "Nhap ngay kham moi (de trong de giu nguyen): ";
        string date = Utils::readString();
        if (!date.empty()) Utils::copyText(dates[index], date, Utils::MAX_TEXT_LENGTH);
        
        cout << "Nhap gio kham moi (de trong de giu nguyen): ";
        string time = Utils::readString();
        if (!time.empty()) Utils::copyText(times[index], time, Utils::MAX_TEXT_LENGTH);
        
        cout << "Nhap trang thai (Scheduled/Completed/Cancelled) (de trong de giu nguyen): ";
        string status = Utils::readString();
        if (!status.empty()) Utils::copyText(statuses[index], status, Utils::MAX_TEXT_LENGTH);
        
        saveToFile();
        cout << "Cap nhat thanh cong!\n";
        Utils::pauseScreen();
        return;
    }
    cout << "Khong tim thay lich kham voi ma " << id << "\n";
    Utils::pauseScreen();
}

void AppointmentManager::deleteAppointment() {
    Utils::clearScreen();
    cout << "--- XOA LICH KHAM ---\n";
    cout << "Nhap ma lich kham can xoa: ";
    string id = Utils::readString();
    int index = findIndexById(id);
    
    if (index != -1) {
        removeAt(index);
        saveToFile();
        cout << "Xoa lich kham thanh cong!\n";
        Utils::pauseScreen();
        return;
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
    for (int i = 0; i < appointmentCount; ++i) {
        if (Utils::containsText(ids[i], query) || Utils::containsText(patientIds[i], query) || Utils::containsText(doctorIds[i], query)) {
            cout << ids[i] << " - BN: " << patientIds[i] << " - BS: " << doctorIds[i]
                 << " - Thoi gian: " << times[i] << " " << dates[i] << " - Trang thai: " << statuses[i] << "\n";
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay ket qua phu hop.\n";
    Utils::pauseScreen();
}

void AppointmentManager::displayAllAppointments() {
    Utils::clearScreen();
    cout << "--- DANH SACH LICH KHAM ---\n";
    if (appointmentCount == 0) {
        cout << "Chua co du lieu.\n";
    } else {
        for (int i = 0; i < appointmentCount; ++i) {
            cout << ids[i] << " | BN: " << patientIds[i] << " | BS: " << doctorIds[i]
                 << " | Ngay: " << dates[i] << " | Gio: " << times[i] << " | TT: " << statuses[i] << "\n";
        }
    }
    Utils::pauseScreen();
}
