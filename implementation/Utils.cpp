#include "Utils.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <sstream>
#include <iomanip>
#include <cstring>

using namespace std;

namespace Utils {
    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void pauseScreen() {
        cout << "\nNhan Enter de tiep tuc...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // if user already pressed enter during a readString, this might just pass, 
        // which is fine or we might need cin.get()
        cin.get();
    }

    string trim(const string& str) {
        size_t first = str.find_first_not_of(' ');
        if (string::npos == first) {
            return str;
        }
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    int readInt() {
        int value;
        while (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Loi nhap du lieu. Vui long nhap mot so nguyen: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }

    long long readLongLong() {
        long long value;
        while (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Loi nhap du lieu. Vui long nhap mot so nguyen lon: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }

    string readString() {
        string value;
        getline(cin, value);
        return trim(value);
    }

    void copyText(char destination[], const string& source, int maxLength) {
        if (maxLength <= 0) return;
        strncpy(destination, source.c_str(), maxLength - 1);
        destination[maxLength - 1] = '\0';
    }

    bool containsText(const char text[], const string& query) {
        return strstr(text, query.c_str()) != nullptr;
    }

    string generateId(const string& prefix, int currentCount) {
        stringstream ss;
        ss << prefix << setfill('0') << setw(3) << (currentCount + 1);
        return ss.str();
    }
}
