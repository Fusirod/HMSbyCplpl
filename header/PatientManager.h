#ifndef PATIENT_MANAGER_H
#define PATIENT_MANAGER_H

#include "models.h"
#include <vector>
#include <string>

using namespace std;

struct PatientManager {
private:
    vector<Patient> patients;
    string filename;

    void loadFromFile();
    void saveToFile();

public:
    PatientManager();
    ~PatientManager();

    void addPatient();
    void editPatient();
    void deletePatient();
    void searchPatient();
    void displayAllPatients();
    
    // For other modules
    Patient* getPatientById(const string& id);
    bool patientExists(const string& id);
};

#endif // PATIENT_MANAGER_H
