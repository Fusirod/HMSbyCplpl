#ifndef APP_H
#define APP_H

#include "SystemManager.h"
#include "EmployeeManager.h"
#include "PatientManager.h"
#include "AppointmentManager.h"
#include "TreatmentManager.h"
#include "InventoryManager.h"
#include "InvoiceManager.h"

struct App {
private:
    EmployeeManager empManager;
    PatientManager patManager;
    AppointmentManager apptManager;
    TreatmentManager treatManager;
    InventoryManager invManager;
    InvoiceManager invcManager;
    SystemManager sysManager;

    void mainMenu();
    void employeeMenu();
    void patientMenu();
    void appointmentMenu();
    void treatmentMenu();
    void inventoryMenu();
    void invoiceMenu();
    void reportMenu();
    void systemMenu();

public:
    App();
    ~App();

    void run();
};

#endif // APP_H
