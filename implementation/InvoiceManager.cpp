#include "InvoiceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

InvoiceManager::InvoiceManager() {
    filename = "data/invoices.txt";
    invoiceCount = 0;
    loadFromFile();
}

InvoiceManager::~InvoiceManager() {
    saveToFile();
}

int InvoiceManager::findIndexById(const string& id) {
    for (int i = 0; i < invoiceCount; ++i) {
        if (id == ids[i]) return i;
    }
    return -1;
}

void InvoiceManager::removeAt(int index) {
    for (int i = index; i < invoiceCount - 1; ++i) {
        strcpy(ids[i], ids[i + 1]);
        strcpy(patientIds[i], patientIds[i + 1]);
        strcpy(dates[i], dates[i + 1]);
        totalAmounts[i] = totalAmounts[i + 1];
        strcpy(statuses[i], statuses[i + 1]);
    }
    --invoiceCount;
}

void InvoiceManager::loadFromFile() {
    invoiceCount = 0;
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (invoiceCount < Utils::MAX_RECORDS && getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, pId, date, amountStr, status;
        
        getline(ss, id, '|');
        getline(ss, pId, '|');
        getline(ss, date, '|');
        getline(ss, amountStr, '|');
        getline(ss, status, '|');

        Utils::copyText(ids[invoiceCount], id, Utils::MAX_ID_LENGTH);
        Utils::copyText(patientIds[invoiceCount], pId, Utils::MAX_ID_LENGTH);
        Utils::copyText(dates[invoiceCount], date, Utils::MAX_TEXT_LENGTH);
        totalAmounts[invoiceCount] = stoll(amountStr);
        Utils::copyText(statuses[invoiceCount], status, Utils::MAX_TEXT_LENGTH);
        ++invoiceCount;
    }
    file.close();
}

void InvoiceManager::saveToFile() {
    ofstream file(filename);
    if (!file.is_open()) return;

    for (int i = 0; i < invoiceCount; ++i) {
        file << ids[i] << "|" << patientIds[i] << "|" << dates[i] << "|"
             << totalAmounts[i] << "|" << statuses[i] << "\n";
    }
    file.close();
}

void InvoiceManager::addInvoice() {
    Utils::clearScreen();
    cout << "--- THEM HOA DON MOI ---\n";
    if (invoiceCount >= Utils::MAX_RECORDS) {
        cout << "Danh sach hoa don da day!\n";
        Utils::pauseScreen();
        return;
    }

    string generatedId = Utils::generateId("HD", invoiceCount);
    Utils::copyText(ids[invoiceCount], generatedId, Utils::MAX_ID_LENGTH);
    
    cout << "Ma hoa don duoc cap: " << ids[invoiceCount] << "\n";
    cout << "Nhap ma benh nhan: ";
    Utils::copyText(patientIds[invoiceCount], Utils::readString(), Utils::MAX_ID_LENGTH);
    
    cout << "Nhap ngay lap (DD/MM/YYYY): ";
    Utils::copyText(dates[invoiceCount], Utils::readString(), Utils::MAX_TEXT_LENGTH);
    
    cout << "Nhap tong tien: ";
    totalAmounts[invoiceCount] = Utils::readLongLong();
    
    cout << "Nhap trang thai (Paid/Unpaid): ";
    Utils::copyText(statuses[invoiceCount], Utils::readString(), Utils::MAX_TEXT_LENGTH);
    
    ++invoiceCount;
    saveToFile();
    cout << "Them hoa don thanh cong!\n";
    Utils::pauseScreen();
}

void InvoiceManager::editInvoice() {
    Utils::clearScreen();
    cout << "--- SUA HOA DON ---\n";
    cout << "Nhap ma hoa don can sua: ";
    string id = Utils::readString();
    int index = findIndexById(id);
    
    if (index != -1) {
        cout << "Thong tin hien tai: BN " << patientIds[index] << " - " << totalAmounts[index] << " - " << statuses[index] << "\n";
        
        cout << "Nhap ngay lap moi (de trong de giu nguyen): ";
        string date = Utils::readString();
        if (!date.empty()) Utils::copyText(dates[index], date, Utils::MAX_TEXT_LENGTH);
        
        cout << "Nhap tong tien moi (nhap -1 de giu nguyen): ";
        long long amount = Utils::readLongLong();
        if (amount != -1) totalAmounts[index] = amount;
        
        cout << "Nhap trang thai moi (Paid/Unpaid) (de trong de giu nguyen): ";
        string status = Utils::readString();
        if (!status.empty()) Utils::copyText(statuses[index], status, Utils::MAX_TEXT_LENGTH);
        
        saveToFile();
        cout << "Cap nhat thanh cong!\n";
        Utils::pauseScreen();
        return;
    }
    cout << "Khong tim thay hoa don voi ma " << id << "\n";
    Utils::pauseScreen();
}

void InvoiceManager::deleteInvoice() {
    Utils::clearScreen();
    cout << "--- XOA HOA DON ---\n";
    cout << "Nhap ma hoa don can xoa: ";
    string id = Utils::readString();
    int index = findIndexById(id);
    
    if (index != -1) {
        removeAt(index);
        saveToFile();
        cout << "Xoa hoa don thanh cong!\n";
        Utils::pauseScreen();
        return;
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
    for (int i = 0; i < invoiceCount; ++i) {
        if (Utils::containsText(ids[i], query) || Utils::containsText(patientIds[i], query)) {
            cout << ids[i] << " - BN: " << patientIds[i] << " - Ngay: " << dates[i]
                 << " - Tong tien: " << totalAmounts[i] << " - Trang thai: " << statuses[i] << "\n";
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay ket qua phu hop.\n";
    Utils::pauseScreen();
}

void InvoiceManager::displayAllInvoices() {
    Utils::clearScreen();
    cout << "--- DANH SACH HOA DON ---\n";
    if (invoiceCount == 0) {
        cout << "Chua co du lieu.\n";
    } else {
        for (int i = 0; i < invoiceCount; ++i) {
            cout << ids[i] << " | BN: " << patientIds[i] << " | Ngay: " << dates[i]
                 << " | Tong tien: " << totalAmounts[i] << " | Trang thai: " << statuses[i] << "\n";
        }
    }
    Utils::pauseScreen();
}

long long InvoiceManager::calculateTotalRevenue() {
    long long total = 0;
    for (int i = 0; i < invoiceCount; ++i) {
        if (strcmp(statuses[i], "Paid") == 0) {
            total += totalAmounts[i];
        }
    }
    return total;
}
