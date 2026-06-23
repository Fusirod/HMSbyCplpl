#ifndef INVOICE_MANAGER_H
#define INVOICE_MANAGER_H

#include "models.h"
#include <vector>
#include <string>

using namespace std;

struct InvoiceManager {
private:
    vector<Invoice> invoices;
    string filename;

    void loadFromFile();
    void saveToFile();

public:
    InvoiceManager();
    ~InvoiceManager();

    void addInvoice();
    void editInvoice();
    void deleteInvoice();
    void searchInvoice();
    void displayAllInvoices();
    
    // For reports
    double calculateTotalRevenue();
};

#endif // INVOICE_MANAGER_H
