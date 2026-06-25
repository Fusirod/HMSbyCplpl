#ifndef UTILS_H
#define UTILS_H

#include <string>

using namespace std;

namespace Utils {
    const int MAX_RECORDS = 1000;
    const int MAX_ID_LENGTH = 32;
    const int MAX_TEXT_LENGTH = 256;
    const int MAX_LONG_TEXT_LENGTH = 512;

    void clearScreen();
    void pauseScreen();
    string trim(const string& str);
    int readInt();
    long long readLongLong();
    string readString();
    void copyText(char destination[], const string& source, int maxLength);
    bool containsText(const char text[], const string& query);
    string generateId(const string& prefix, int currentCount);
}

#endif // UTILS_H
