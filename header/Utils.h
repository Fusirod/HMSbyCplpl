#ifndef UTILS_H
#define UTILS_H

#include <string>

using namespace std;

namespace Utils {
    void clearScreen();
    void pauseScreen();
    string trim(const string& str);
    int readInt();
    double readDouble();
    string readString();
    string generateId(const string& prefix, int currentCount);
}

#endif // UTILS_H
