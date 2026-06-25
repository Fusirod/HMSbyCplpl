#ifndef TREATMENT_MANAGER_H
#define TREATMENT_MANAGER_H

#include "Utils.h"
#include <string>

using namespace std;

class TreatmentManager {
private:
    int treatmentCount;
    char ids[Utils::MAX_RECORDS][Utils::MAX_ID_LENGTH];
    char patientIds[Utils::MAX_RECORDS][Utils::MAX_ID_LENGTH];
    char doctorIds[Utils::MAX_RECORDS][Utils::MAX_ID_LENGTH];
    char diagnoses[Utils::MAX_RECORDS][Utils::MAX_LONG_TEXT_LENGTH];
    char prescriptions[Utils::MAX_RECORDS][Utils::MAX_LONG_TEXT_LENGTH];
    char notes[Utils::MAX_RECORDS][Utils::MAX_LONG_TEXT_LENGTH];
    string filename;

    void loadFromFile();
    void saveToFile();
    int findIndexById(const string& id);
    void removeAt(int index);

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
