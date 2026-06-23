#include "InvoiceManager.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

InvoiceManager::InvoiceManager() {
    filename = "data/invoices.txt";
    loadFromFile();
}

InvoiceManager::~InvoiceManager() {
    saveToFile();
}

void InvoiceManager::loadFromFile() {
    invoices.clear();
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, pId, date, amountStr, status;
        
        getline(ss, id, '|');
        getline(ss, pId, '|');
        getline(ss, date, '|');
        getline(ss, amountStr, '|');
        getline(ss, status, '|');

        Invoice inv;
        inv.id = id;
        inv.patientId = pId;
        inv.date = date;
        inv.totalAmount = stod(amountStr);
        inv.status = status;
        invoices.push_back(inv);
    }
    file.close();
}

void InvoiceManager::saveToFile() {
    ofstream file(filename);
    if (!file.is_open()) return;

    for (const auto& inv : invoices) {
        file << inv.id << "|" << inv.patientId << "|" << inv.date << "|" 
             << inv.totalAmount << "|" << inv.status << "\n";
    }
    file.close();
}

void InvoiceManager::addInvoice() {
    Utils::clearScreen();
    cout << "--- THEM HOA DON MOI ---\n";
    Invoice inv;
    inv.id = Utils::generateId("HD", invoices.size());
    
    cout << "Ma hoa don duoc cap: " << inv.id << "\n";
    cout << "Nhap ma benh nhan: ";
    inv.patientId = Utils::readString();
    
    cout << "Nhap ngay lap (DD/MM/YYYY): ";
    inv.date = Utils::readString();
    
    cout << "Nhap tong tien: ";
    inv.totalAmount = Utils::readDouble();
    
    cout << "Nhap trang thai (Paid/Unpaid): ";
    inv.status = Utils::readString();
    
    invoices.push_back(inv);
    saveToFile();
    cout << "Them hoa don thanh cong!\n";
    Utils::pauseScreen();
}

void InvoiceManager::editInvoice() {
    Utils::clearScreen();
    cout << "--- SUA HOA DON ---\n";
    cout << "Nhap ma hoa don can sua: ";
    string id = Utils::readString();
    
    for (auto& inv : invoices) {
        if (inv.id == id) {
            cout << "Thong tin hien tai: BN " << inv.patientId << " - " << inv.totalAmount << " - " << inv.status << "\n";
            
            cout << "Nhap ngay lap moi (de trong de giu nguyen): ";
            string date = Utils::readString();
            if (!date.empty()) inv.date = date;
            
            cout << "Nhap tong tien moi (nhap -1 de giu nguyen): ";
            double amount = Utils::readDouble();
            if (amount != -1) inv.totalAmount = amount;
            
            cout << "Nhap trang thai moi (Paid/Unpaid) (de trong de giu nguyen): ";
            string status = Utils::readString();
            if (!status.empty()) inv.status = status;
            
            saveToFile();
            cout << "Cap nhat thanh cong!\n";
            Utils::pauseScreen();
            return;
        }
    }
    cout << "Khong tim thay hoa don voi ma " << id << "\n";
    Utils::pauseScreen();
}

void InvoiceManager::deleteInvoice() {
    Utils::clearScreen();
    cout << "--- XOA HOA DON ---\n";
    cout << "Nhap ma hoa don can xoa: ";
    string id = Utils::readString();
    
    for (auto it = invoices.begin(); it != invoices.end(); ++it) {
        if (it->id == id) {
            invoices.erase(it);
            saveToFile();
            cout << "Xoa hoa don thanh cong!\n";
            Utils::pauseScreen();
            return;
        }
    }
    cout << "Khong tim thay hoa don voi ma " << id << "\n";
    Utils::pauseScreen();
}

void InvoiceManager::searchInvoice() {
    Utils::clearScreen();
    cout << "--- TIM KIEM HOA DON ---\n";
    cout << "Nhap ma hoa don hoac ma benh nhan: ";
    string query = Utils::readString();
    
    bool found = false;
    for (const auto& inv : invoices) {
        if (inv.id.find(query) != string::npos || inv.patientId.find(query) != string::npos) {
            cout << inv.id << " - BN: " << inv.patientId << " - Ngay: " << inv.date 
                 << " - Tong tien: " << inv.totalAmount << " - Trang thai: " << inv.status << "\n";
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay ket qua phu hop.\n";
    Utils::pauseScreen();
}

void InvoiceManager::displayAllInvoices() {
    Utils::clearScreen();
    cout << "--- DANH SACH HOA DON ---\n";
    if (invoices.empty()) {
        cout << "Chua co du lieu.\n";
    } else {
        for (const auto& inv : invoices) {
            cout << inv.id << " | BN: " << inv.patientId << " | Ngay: " << inv.date 
                 << " | Tong tien: " << inv.totalAmount << " | Trang thai: " << inv.status << "\n";
        }
    }
    Utils::pauseScreen();
}

double InvoiceManager::calculateTotalRevenue() {
    double total = 0;
    for (const auto& inv : invoices) {
        if (inv.status == "Paid") {
            total += inv.totalAmount;
        }
    }
    return total;
}
