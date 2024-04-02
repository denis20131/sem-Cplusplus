#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class BankAccount {
private:
    struct Date {
        int day;
        int month;
        int year;
    };

    struct Transaction {
        Date date;
        string type;
        double amount;
    };

    Date creationDate;
    double balance;
    string ownerFirstName;
    string ownerLastName;
    Transaction lastTransaction;

public:
    BankAccount(const string& firstName, const string& lastName) {
        // Устанавливаем дату создания счета на текущую дату
        time_t t = time(NULL);
        tm* localTime = localtime(&t);
        creationDate.day = localTime->tm_mday;
        creationDate.month = localTime->tm_mon + 1;
        creationDate.year = localTime->tm_year + 1900;

        balance = 0.0;
        ownerFirstName = firstName;
        ownerLastName = lastName;
    }

    void deposit(double amount) {
        if (amount > 0.0) {
            balance += amount;
            lastTransaction = {getCurrentDate(), "Deposit", amount};
            cout << "Deposit of " << amount << " is successful.\n";
        } else {
            cout << "Invalid amount.\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0.0 && amount <= balance) {
            balance -= amount;
            lastTransaction = {getCurrentDate(), "Withdrawal", amount};
            cout << "Withdrawal of " << amount << " is successful.\n";
        } else {
            cout << "Invalid: " << amount<<"\n";
        }
    }

    void printLastTransaction() const {
        cout << "Last Transaction: "
                  << lastTransaction.date.day << "/"
                  << lastTransaction.date.month << "/"
                  << lastTransaction.date.year << "\n"
                  << "Type: " << lastTransaction.type << "\n"
                  << "Amount: $" << lastTransaction.amount << "\n";
    }

    void printBalance() const {
        cout << "Available Balance: " << balance << "\n";
    }

private:
    Date getCurrentDate() const {
        time_t t = time(NULL);
        tm* localTime = localtime(&t);
        Date currentDate;
        currentDate.day = localTime->tm_mday;
        currentDate.month = localTime->tm_mon + 1;
        currentDate.year = localTime->tm_year + 1900;
        return currentDate;
    }
};

int main() {
    BankAccount account("Khaibullin","Denis");

    account.deposit(1000.0);
    account.withdraw(500.0);
    account.withdraw(600.0);
    account.printLastTransaction();
    account.printBalance();

    return 0;
}