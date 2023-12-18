#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

const int ID_LENGTH = 10;
const int PIN_LENGTH = 6;

struct Account
{
    string id;
    double balance;
};

string generateRandomID()
{
    // Generate a random 10-character string
    string id;
    for (int i = 0; i < ID_LENGTH; ++i)
    {
        id += rand() % 10 + '0';
    }
    return id;
}

bool login(const string &id, const string &pin)
{
    string filename = id + ".txt";
    ifstream file(filename.c_str());
    if (!file.is_open())
    {
        return false;
    }

    string storedPin;
    file >> storedPin;
    if (storedPin != pin)
    {
        return false;
    }

    Account account;
    file >> account.balance;
    for (string friendly_account; file >> friendly_account;)
    {
        account.friendly_accounts.push_back(friendly_account);
    }

    file.close();
    return true;
}

void createAccount()
{
    string id = generateRandomID();
    string pin;
    cout << "Enter your desired PIN (6 digits): ";
    cin >> pin;

    string filename = id + ".txt";
    ofstream file(filename.c_str());
    file << pin << " 0" << endl;

    cout << "Your new ID is: " << id << endl;
}

void displayMenu()
{
    cout << "** ATM Main Menu **" << endl;
    cout << "1. Login" << endl;
    cout << "2. Create new account" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

int main()
{
    int choice;

    while (true)
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            string id, pin;
            cout << "Enter your ID: ";
            cin >> id;
            cout << "Enter your PIN: ";
            cin >> pin;

            if (login(id, pin))
            {
                // Implement account management logic here
                cout << "Login successful!" << endl;
            }
            else
            {
                cout << "Invalid ID or PIN. Please try again." << endl;
            }
            break;
        case 2:
            createAccount();
            break;
        case 3:
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
    return 0;
}