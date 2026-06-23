#include "InventoryManager.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

InventoryManager::InventoryManager() {
    filename = "data/inventory.txt";
    loadFromFile();
}

InventoryManager::~InventoryManager() {
    saveToFile();
}

void InventoryManager::loadFromFile() {
    items.clear();
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, name, category, qtyStr, priceStr;
        
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, category, '|');
        getline(ss, qtyStr, '|');
        getline(ss, priceStr, '|');

        InventoryItem item;
        item.id = id;
        item.name = name;
        item.category = category;
        item.quantity = stoi(qtyStr);
        item.price = stod(priceStr);
        items.push_back(item);
    }
    file.close();
}

void InventoryManager::saveToFile() {
    ofstream file(filename);
    if (!file.is_open()) return;

    for (const auto& item : items) {
        file << item.id << "|" << item.name << "|" << item.category << "|" 
             << item.quantity << "|" << item.price << "\n";
    }
    file.close();
}

void InventoryManager::addItem() {
    Utils::clearScreen();
    cout << "--- THEM THUOC / VAT TU ---\n";
    InventoryItem item;
    item.id = Utils::generateId("VT", items.size());
    
    cout << "Ma vat tu duoc cap: " << item.id << "\n";
    cout << "Nhap ten: ";
    item.name = Utils::readString();
    
    cout << "Nhap danh muc (Medicine/Equipment): ";
    item.category = Utils::readString();
    
    cout << "Nhap so luong: ";
    item.quantity = Utils::readInt();
    
    cout << "Nhap don gia: ";
    item.price = Utils::readDouble();
    
    items.push_back(item);
    saveToFile();
    cout << "Them vat tu thanh cong!\n";
    Utils::pauseScreen();
}

void InventoryManager::editItem() {
    Utils::clearScreen();
    cout << "--- SUA THONG TIN VAT TU ---\n";
    cout << "Nhap ma vat tu can sua: ";
    string id = Utils::readString();
    
    for (auto& item : items) {
        if (item.id == id) {
            cout << "Thong tin hien tai: " << item.name << " (" << item.quantity << " " << item.category << ")\n";
            
            cout << "Nhap ten moi (de trong de giu nguyen): ";
            string name = Utils::readString();
            if (!name.empty()) item.name = name;
            
            cout << "Nhap danh muc moi (de trong de giu nguyen): ";
            string cat = Utils::readString();
            if (!cat.empty()) item.category = cat;
            
            cout << "Nhap so luong moi (nhap -1 de giu nguyen): ";
            int qty = Utils::readInt();
            if (qty != -1) item.quantity = qty;
            
            cout << "Nhap don gia moi (nhap -1 de giu nguyen): ";
            double price = Utils::readDouble();
            if (price != -1) item.price = price;
            
            saveToFile();
            cout << "Cap nhat thanh cong!\n";
            Utils::pauseScreen();
            return;
        }
    }
    cout << "Khong tim thay vat tu voi ma " << id << "\n";
    Utils::pauseScreen();
}

void InventoryManager::deleteItem() {
    Utils::clearScreen();
    cout << "--- XOA VAT TU ---\n";
    cout << "Nhap ma vat tu can xoa: ";
    string id = Utils::readString();
    
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->id == id) {
            items.erase(it);
            saveToFile();
            cout << "Xoa vat tu thanh cong!\n";
            Utils::pauseScreen();
            return;
        }
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
    for (const auto& item : items) {
        if (item.id.find(query) != string::npos || item.name.find(query) != string::npos) {
            cout << item.id << " - " << item.name << " - Danh muc: " << item.category 
                 << " - So luong: " << item.quantity << " - Don gia: " << item.price << "\n";
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay ket qua phu hop.\n";
    Utils::pauseScreen();
}

void InventoryManager::displayAllItems() {
    Utils::clearScreen();
    cout << "--- KHO THUOC & VAT TU ---\n";
    if (items.empty()) {
        cout << "Chua co du lieu.\n";
    } else {
        for (const auto& item : items) {
            cout << item.id << " | " << item.name << " | Danh muc: " << item.category 
                 << " | So luong: " << item.quantity << " | Don gia: " << item.price << "\n";
        }
    }
    Utils::pauseScreen();
}
