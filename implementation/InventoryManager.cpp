#include "InventoryManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

InventoryManager::InventoryManager() {
    filename = "data/inventory.txt";
    itemCount = 0;
    loadFromFile();
}

InventoryManager::~InventoryManager() {
    saveToFile();
}

int InventoryManager::findIndexById(const string& id) {
    for (int i = 0; i < itemCount; ++i) {
        if (id == ids[i]) return i;
    }
    return -1;
}

void InventoryManager::removeAt(int index) {
    for (int i = index; i < itemCount - 1; ++i) {
        strcpy(ids[i], ids[i + 1]);
        strcpy(names[i], names[i + 1]);
        strcpy(categories[i], categories[i + 1]);
        quantities[i] = quantities[i + 1];
        prices[i] = prices[i + 1];
    }
    --itemCount;
}

void InventoryManager::loadFromFile() {
    itemCount = 0;
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (itemCount < Utils::MAX_RECORDS && getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, name, category, qtyStr, priceStr;
        
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, category, '|');
        getline(ss, qtyStr, '|');
        getline(ss, priceStr, '|');

        Utils::copyText(ids[itemCount], id, Utils::MAX_ID_LENGTH);
        Utils::copyText(names[itemCount], name, Utils::MAX_TEXT_LENGTH);
        Utils::copyText(categories[itemCount], category, Utils::MAX_TEXT_LENGTH);
        quantities[itemCount] = stoi(qtyStr);
        prices[itemCount] = stoll(priceStr);
        ++itemCount;
    }
    file.close();
}

void InventoryManager::saveToFile() {
    ofstream file(filename);
    if (!file.is_open()) return;

    for (int i = 0; i < itemCount; ++i) {
        file << ids[i] << "|" << names[i] << "|" << categories[i] << "|"
             << quantities[i] << "|" << prices[i] << "\n";
    }
    file.close();
}

void InventoryManager::addItem() {
    Utils::clearScreen();
    cout << "--- THEM THUOC / VAT TU ---\n";
    if (itemCount >= Utils::MAX_RECORDS) {
        cout << "Danh sach vat tu da day!\n";
        Utils::pauseScreen();
        return;
    }

    string generatedId = Utils::generateId("VT", itemCount);
    Utils::copyText(ids[itemCount], generatedId, Utils::MAX_ID_LENGTH);
    
    cout << "Ma vat tu duoc cap: " << ids[itemCount] << "\n";
    cout << "Nhap ten: ";
    Utils::copyText(names[itemCount], Utils::readString(), Utils::MAX_TEXT_LENGTH);
    
    cout << "Nhap danh muc (Medicine/Equipment): ";
    Utils::copyText(categories[itemCount], Utils::readString(), Utils::MAX_TEXT_LENGTH);
    
    cout << "Nhap so luong: ";
    quantities[itemCount] = Utils::readInt();
    
    cout << "Nhap don gia: ";
    prices[itemCount] = Utils::readLongLong();
    
    ++itemCount;
    saveToFile();
    cout << "Them vat tu thanh cong!\n";
    Utils::pauseScreen();
}

void InventoryManager::editItem() {
    Utils::clearScreen();
    cout << "--- SUA THONG TIN VAT TU ---\n";
    cout << "Nhap ma vat tu can sua: ";
    string id = Utils::readString();
    int index = findIndexById(id);
    
    if (index != -1) {
        cout << "Thong tin hien tai: " << names[index] << " (" << quantities[index] << " " << categories[index] << ")\n";
        
        cout << "Nhap ten moi (de trong de giu nguyen): ";
        string name = Utils::readString();
        if (!name.empty()) Utils::copyText(names[index], name, Utils::MAX_TEXT_LENGTH);
        
        cout << "Nhap danh muc moi (de trong de giu nguyen): ";
        string cat = Utils::readString();
        if (!cat.empty()) Utils::copyText(categories[index], cat, Utils::MAX_TEXT_LENGTH);
        
        cout << "Nhap so luong moi (nhap -1 de giu nguyen): ";
        int qty = Utils::readInt();
        if (qty != -1) quantities[index] = qty;
        
        cout << "Nhap don gia moi (nhap -1 de giu nguyen): ";
        long long price = Utils::readLongLong();
        if (price != -1) prices[index] = price;
        
        saveToFile();
        cout << "Cap nhat thanh cong!\n";
        Utils::pauseScreen();
        return;
    }
    cout << "Khong tim thay vat tu voi ma " << id << "\n";
    Utils::pauseScreen();
}

void InventoryManager::deleteItem() {
    Utils::clearScreen();
    cout << "--- XOA VAT TU ---\n";
    cout << "Nhap ma vat tu can xoa: ";
    string id = Utils::readString();
    int index = findIndexById(id);
    
    if (index != -1) {
        removeAt(index);
        saveToFile();
        cout << "Xoa vat tu thanh cong!\n";
        Utils::pauseScreen();
        return;
    }
    cout << "Khong tim thay vat tu voi ma " << id << "\n";
    Utils::pauseScreen();
}

void InventoryManager::searchItem() {
    Utils::clearScreen();
    cout << "--- TIM KIEM VAT TU ---\n";
    cout << "Nhap ten hoac ma vat tu: ";
    string query = Utils::readString();
    
    bool found = false;
    for (int i = 0; i < itemCount; ++i) {
        if (Utils::containsText(ids[i], query) || Utils::containsText(names[i], query)) {
            cout << ids[i] << " - " << names[i] << " - Danh muc: " << categories[i]
                 << " - So luong: " << quantities[i] << " - Don gia: " << prices[i] << "\n";
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay ket qua phu hop.\n";
    Utils::pauseScreen();
}

void InventoryManager::displayAllItems() {
    Utils::clearScreen();
    cout << "--- KHO THUOC & VAT TU ---\n";
    if (itemCount == 0) {
        cout << "Chua co du lieu.\n";
    } else {
        for (int i = 0; i < itemCount; ++i) {
            cout << ids[i] << " | " << names[i] << " | Danh muc: " << categories[i]
                 << " | So luong: " << quantities[i] << " | Don gia: " << prices[i] << "\n";
        }
    }
    Utils::pauseScreen();
}
