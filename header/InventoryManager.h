#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "Utils.h"
#include <string>

using namespace std;

class InventoryManager {
private:
    int itemCount;
    char ids[Utils::MAX_RECORDS][Utils::MAX_ID_LENGTH];
    char names[Utils::MAX_RECORDS][Utils::MAX_TEXT_LENGTH];
    char categories[Utils::MAX_RECORDS][Utils::MAX_TEXT_LENGTH];
    int quantities[Utils::MAX_RECORDS];
    long long prices[Utils::MAX_RECORDS];
    string filename;

    void loadFromFile();
    void saveToFile();
    int findIndexById(const string& id);
    void removeAt(int index);

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
