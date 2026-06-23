#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "models.h"
#include <vector>
#include <string>

using namespace std;

struct InventoryManager {
private:
    vector<InventoryItem> items;
    string filename;

    void loadFromFile();
    void saveToFile();

public:
    InventoryManager();
    ~InventoryManager();

    void addItem();
    void editItem();
    void deleteItem();
    void searchItem();
    void displayAllItems();
};

#endif // INVENTORY_MANAGER_H
