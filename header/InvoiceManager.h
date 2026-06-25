#ifndef INVOICE_MANAGER_H
#define INVOICE_MANAGER_H

#include "Utils.h"
#include <string>

using namespace std;

class InvoiceManager {
private:
    int invoiceCount;
    char ids[Utils::MAX_RECORDS][Utils::MAX_ID_LENGTH];
    char patientIds[Utils::MAX_RECORDS][Utils::MAX_ID_LENGTH];
    char dates[Utils::MAX_RECORDS][Utils::MAX_TEXT_LENGTH];
    long long totalAmounts[Utils::MAX_RECORDS];
    char statuses[Utils::MAX_RECORDS][Utils::MAX_TEXT_LENGTH];
    string filename;

    void loadFromFile();
    void saveToFile();
    int findIndexById(const string& id);
    void removeAt(int index);

public:
    InvoiceManager();
    ~InvoiceManager();

    void addInvoice();
    void editInvoice();
    void deleteInvoice();
    void searchInvoice();
    void displayAllInvoices();
    
    // For reports
    long long calculateTotalRevenue();
};

#endif // INVOICE_MANAGER_H
