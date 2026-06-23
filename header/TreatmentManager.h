#ifndef TREATMENT_MANAGER_H
#define TREATMENT_MANAGER_H

#include "models.h"
#include <vector>
#include <string>

using namespace std;

struct TreatmentManager {
private:
    vector<Treatment> treatments;
    string filename;

    void loadFromFile();
    void saveToFile();

public:
    TreatmentManager();
    ~TreatmentManager();

    void addTreatment();
    void editTreatment();
    void deleteTreatment();
    void searchTreatment();
    void displayAllTreatments();
};

#endif // TREATMENT_MANAGER_H
