#ifndef PATIENT_MANAGER_H
#define PATIENT_MANAGER_H

#include "Utils.h"
#include <string>

using namespace std;

class PatientManager {
private:
    int patientCount;
    char ids[Utils::MAX_RECORDS][Utils::MAX_ID_LENGTH];
    char names[Utils::MAX_RECORDS][Utils::MAX_TEXT_LENGTH];
    int ages[Utils::MAX_RECORDS];
    char genders[Utils::MAX_RECORDS][Utils::MAX_TEXT_LENGTH];
    char phones[Utils::MAX_RECORDS][Utils::MAX_TEXT_LENGTH];
    char addresses[Utils::MAX_RECORDS][Utils::MAX_TEXT_LENGTH];
    char medicalHistories[Utils::MAX_RECORDS][Utils::MAX_LONG_TEXT_LENGTH];
    string filename;

    void loadFromFile();
    void saveToFile();
    int findIndexById(const string& id);
    void removeAt(int index);

public:
    PatientManager();
    ~PatientManager();

    void addPatient();
    void editPatient();
    void deletePatient();
    void searchPatient();
    void displayAllPatients();
    
    int getPatientIndexById(const string& id);
    bool patientExists(const string& id);
};

#endif // PATIENT_MANAGER_H
