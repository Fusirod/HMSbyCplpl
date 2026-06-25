#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>

using namespace std;

const int MAX = 1000;
const int LEN_ID = 20;
const int LEN_NAME = 100;
const int LEN_TEXT = 200;
const char FILE_NAME[] = "data/patients.txt";

void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pauseScreen() {
    cout << "\nNhan Enter de tiep tuc...";
    cin.get();
}

void copyText(char destination[], const char source[], int maxLength) {
    strncpy(destination, source, maxLength - 1);
    destination[maxLength - 1] = '\0';
}

void readLine(char value[], int maxLength) {
    cin.getline(value, maxLength);
}

int findPatient(char patientIds[][LEN_ID], int n, const char id[]) {
    for (int i = 0; i < n; ++i) {
        if (strcmp(patientIds[i], id) == 0) {
            return i;
        }
    }
    return -1;
}

void readFile(char patientIds[][LEN_ID], char names[][LEN_NAME], int ages[],
              char genders[][LEN_TEXT], char phones[][LEN_TEXT],
              char diagnoses[][LEN_TEXT], long long fees[], int &n) {
    n = 0;
    ifstream file(FILE_NAME);
    if (!file.is_open()) {
        return;
    }

    while (n < MAX && file.getline(patientIds[n], LEN_ID, '|')) {
        file.getline(names[n], LEN_NAME, '|');
        file >> ages[n];
        file.ignore(1, '|');
        file.getline(genders[n], LEN_TEXT, '|');
        file.getline(phones[n], LEN_TEXT, '|');
        file.getline(diagnoses[n], LEN_TEXT, '|');
        file >> fees[n];
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        ++n;
    }

    file.close();
}

void writeFile(char patientIds[][LEN_ID], char names[][LEN_NAME], int ages[],
               char genders[][LEN_TEXT], char phones[][LEN_TEXT],
               char diagnoses[][LEN_TEXT], long long fees[], int n) {
    ofstream file(FILE_NAME);
    if (!file.is_open()) {
        cout << "Khong the ghi file du lieu!\n";
        return;
    }

    for (int i = 0; i < n; ++i) {
        file << patientIds[i] << "|" << names[i] << "|" << ages[i] << "|"
             << genders[i] << "|" << phones[i] << "|" << diagnoses[i] << "|"
             << fees[i] << "\n";
    }

    file.close();
}

void addPatient(char patientIds[][LEN_ID], char names[][LEN_NAME], int ages[],
                char genders[][LEN_TEXT], char phones[][LEN_TEXT],
                char diagnoses[][LEN_TEXT], long long fees[], int &n) {
    if (n >= MAX) {
        cout << "Danh sach da day!\n";
        return;
    }

    clearInput();
    cout << "Nhap ma benh nhan: ";
    readLine(patientIds[n], LEN_ID);

    if (findPatient(patientIds, n, patientIds[n]) != -1) {
        cout << "Ma benh nhan da ton tai!\n";
        return;
    }

    cout << "Nhap ho ten: ";
    readLine(names[n], LEN_NAME);

    cout << "Nhap tuoi: ";
    cin >> ages[n];
    clearInput();

    cout << "Nhap gioi tinh: ";
    readLine(genders[n], LEN_TEXT);

    cout << "Nhap so dien thoai: ";
    readLine(phones[n], LEN_TEXT);

    cout << "Nhap chan doan: ";
    readLine(diagnoses[n], LEN_TEXT);

    cout << "Nhap phi kham: ";
    cin >> fees[n];

    ++n;
    cout << "Them benh nhan thanh cong!\n";
}

void displayPatients(char patientIds[][LEN_ID], char names[][LEN_NAME], int ages[],
                     char genders[][LEN_TEXT], char phones[][LEN_TEXT],
                     char diagnoses[][LEN_TEXT], long long fees[], int n) {
    if (n == 0) {
        cout << "Chua co du lieu.\n";
        return;
    }

    cout << "===== DANH SACH BENH NHAN =====\n";
    for (int i = 0; i < n; ++i) {
        cout << i + 1 << ". Ma: " << patientIds[i]
             << " | Ten: " << names[i]
             << " | Tuoi: " << ages[i]
             << " | Gioi tinh: " << genders[i]
             << " | SDT: " << phones[i]
             << " | Chan doan: " << diagnoses[i]
             << " | Phi kham: " << fees[i] << "\n";
    }
}

void searchPatient(char patientIds[][LEN_ID], char names[][LEN_NAME], int ages[],
                   char genders[][LEN_TEXT], char phones[][LEN_TEXT],
                   char diagnoses[][LEN_TEXT], long long fees[], int n) {
    char keyword[LEN_NAME];
    clearInput();
    cout << "Nhap ma hoac ten benh nhan can tim: ";
    readLine(keyword, LEN_NAME);

    bool found = false;
    for (int i = 0; i < n; ++i) {
        if (strstr(patientIds[i], keyword) != nullptr || strstr(names[i], keyword) != nullptr) {
            cout << "Ma: " << patientIds[i]
                 << " | Ten: " << names[i]
                 << " | Tuoi: " << ages[i]
                 << " | Gioi tinh: " << genders[i]
                 << " | SDT: " << phones[i]
                 << " | Chan doan: " << diagnoses[i]
                 << " | Phi kham: " << fees[i] << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "Khong tim thay benh nhan phu hop.\n";
    }
}

void updatePatient(char patientIds[][LEN_ID], char names[][LEN_NAME], int ages[],
                   char genders[][LEN_TEXT], char phones[][LEN_TEXT],
                   char diagnoses[][LEN_TEXT], long long fees[], int n) {
    char id[LEN_ID];
    clearInput();
    cout << "Nhap ma benh nhan can cap nhat: ";
    readLine(id, LEN_ID);

    int index = findPatient(patientIds, n, id);
    if (index == -1) {
        cout << "Khong tim thay benh nhan.\n";
        return;
    }

    cout << "Nhap ho ten moi: ";
    readLine(names[index], LEN_NAME);

    cout << "Nhap tuoi moi: ";
    cin >> ages[index];
    clearInput();

    cout << "Nhap gioi tinh moi: ";
    readLine(genders[index], LEN_TEXT);

    cout << "Nhap so dien thoai moi: ";
    readLine(phones[index], LEN_TEXT);

    cout << "Nhap chan doan moi: ";
    readLine(diagnoses[index], LEN_TEXT);

    cout << "Nhap phi kham moi: ";
    cin >> fees[index];

    cout << "Cap nhat thanh cong!\n";
}

void deletePatient(char patientIds[][LEN_ID], char names[][LEN_NAME], int ages[],
                   char genders[][LEN_TEXT], char phones[][LEN_TEXT],
                   char diagnoses[][LEN_TEXT], long long fees[], int &n) {
    char id[LEN_ID];
    clearInput();
    cout << "Nhap ma benh nhan can xoa: ";
    readLine(id, LEN_ID);

    int index = findPatient(patientIds, n, id);
    if (index == -1) {
        cout << "Khong tim thay benh nhan.\n";
        return;
    }

    for (int i = index; i < n - 1; ++i) {
        copyText(patientIds[i], patientIds[i + 1], LEN_ID);
        copyText(names[i], names[i + 1], LEN_NAME);
        ages[i] = ages[i + 1];
        copyText(genders[i], genders[i + 1], LEN_TEXT);
        copyText(phones[i], phones[i + 1], LEN_TEXT);
        copyText(diagnoses[i], diagnoses[i + 1], LEN_TEXT);
        fees[i] = fees[i + 1];
    }

    --n;
    cout << "Xoa thanh cong!\n";
}

void swapPatient(int a, int b, char patientIds[][LEN_ID], char names[][LEN_NAME], int ages[],
                 char genders[][LEN_TEXT], char phones[][LEN_TEXT],
                 char diagnoses[][LEN_TEXT], long long fees[]) {
    char tmpId[LEN_ID], tmpName[LEN_NAME], tmpGender[LEN_TEXT], tmpPhone[LEN_TEXT], tmpDiagnosis[LEN_TEXT];
    int tmpAge = ages[a];
    long long tmpFee = fees[a];

    copyText(tmpId, patientIds[a], LEN_ID);
    copyText(tmpName, names[a], LEN_NAME);
    copyText(tmpGender, genders[a], LEN_TEXT);
    copyText(tmpPhone, phones[a], LEN_TEXT);
    copyText(tmpDiagnosis, diagnoses[a], LEN_TEXT);

    copyText(patientIds[a], patientIds[b], LEN_ID);
    copyText(names[a], names[b], LEN_NAME);
    ages[a] = ages[b];
    copyText(genders[a], genders[b], LEN_TEXT);
    copyText(phones[a], phones[b], LEN_TEXT);
    copyText(diagnoses[a], diagnoses[b], LEN_TEXT);
    fees[a] = fees[b];

    copyText(patientIds[b], tmpId, LEN_ID);
    copyText(names[b], tmpName, LEN_NAME);
    ages[b] = tmpAge;
    copyText(genders[b], tmpGender, LEN_TEXT);
    copyText(phones[b], tmpPhone, LEN_TEXT);
    copyText(diagnoses[b], tmpDiagnosis, LEN_TEXT);
    fees[b] = tmpFee;
}

void sortPatientsByName(char patientIds[][LEN_ID], char names[][LEN_NAME], int ages[],
                        char genders[][LEN_TEXT], char phones[][LEN_TEXT],
                        char diagnoses[][LEN_TEXT], long long fees[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (strcmp(names[i], names[j]) > 0) {
                swapPatient(i, j, patientIds, names, ages, genders, phones, diagnoses, fees);
            }
        }
    }
    cout << "Sap xep theo ten thanh cong!\n";
}

void showMenu() {
    cout << "\n===== QUAN LY BENH VIEN =====\n";
    cout << "1. Them benh nhan\n";
    cout << "2. Hien thi danh sach\n";
    cout << "3. Tim kiem benh nhan\n";
    cout << "4. Cap nhat benh nhan\n";
    cout << "5. Xoa benh nhan\n";
    cout << "6. Sap xep theo ten\n";
    cout << "0. Luu va thoat\n";
    cout << "Chon chuc nang: ";
}

int main() {
    char patientIds[MAX][LEN_ID];
    char names[MAX][LEN_NAME];
    int ages[MAX];
    char genders[MAX][LEN_TEXT];
    char phones[MAX][LEN_TEXT];
    char diagnoses[MAX][LEN_TEXT];
    long long fees[MAX];
    int n = 0;
    int choice;

    readFile(patientIds, names, ages, genders, phones, diagnoses, fees, n);

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addPatient(patientIds, names, ages, genders, phones, diagnoses, fees, n);
                break;
            case 2:
                displayPatients(patientIds, names, ages, genders, phones, diagnoses, fees, n);
                break;
            case 3:
                searchPatient(patientIds, names, ages, genders, phones, diagnoses, fees, n);
                break;
            case 4:
                updatePatient(patientIds, names, ages, genders, phones, diagnoses, fees, n);
                break;
            case 5:
                deletePatient(patientIds, names, ages, genders, phones, diagnoses, fees, n);
                break;
            case 6:
                sortPatientsByName(patientIds, names, ages, genders, phones, diagnoses, fees, n);
                break;
            case 0:
                writeFile(patientIds, names, ages, genders, phones, diagnoses, fees, n);
                cout << "Da luu du lieu. Tam biet!\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
                break;
        }

        if (choice != 0) {
            clearInput();
            pauseScreen();
        }
    } while (choice != 0);

    return 0;
}
