#ifndef MODELS_H
#define MODELS_H

#include <string>

using namespace std;

// 1. Quản lý Nhân viên (Employees - bao gồm Bác sĩ, Y tá, Quản lý)
struct Employee {
    string id;
    string name;
    string role; // "Doctor", "Nurse", "Admin"
    string phone;
    string department;
    string username;
    string password;
};

// 2. Quản lý Bệnh nhân (Patients)
struct Patient {
    string id;
    string name;
    int age;
    string gender;
    string phone;
    string address;
    string medicalHistory;
};

// 3. Quản lý Lịch khám (Appointments)
struct Appointment {
    string id;
    string patientId;
    string doctorId;
    string date; // Format: DD/MM/YYYY
    string time; // Format: HH:MM
    string status; // "Scheduled", "Completed", "Cancelled"
};

// 4. Quản lý Điều trị (Treatments)
struct Treatment {
    string id;
    string patientId;
    string doctorId;
    string diagnosis;
    string prescription; 
    string notes;
};

// 5. Quản lý Thuốc và Vật tư (Inventory)
struct InventoryItem {
    string id;
    string name;
    string category; // "Medicine", "Equipment"
    int quantity;
    long long price;
};

// 6. Quản lý Hóa đơn và Thanh toán (Invoices)
struct Invoice {
    string id;
    string patientId;
    string date;
    long long totalAmount;
    string status; // "Unpaid", "Paid"
};

#endif // MODELS_H
