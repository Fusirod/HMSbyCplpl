#ifndef APPOINTMENT_MANAGER_H
#define APPOINTMENT_MANAGER_H

#include "models.h"
#include <vector>
#include <string>

using namespace std;

struct AppointmentManager {
private:
    vector<Appointment> appointments;
    string filename;

    void loadFromFile();
    void saveToFile();

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
