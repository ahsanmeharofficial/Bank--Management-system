#include <iostream>
#include <string>

using namespace std;

// Base class for all types of accounts
class Account {
protected:
    int accountNumber;              // Unique account number for identification
    string accountHolderName;       // Name of the account holder
    double balance;                 // Current account balance in PKR

public:
    // Constructor to initialize account details
    Account(int accNum, string accHolder, double bal)
        : accountNumber(accNum), accountHolderName(accHolder), balance(bal) {}

    // Display basic account information
    virtual void displayAccountInfo() const {
        cout << "Account Holder: Prof M. Shahzad Sab" << endl;  // Display the user's name
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: PKR " << balance << endl;  // Display balance in PKR
    }

    // Virtual deposit and withdraw functions to be implemented in derived classes
    virtual void deposit(double amount) = 0;
    virtual bool withdraw(double amount) = 0;

    // Method to check the current balance
    double checkBalance() const {
        return balance;  // Return current balance
    }

    // Virtual destructor for cleanup
    virtual ~Account() {}
};

// Derived class for Savings Account (same functionality as Current Account but without overdraft)
class SavingsAccount : public Account {
public:
    // Constructor to initialize Savings Account details
    SavingsAccount(int accNum, string accHolder, double bal)
        : Account(accNum, accHolder, bal) {}

    // Deposit money into the account
    void deposit(double amount) override {
        balance += amount;
        cout << "Deposited PKR " << amount << ", New Balance: PKR " << balance << endl;
    }

    // Withdraw money from the account (if sufficient balance)
    bool withdraw(double amount) override {
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrawn PKR " << amount << ", New Balance: PKR " << balance << endl;
            return true;
        } else {
            cout << "Insufficient balance!" << endl;
            return false;
        }
    }
};

// Derived class for Current Account with overdraft facility
class CurrentAccount : public Account {
private:
    double overdraftLimit;  // Overdraft limit for the current account

public:
    // Constructor to initialize Current Account details
    CurrentAccount(int accNum, string accHolder, double bal, double overdraft)
        : Account(accNum, accHolder, bal), overdraftLimit(overdraft) {}

    // Deposit money into the account
    void deposit(double amount) override {
        balance += amount;
        cout << "Deposited PKR " << amount << ", New Balance: PKR " << balance << endl;
    }

    // Withdraw money from the account with overdraft facility
    bool withdraw(double amount) override {
        if (amount <= balance + overdraftLimit) {  // Allow overdraft up to the limit
            balance -= amount;
            cout << "Withdrawn PKR " << amount << ", New Balance: PKR " << balance << endl;
            return true;
        } else {
            cout << "Overdraft limit exceeded!" << endl;
            return false;
        }
    }
};

// Function to simulate the ATM process
void atmProcess(Account* account) {
    int pin;
    int attempts = 0;

    // PIN entry with 3 attempts for security
    while (attempts < 3) {
        cout << "Enter your 4-digit PIN: ";
        cin >> pin;

        if (pin == 1234) {  // Hardcoded correct PIN
            cout << "PIN accepted!\n" << endl;
            break;
        } else {
            cout << "Incorrect PIN. Try again." << endl;
            attempts++;
        }

        if (attempts == 3) {  // Block card after 3 incorrect attempts
            cout << "ATM Card blocked due to multiple incorrect PIN attempts!" << endl;
            return;
        }
    }

    // Display the balance after PIN is accepted
    cout << "Your current balance is: PKR " << account->checkBalance() << endl;

    // User inputs the amount to withdraw
    double withdrawAmount;
    cout << "Enter amount to withdraw (in PKR): ";
    cin >> withdrawAmount;

    // Perform withdrawal and check if successful
    if (account->withdraw(withdrawAmount)) {
        // Ask if the user wants a receipt
        char receiptChoice;
        cout << "Do you want a receipt? (y/n): ";
        cin >> receiptChoice;

        // Print the receipt if requested
        if (receiptChoice == 'y' || receiptChoice == 'Y') {
            cout << "\n----- RECEIPT -----" << endl;
            account->displayAccountInfo();  // Show account details
            cout << "Withdrawn Amount: PKR " << withdrawAmount << endl;
            cout << "Remaining Balance: PKR " << account->checkBalance() << endl;
            cout << "-------------------\n" << endl;
        }
    } else {
        cout << "Transaction failed due to insufficient balance." << endl;
    }

    // Thank the user for using the ATM service
    cout << "Thank you very much, Prof M. Shahzad Sab, for using our ATM service!" << endl;
}

// Function to select account type (Savings or Current)
Account* selectAccount() {
    int accountType;
    cout << "Select Account Type:\n1. Savings Account\n2. Current Account\n";
    cin >> accountType;

    if (accountType == 1) {
        // Create a SavingsAccount (same data as CurrentAccount)
        return new SavingsAccount(101, "Prof M. Shahzad Sab", 3000.0);  // Example Savings Account
    } else if (accountType == 2) {
        // Create a CurrentAccount with overdraft limit
        return new CurrentAccount(102, "Prof M. Shahzad Sab", 3000.0, 1000.0);  // Example Current Account
    } else {
        cout << "Invalid account type! Exiting..." << endl;
        return nullptr;
    }
}

// Main function to simulate ATM process
int main() {
    cout << "Please insert your ATM card (press enter to continue)..." << endl;
    cin.get();  // Simulating ATM card insertion

    // Account selection
    Account* account = selectAccount();
    if (account != nullptr) {
        atmProcess(account);  // Perform ATM operations
        delete account;  // Clean up allocated memory
    }

    return 0;
}

