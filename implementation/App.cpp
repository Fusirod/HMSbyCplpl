#include "App.h"
#include "Utils.h"
#include <iostream>

using namespace std;

App::App() : sysManager(&empManager) {
}

App::~App() {
}

void App::run() {
    while (true) {
        if (!sysManager.isLoggedIn()) {
            Utils::clearScreen();
            cout << "1. Dang nhap\n";
            cout << "0. Thoat chuong trinh\n";
            cout << "Chon: ";
            int choice = Utils::readInt();
            if (choice == 1) {
                sysManager.login();
            } else if (choice == 0) {
                break;
            }
        } else {
            mainMenu();
        }
    }
}

void App::mainMenu() {
    while (sysManager.isLoggedIn()) {
        Utils::clearScreen();
        cout << "===== MENU CHINH =====\n";
        cout << "1. Quan ly Nhan vien\n";
        cout << "2. Quan ly Benh nhan\n";
        cout << "3. Quan ly Lich kham\n";
        cout << "4. Quan ly Dieu tri\n";
        cout << "5. Quan ly Thuoc & Vat tu\n";
        cout << "6. Quan ly Hoa don\n";
        cout << "7. Bao cao & Thong ke\n";
        cout << "8. Quan tri He thong\n";
        cout << "0. Dang xuat\n";
        cout << "======================\n";
        cout << "Chon tac vu (0-8): ";
        int choice = Utils::readInt();

        switch (choice) {
            case 1: employeeMenu(); break;
            case 2: patientMenu(); break;
            case 3: appointmentMenu(); break;
            case 4: treatmentMenu(); break;
            case 5: inventoryMenu(); break;
            case 6: invoiceMenu(); break;
            case 7: reportMenu(); break;
            case 8: systemMenu(); break;
            case 0: sysManager.logout(); return;
            default: break;
        }
    }
}

void App::employeeMenu() {
    while (true) {
        Utils::clearScreen();
        cout << "--- QUAN LY NHAN VIEN ---\n";
        cout << "1. Them nhan vien\n";
        cout << "2. Sua thong tin\n";
        cout << "3. Xoa nhan vien\n";
        cout << "4. Tim kiem\n";
        cout << "5. Xem danh sach\n";
        cout << "0. Quay lai\n";
        cout << "Chon tac vu: ";
        int choice = Utils::readInt();
        switch (choice) {
            case 1: empManager.addEmployee(); break;
            case 2: empManager.editEmployee(); break;
            case 3: empManager.deleteEmployee(); break;
            case 4: empManager.searchEmployee(); break;
            case 5: empManager.displayAllEmployees(); break;
            case 0: return;
        }
    }
}

void App::patientMenu() {
    while (true) {
        Utils::clearScreen();
        cout << "--- QUAN LY BENH NHAN ---\n";
        cout << "1. Them benh nhan\n";
        cout << "2. Sua thong tin\n";
        cout << "3. Xoa benh nhan\n";
        cout << "4. Tim kiem\n";
        cout << "5. Xem danh sach\n";
        cout << "0. Quay lai\n";
        cout << "Chon tac vu: ";
        int choice = Utils::readInt();
        switch (choice) {
            case 1: patManager.addPatient(); break;
            case 2: patManager.editPatient(); break;
            case 3: patManager.deletePatient(); break;
            case 4: patManager.searchPatient(); break;
            case 5: patManager.displayAllPatients(); break;
            case 0: return;
        }
    }
}

void App::appointmentMenu() {
    while (true) {
        Utils::clearScreen();
        cout << "--- QUAN LY LICH KHAM ---\n";
        cout << "1. Dat lich kham\n";
        cout << "2. Sua lich kham\n";
        cout << "3. Huy lich kham (Xoa)\n";
        cout << "4. Tim kiem lich kham\n";
        cout << "5. Xem tat ca lich kham\n";
        cout << "0. Quay lai\n";
        cout << "Chon tac vu: ";
        int choice = Utils::readInt();
        switch (choice) {
            case 1: apptManager.addAppointment(); break;
            case 2: apptManager.editAppointment(); break;
            case 3: apptManager.deleteAppointment(); break;
            case 4: apptManager.searchAppointment(); break;
            case 5: apptManager.displayAllAppointments(); break;
            case 0: return;
        }
    }
}

void App::treatmentMenu() {
    while (true) {
        Utils::clearScreen();
        cout << "--- QUAN LY DIEU TRI ---\n";
        cout << "1. Them ho so dieu tri\n";
        cout << "2. Sua ho so dieu tri\n";
        cout << "3. Xoa ho so dieu tri\n";
        cout << "4. Tim kiem ho so dieu tri\n";
        cout << "5. Xem tat ca ho so\n";
        cout << "0. Quay lai\n";
        cout << "Chon tac vu: ";
        int choice = Utils::readInt();
        switch (choice) {
            case 1: treatManager.addTreatment(); break;
            case 2: treatManager.editTreatment(); break;
            case 3: treatManager.deleteTreatment(); break;
            case 4: treatManager.searchTreatment(); break;
            case 5: treatManager.displayAllTreatments(); break;
            case 0: return;
        }
    }
}

void App::inventoryMenu() {
    while (true) {
        Utils::clearScreen();
        cout << "--- QUAN LY KHO ---\n";
        cout << "1. Nhap thuoc/vat tu moi\n";
        cout << "2. Sua thong tin\n";
        cout << "3. Xoa vat tu\n";
        cout << "4. Tim kiem\n";
        cout << "5. Xem danh sach kho\n";
        cout << "0. Quay lai\n";
        cout << "Chon tac vu: ";
        int choice = Utils::readInt();
        switch (choice) {
            case 1: invManager.addItem(); break;
            case 2: invManager.editItem(); break;
            case 3: invManager.deleteItem(); break;
            case 4: invManager.searchItem(); break;
            case 5: invManager.displayAllItems(); break;
            case 0: return;
        }
    }
}

void App::invoiceMenu() {
    while (true) {
        Utils::clearScreen();
        cout << "--- QUAN LY HOA DON ---\n";
        cout << "1. Lap hoa don moi\n";
        cout << "2. Sua hoa don\n";
        cout << "3. Xoa hoa don\n";
        cout << "4. Tim kiem hoa don\n";
        cout << "5. Xem tat ca hoa don\n";
        cout << "0. Quay lai\n";
        cout << "Chon tac vu: ";
        int choice = Utils::readInt();
        switch (choice) {
            case 1: invcManager.addInvoice(); break;
            case 2: invcManager.editInvoice(); break;
            case 3: invcManager.deleteInvoice(); break;
            case 4: invcManager.searchInvoice(); break;
            case 5: invcManager.displayAllInvoices(); break;
            case 0: return;
        }
    }
}

void App::reportMenu() {
    Utils::clearScreen();
    cout << "--- BAO CAO & THONG KE ---\n";
    cout << "Tong doanh thu da thu (Paid): " << invcManager.calculateTotalRevenue() << " VND\n";
    Utils::pauseScreen();
}

void App::systemMenu() {
    while (true) {
        Utils::clearScreen();
        cout << "--- QUAN TRI HE THONG ---\n";
        cout << "1. Thay doi mat khau\n";
        cout << "2. Thay doi giao dien (mau sac)\n";
        cout << "0. Quay lai\n";
        cout << "Chon tac vu: ";
        int choice = Utils::readInt();
        switch (choice) {
            case 1: sysManager.changePassword(); break;
            case 2: sysManager.changeTheme(); break;
            case 0: return;
        }
    }
}
