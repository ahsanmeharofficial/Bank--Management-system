#include <iostream>
#include <string>

using namespace std;

// Base class for all types of accounts
class Account {
protected:
    int accountNumber;              // Account number jo har account ke liye unique hota hai
    string accountHolderName;       // Account holder ka naam
    double balance;                 // Account mein mojood rakam (balance) PKR mein

public:
    // Account ki maloomat ko initialize karne ke liye constructor
    Account(int accNum, string accHolder, double bal)
        : accountNumber(accNum), accountHolderName(accHolder), balance(bal) {}

    // Account ki buniyadi maloomat dikhane ka function
    virtual void displayAccountInfo() const {
        cout << "Account Holder: Prof M. Shahzad Sab" << endl;  // Account holder ka naam dikhain
        cout << "Account Number: " << accountNumber << endl;    // Account number dikhain
        cout << "Balance: PKR " << balance << endl;             // Account mein mojood balance dikhain
    }

    // Deposit aur withdraw ke liye virtual functions (derived classes mein implement honge)
    virtual void deposit(double amount) = 0;
    virtual bool withdraw(double amount) = 0;

    // Account ka mojoodah balance check karne ka function
    double checkBalance() const {
        return balance;  // Mojoodah balance wapas karein
    }

    // Virtual destructor takay memory clean up ho sake
    virtual ~Account() {}
};

// SavingsAccount class jo Account se inheritance mein mili hai (Derived Class)
class SavingsAccount : public Account {
public:
    // Savings Account ki details initialize karne ke liye constructor
    SavingsAccount(int accNum, string accHolder, double bal)
        : Account(accNum, accHolder, bal) {}

    // Account mein paise jama karne ka function
    void deposit(double amount) override {
        balance += amount;  // Balance mein paise shamil karein
        cout << "Deposited PKR " << amount << ", New Balance: PKR " << balance << endl;  // Naya balance dikhain
    }

    // Account se paise nikalne ka function (agar balance kafi hai)
    bool withdraw(double amount) override {
        if (amount <= balance) {
            balance -= amount;  // Balance mein se paise nikal lein
            cout << "Withdrawn PKR " << amount << ", New Balance: PKR " << balance << endl;  // Naya balance dikhain
            return true;
        } else {
            cout << "Insufficient balance!" << endl;  // Agar balance kam ho to message dikhain
            return false;
        }
    }
};

// CurrentAccount class jisme overdraft facility hai
class CurrentAccount : public Account {
private:
    double overdraftLimit;  // Overdraft ki had

public:
    // Current Account ki details initialize karne ke liye constructor
    CurrentAccount(int accNum, string accHolder, double bal, double overdraft)
        : Account(accNum, accHolder, bal), overdraftLimit(overdraft) {}

    // Account mein paise jama karne ka function
    void deposit(double amount) override {
        balance += amount;  // Balance mein paise shamil karein
        cout << "Deposited PKR " << amount << ", New Balance: PKR " << balance << endl;  // Naya balance dikhain
    }

    // Account se paise nikalne ka function overdraft facility ke saath
    bool withdraw(double amount) override {
        if (amount <= balance + overdraftLimit) {  // Overdraft ki had ke andar paise nikalain
            balance -= amount;  // Balance mein se paise nikal lein
            cout << "Withdrawn PKR " << amount << ", New Balance: PKR " << balance << endl;  // Naya balance dikhain
            return true;
        } else {
            cout << "Overdraft limit exceeded!" << endl;  // Agar overdraft limit se zyada ho to message dikhain
            return false;
        }
    }
};

// ATM process ko simulate karne ka function
void atmProcess(Account* account) {
    int pin;
    int attempts = 0;

    // PIN entry (3 baar koshish karne ki ijazat)
    while (attempts < 3) {
        cout << "Enter your 4-digit PIN: ";
        cin >> pin;

        if (pin == 1234) {  // Hardcoded sahi PIN
            cout << "PIN accepted!\n" << endl;  // PIN sahi hone par message
            break;
        } else {
            cout << "Incorrect PIN. Try again." << endl;  // PIN galat hone par message
            attempts++;
        }

        if (attempts == 3) {  // 3 baar galat PIN enter karne par ATM block ho jayegi
            cout << "ATM Card blocked due to multiple incorrect PIN attempts!" << endl;
            return;
        }
    }

    // PIN sahi hone ke baad mojoodah balance dikhain
    cout << "Your current balance is: PKR " << account->checkBalance() << endl;

    // User se paise nikalne ke liye amount input lein
    double withdrawAmount;
    cout << "Enter amount to withdraw (in PKR): ";
    cin >> withdrawAmount;

    // Paise nikalne ka amal aur successful hone par receipt ki offer
    if (account->withdraw(withdrawAmount)) {
        // User se receipt ki darkhwast karein
        char receiptChoice;
        cout << "Do you want a receipt? (y/n): ";
        cin >> receiptChoice;

        // Receipt print karein agar user chahain
        if (receiptChoice == 'y' || receiptChoice == 'Y') {
            cout << "\n----- RECEIPT -----" << endl;
            account->displayAccountInfo();  // Account ki details dikhain
            cout << "Withdrawn Amount: PKR " << withdrawAmount << endl;
            cout << "Remaining Balance: PKR " << account->checkBalance() << endl;
            cout << "-------------------\n" << endl;
        }
    } else {
        cout << "Transaction failed due to insufficient balance." << endl;  // Agar transaction fail ho to message dikhain
    }

    // User ko ATM service ke liye shukriya ada karein
    cout << "Thank you very much, Prof M. Shahzad Sab, for using our ATM service!" << endl;
}

// Account type (Savings ya Current) select karne ka function
Account* selectAccount() {
    int accountType;
    cout << "Select Account Type:\n1. Savings Account\n2. Current Account\n";
    cin >> accountType;

    if (accountType == 1) {
        // SavingsAccount create karein (CurrentAccount ki tarah hi data)
        return new SavingsAccount(101, "Prof M. Shahzad Sab", 3000.0);  // Example Savings Account
    } else if (accountType == 2) {
        // CurrentAccount create karein with overdraft limit
        return new CurrentAccount(102, "Prof M. Shahzad Sab", 3000.0, 1000.0);  // Example Current Account
    } else {
        cout << "Invalid account type! Exiting..." << endl;  // Agar account type galat ho to exit karein
        return nullptr;
    }
}

// Main function jo ATM process ko simulate karta hai
int main() {
    cout << "Please insert your ATM card (press enter to continue)..." << endl;
    cin.get();  // ATM card insertion ko simulate karna

    // Account selection
    Account* account = selectAccount();
    if (account != nullptr) {
        atmProcess(account);  // ATM operations perform karna
        delete account;  // Allocated memory clean up karna
    }

    return 0;
}


