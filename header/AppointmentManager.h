#ifndef APPOINTMENT_MANAGER_H
#define APPOINTMENT_MANAGER_H

#include "Utils.h"
#include <string>

using namespace std;

class AppointmentManager {
private:
    int appointmentCount;
    char ids[Utils::MAX_RECORDS][Utils::MAX_ID_LENGTH];
    char patientIds[Utils::MAX_RECORDS][Utils::MAX_ID_LENGTH];
    char doctorIds[Utils::MAX_RECORDS][Utils::MAX_ID_LENGTH];
    char dates[Utils::MAX_RECORDS][Utils::MAX_TEXT_LENGTH];
    char times[Utils::MAX_RECORDS][Utils::MAX_TEXT_LENGTH];
    char statuses[Utils::MAX_RECORDS][Utils::MAX_TEXT_LENGTH];
    string filename;

    void loadFromFile();
    void saveToFile();
    int findIndexById(const string& id);
    void removeAt(int index);

public:
    AppointmentManager();
    ~AppointmentManager();

    void addAppointment();
    void editAppointment();
    void deleteAppointment();
    void searchAppointment();
    void displayAllAppointments();
};

#endif // APPOINTMENT_MANAGER_H
