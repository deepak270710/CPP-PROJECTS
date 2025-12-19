#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    char name[50];
    char aadhaar[15];
    double balance;

public:
    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;
        cin.ignore();

        cout << "Enter Account Holder Name: ";
        cin.getline(name, 50);

        cout << "Enter Aadhaar Number: ";
        cin >> aadhaar;

        cout << "Enter Initial Balance: ";
        cin >> balance;

        cout << "\n✅ Account Created Successfully!\n";
    }

    void showAccount() const {
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nName           : " << name;
        cout << "\nAadhaar No     : " << aadhaar;
        cout << "\nBalance        : ₹" << balance << endl;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "\n✅ Amount Deposited Successfully!\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "\n❌ Insufficient Balance!\n";
        } else {
            balance -= amount;
            cout << "\n✅ Amount Withdrawn Successfully!\n";
        }
    }

    double getBalance() const {
        return balance;
    }
};

// Function Prototypes
void writeAccount();
void displayAccount(int);
void depositWithdraw(int, int);
void displayAll();

int main() {
    int choice;
    int accNo;

    do {
        cout << "\n\n===== BANK MANAGEMENT SYSTEM =====";
        cout << "\n1. Create New Account";
        cout << "\n2. Deposit Amount";
        cout << "\n3. Withdraw Amount";
        cout << "\n4. Check Balance";
        cout << "\n5. Display All Accounts";
        cout << "\n6. Exit";
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            writeAccount();
            break;
        case 2:
            cout << "\nEnter Account Number: ";
            cin >> accNo;
            depositWithdraw(accNo, 1);
            break;
        case 3:
            cout << "\nEnter Account Number: ";
            cin >> accNo;
            depositWithdraw(accNo, 2);
            break;
        case 4:
            cout << "\nEnter Account Number: ";
            cin >> accNo;
            displayAccount(accNo);
            break;
        case 5:
            displayAll();
            break;
        case 6:
            cout << "\nThank you for using Bank System 🙏\n";
            break;
        default:
            cout << "\n❌ Invalid Choice!\n";
        }
    } while (choice != 6);

    return 0;
}

// Create Account
void writeAccount() {
    BankAccount acc;
    ofstream outFile("bank.dat", ios::binary | ios::app);

    acc.createAccount();
    outFile.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
    outFile.close();
}

// Display Single Account
void displayAccount(int accNo) {
    BankAccount acc;
    ifstream inFile("bank.dat", ios::binary);

    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        if (acc.getAccountNumber() == accNo) {
            acc.showAccount();
            found = true;
        }
    }
    inFile.close();

    if (!found)
        cout << "\n❌ Account Not Found!\n";
}

// Deposit / Withdraw
void depositWithdraw(int accNo, int option) {
    BankAccount acc;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    double amount;
    bool found = false;

    while (!file.eof() && file.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        if (acc.getAccountNumber() == accNo) {
            acc.showAccount();

            if (option == 1) {
                cout << "\nEnter Amount to Deposit: ";
                cin >> amount;
                acc.deposit(amount);
            } else {
                cout << "\nEnter Amount to Withdraw: ";
                cin >> amount;
                acc.withdraw(amount);
            }

            int pos = (-1) * static_cast<int>(sizeof(BankAccount));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));

            found = true;
            break;
        }
    }
    file.close();

    if (!found)
        cout << "\n❌ Account Not Found!\n";
}

// Display All Accounts
void displayAll() {
    BankAccount acc;
    ifstream inFile("bank.dat", ios::binary);

    if (!inFile) {
        cout << "\n❌ No Data Found!\n";
        return;
    }

    cout << "\n\n===== ALL BANK ACCOUNTS =====\n";
    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        acc.showAccount();
        cout << "-----------------------------";
    }
    inFile.close();
}
