#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ostream>
#include <cmath>

using namespace std;

struct account
{
    string accountNumber;
    string name;
    double accountBalance;
    string pinCode;
    string phone;
};

struct user
{
    string name;
    string password;
    string perms;
};

string ReadString(string message = "Enter String")
{
    string S1;
    cout << message << endl;
    cin >> S1;
    return S1;
}

double ReadDouble(string message = "Your String")
{
    double S1;
    cout << "Please Enter " << message << endl;
    cin >> S1;
    return S1;
}

string decimalToBinary(const string &decimalStr)
{
    int decimal = stoi(decimalStr);
    string binary = "";

    while (decimal > 0)
    {
        binary = (decimal % 2 == 0 ? "0" : "1") + binary;
        decimal /= 2;
    }

    return binary == "" ? "0" : binary;
}

string binaryToDecimal(const string &binary)
{
    int decimal = 0;
    int len = binary.length();

    for (int i = 0; i < len; i++)
    {
        if (binary[len - i - 1] == '1')
        {
            decimal += pow(2, i);
        }
    }

    return to_string(decimal);
}

char ReadChar()
{
    char Ch1;
    cin >> Ch1;
    return Ch1;
}

int ReadNumber(string message = "\nPlease Enter a Integer?\n")
{
    int Ch1;
    cout << message;
    cin >> Ch1;
    return Ch1;
}

void loadIntoVector(string fileName, vector<string> &vRecords)
{
    fstream myFile;
    myFile.open(fileName, ios::in);
    if (myFile.is_open())
    {
        string line;
        while (getline(myFile, line))
        {
            vRecords.push_back(line);
        }
    }
}

void saveFromVector(string fileName, vector<string> &vRecords)
{
    fstream myFile;
    myFile.open(fileName, ios::out);
    if (myFile.is_open())
    {
        for (string &line : vRecords)
            if (line != "")
                myFile << line << endl;
    }
}

void deleteRecord(string fileName, string record)
{
    vector<string> vRecords;
    loadIntoVector(fileName, vRecords);
    for (string &line : vRecords)
        if (line == record)
            line = "";
    saveFromVector(fileName, vRecords);
}

void pause()
{
    string a;
    cout << "Please click anything to continue...";
    cin >> a;
    for (size_t i = 0; i < 50; i++)
    {
        cout << endl;
    }
}

void updateRecord(string fileName, string record, string newRecord)
{
    vector<string> vRecords;
    loadIntoVector(fileName, vRecords);
    for (string &line : vRecords)
        if (line == record)
            line = newRecord;
    saveFromVector(fileName, vRecords);
}

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable
    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length()); /* erase() until positon and move to next word. */
    }
    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }
    return vString;
}

string convertToString(account &acc)
{
    if (acc.accountNumber == "Deleted")
        return "";
    string data = acc.accountNumber + "#//#";
    data += acc.name;
    data += "#//#" + to_string(acc.accountBalance);
    data += "#//#" + acc.phone;
    data += "#//#" + acc.pinCode;
    return data;
}

string convertToString(user &acc)
{
    if (acc.name == "Deleted")
        return "";
    string data = acc.name + "#//#";
    data += "#//#" + acc.password;
    data += "#//#" + acc.perms;
    return data;
}

void convertToStruct(account &acc, string data)
{
    vector<string> strings;
    strings = SplitString(data, "#//#");
    acc.accountNumber = strings[0];
    acc.name = strings[1];
    acc.accountBalance = stod(strings[2]);
    acc.phone = strings[3];
    acc.pinCode = strings[4];
}

void convertToStruct(user &acc, string data)
{
    vector<string> strings;
    strings = SplitString(data, "#//#");
    acc.name = strings[0];
    acc.password = strings[1];
    acc.perms = strings[2];
}

void PrintClientRecord(account Client)
{
    cout << "| " << setw(15) << left << Client.accountNumber;
    cout << "| " << setw(10) << left << Client.pinCode;
    cout << "| " << setw(40) << left << Client.name;
    cout << "| " << setw(12) << left << Client.phone;
    cout << "| " << setw(12) << left << Client.accountBalance;
}

void PrintUserRecord(user usr)
{
    cout << "| " << setw(40) << left << usr.name;
    cout << "| " << setw(12) << left << usr.password;
    cout << "| " << setw(12) << left << usr.perms;
}

void PrintClientBalance(account Client)
{
    cout << "| " << setw(15) << left << Client.accountNumber;
    cout << "| " << setw(40) << left << Client.name;
    cout << "| " << setw(12) << left << Client.accountBalance;
}

void PrintAllClientsData(vector<account> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    for (account Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    pause();
}

void PrintAllUsersData(vector<user> vUsers)
{
    cout << "\n\t\t\t\t\tUser List (" << vUsers.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    cout << "| " << left << setw(15) << "Name";
    cout << "| " << left << setw(10) << "password";
    cout << "| " << left << setw(40) << "perms";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    for (user usr : vUsers)
    {
        PrintUserRecord(usr);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    pause();
}

vector<account> LoadClientsDataFromFile(string FileName)
{
    vector<account> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode
    if (MyFile.is_open())
    {
        string Line;
        account Client;
        while (getline(MyFile, Line))
        {
            convertToStruct(Client, Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

vector<user> LoadUsersDataFromFile(string FileName)
{
    vector<user> vUsers;
    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode
    if (MyFile.is_open())
    {
        string Line;
        user User;
        while (getline(MyFile, Line))
        {
            convertToStruct(User, Line);
            vUsers.push_back(User);
        }
        MyFile.close();
    }
    return vUsers;
}

void printClientRecord(account Client)
{
    cout << "-------------------------------------";
    cout << "\n\nThe following is the extracted client record:\n";
    cout << "\nAccount Number: " << Client.accountNumber;
    cout << "\nPin Code     : " << Client.pinCode;
    cout << "\nName         : " << Client.name;
    cout << "\nPhone        : " << Client.phone;
    cout << "\nAccount Balance: " << Client.accountBalance << endl;
    cout << "-------------------------------------" << endl;
}

void printUserRecord(user usr)
{
    cout << "-------------------------------------";
    cout << "\n\nThe following is the extracted user record:\n";
    cout << "\nName         : " << usr.name;
    cout << "\nPassword        : " << usr.password;
    cout << "\nperms: " << usr.perms << endl;
    cout << "-------------------------------------" << endl;
}

void structToStringVector(vector<account> &vClients, vector<string> &vStrings)
{
    for (account &client : vClients)
    {
        vStrings.push_back(convertToString(client));
    }
}

void structToStringVector(vector<user> &vClients, vector<string> &vStrings)
{
    for (user &client : vClients)
    {
        vStrings.push_back(convertToString(client));
    }
}
/* ALl clients methods */
account ReadNewClient(vector<account> &vClients)
{
    account Client;
    bool flag = false;
    while (!flag)
    {
        cout << "Enter Account Number? "; // Usage of std::ws will extract allthe whitespace character
        getline(cin >> ws, Client.accountNumber);
        bool rep = false;
        for (account client : vClients)
        {
            if (client.accountNumber == Client.accountNumber)
                rep = true;
        }

        flag = !rep;
    }
    cout << "Enter PinCode? ";
    getline(cin >> ws, Client.pinCode);
    cout << "Enter Name? ";
    getline(cin, Client.name);
    cout << "Enter Phone? ";
    getline(cin, Client.phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.accountBalance;
    return Client;
}

user ReadNewUser(vector<user> &vUsers)
{
    user usr;
    bool flag = false;
    while (!flag)
    {
        cout << "Enter Name? "; // Usage of std::ws will extract allthe whitespace character
        getline(cin >> ws, usr.name);
        bool rep = false;
        for (user ur : vUsers)
        {
            if (ur.name == usr.name)
                rep = true;
        }

        flag = !rep;
    }
    cout << "Enter password? ";
    getline(cin >> ws, usr.password);
    cout << "you want this user to have all perms?? (Y|N) " << endl;
    char b = 'q';
    cin >> b;
    if (b == 'Y' || b == 'y')
    {
        usr.perms = "-1";
        return usr;
    }
    else
    {
        string arr[7] = {
            "Can Show Client List",
            "Can Add New Client",
            "Can Delete Client",
            "Can Update Client Info",
            "Can Find Client",
            "Can Transactions",
            "Can Manage users."};
        string perms = "";
        for (int i = 0; i < 7; i++)
        {
            cout << arr[i] << " ? (Y|N)";
            char a = 'f';
            cin >> a;
            if (a == 'Y' || a == 'y')
                perms += "1";
            else
                perms += "0";
        }
        usr.perms = binaryToDecimal(perms);
        return usr;
    }
}

void addNewClient(vector<account> &vClients)
{
    cout << "================================================================" << endl;
    cout << "Add Client" << endl;
    cout << "================================================================" << endl;
    while (true)
    {
        vClients.push_back(ReadNewClient(vClients));
        vector<string> it;
        structToStringVector(vClients, it);
        saveFromVector("account.txt", it);
        cout << "Add more clients ? (Y|N)" << endl;
        char ch = ReadChar();
        if (ch != 'y' && ch != 'Y')
            break;
    }
    pause();
}

void addNewUser(vector<user> &vUsers)
{
    cout << "================================================================" << endl;
    cout << "Add User" << endl;
    cout << "================================================================" << endl;
    while (true)
    {
        vUsers.push_back(ReadNewUser(vUsers));
        vector<string> it;
        structToStringVector(vUsers, it);
        saveFromVector("users.txt", it);
        cout << "Add more users ? (Y|N)" << endl;
        char ch = ReadChar();
        if (ch != 'y' && ch != 'Y')
            break;
    }
    pause();
}

void deleteClients(vector<account> &clients)
{
    string accNum = ReadString("Please enter the account number that you want to delete");
    bool flag = false;
    for (account &client : clients)
    {
        if (client.accountNumber == accNum)
        {
            flag = true;
            printClientRecord(client);
            cout << "\n You sure you want to delete this account?" << endl;
            char ch = ReadChar();
            if (ch == 'y' || ch == 'Y')
            {
                client.accountNumber = "Deleted";
                vector<string> it;
                structToStringVector(clients, it);
                saveFromVector("account.txt", it);
                clients = LoadClientsDataFromFile("account.txt");
                pause();
                return;
            }
            else
            {
                pause();
                return;
            }
        }
    }

    if (!flag)
        cout << "No User With This account number" << endl;
    pause();
}
void deleteUsers(vector<user> &users)
{
    string userName = ReadString("Please enter the User name that you want to delete");
    bool flag = false;
    for (user &usr : users)
    {
        if (usr.name == userName)
        {
            flag = true;
            printUserRecord(usr);
            cout << "\n You sure you want to delete this user?" << endl;
            char ch = ReadChar();
            if (ch == 'y' || ch == 'Y')
            {
                usr.name = "Deleted";
                vector<string> it;
                structToStringVector(users, it);
                saveFromVector("users.txt", it);
                users = LoadUsersDataFromFile("users.txt");
                pause();
                return;
            }
            else
            {
                pause();
                return;
            }
        }
    }

    if (!flag)
        cout << "No User With This name" << endl;
    pause();
}

void updateClient(vector<account> &clients)
{
    string accNum = ReadString("Please enter the account number that you want to Update");
    bool flag = false;
    for (account &client : clients)
    {
        if (client.accountNumber == accNum)
        {
            flag = true;
            printClientRecord(client);
            cout << "\n You sure you want to Update this account?" << endl;
            char ch = ReadChar();
            if (ch == 'y' || ch == 'Y')
            {

                cout << "Enter PinCode? ";
                getline(cin >> ws, client.pinCode);
                cout << "Enter Name? ";
                getline(cin, client.name);
                cout << "Enter Phone? ";
                getline(cin, client.phone);
                cout << "Enter AccountBalance? ";
                cin >> client.accountBalance;
                vector<string> it;
                structToStringVector(clients, it);
                saveFromVector("account.txt", it);
                pause();
                return;
            }
            else
            {
                pause();
                return;
            }
        }
    }

    if (!flag)
        cout << "No User With This account number" << endl;
    pause();
}

void updateUsers(vector<user> &users)
{
    string name = ReadString("Please enter the user Name that you want to Update");
    bool flag = false;
    for (user &usr : users)
    {
        if (usr.name == name)
        {
            flag = true;
            printUserRecord(usr);
            cout << "\n You sure you want to Update this user?" << endl;
            char ch = ReadChar();
            if (ch == 'y' || ch == 'Y')
            {

                cout << "Enter PinCode? ";
                getline(cin >> ws, usr.password);
                cout << "Enter Name? ";

                cout << "you want this user to have all perms?? (Y|N) " << endl;
                char b = 'q';
                cin >> b;
                if (b == 'Y' || b == 'y')
                {
                    usr.perms = "-1";
                }
                else
                {
                    string arr[7] = {
                        "Can Show Client List",
                        "Can Add New Client",
                        "Can Delete Client",
                        "Can Update Client Info",
                        "Can Find Client",
                        "Can Transactions",
                        "Can Manage users."};
                    string perms = "";
                    for (int i = 0; i < 7; i++)
                    {
                        cout << arr[i] << " ? (Y|N)";
                        char a = 'f';
                        cin >> a;
                        if (a == 'Y' || a == 'y')
                            perms += "1";
                        else
                            perms += "0";
                    }
                    usr.perms = binaryToDecimal(perms);
                }

                vector<string> it;
                structToStringVector(users, it);
                saveFromVector("users.txt", it);
                pause();
                return;
            }
            else
            {
                pause();
                return;
            }
        }
    }

    if (!flag)
        cout << "No User With This account number" << endl;
    pause();
}

void findClient(vector<account> &clients)
{
    string accNum = ReadString("Please enter the account number that you want to Find");
    bool flag = false;
    for (account &client : clients)
    {
        if (client.accountNumber == accNum)
        {
            flag = true;
            printClientRecord(client);
            pause();
            return;
        }
    }

    if (!flag)
        cout << "No User With This account number" << endl;
    pause();
}

void findUser(vector<user> &users)
{
    string name = ReadString("Please enter the User Name that you want to Find");
    bool flag = false;
    for (user &usr : users)
    {
        if (usr.name == name)
        {
            flag = true;
            printUserRecord(usr);
            pause();
            return;
        }
    }

    if (!flag)
        cout << "No User With This Name" << endl;
    pause();
}

void deposit(vector<account> &clients)
{
    string accNum = ReadString("Please enter the account number that you want to deposit in");
    bool flag = false;
    for (account &client : clients)
    {
        if (client.accountNumber == accNum)
        {
            flag = true;
            printClientRecord(client);
            int money = 0;
            cout << "Please enter the amount you want to deposit in this account :";
            cin >> money;
            cout << "\n You sure you want to deposit in this account?" << endl;
            char ch = ReadChar();
            if (ch == 'y' || ch == 'Y')
            {
                client.accountBalance += money;
                vector<string> it;
                structToStringVector(clients, it);
                saveFromVector("account.txt", it);
                clients = LoadClientsDataFromFile("account.txt");
                pause();
                return;
            }
            else
            {
                pause();
                return;
            }
        }
    }

    if (!flag)
        cout << "No User With This account number" << endl;
    pause();
}

void withdraw(vector<account> &clients)
{
    string accNum = ReadString("Please enter the account number that you want to withdraw from");
    bool flag = false;
    for (account &client : clients)
    {
        if (client.accountNumber == accNum)
        {
            flag = true;
            printClientRecord(client);
            int money = 0;
            cout << "Please enter the amount you want to withdraw from this account :";
            cin >> money;
            cout << "\n You sure you want to withdraw from this account?" << endl;
            char ch = ReadChar();
            if (ch == 'y' || ch == 'Y')
            {
                client.accountBalance -= money;
                vector<string> it;
                structToStringVector(clients, it);
                saveFromVector("account.txt", it);
                clients = LoadClientsDataFromFile("account.txt");
                pause();
                return;
            }
            else
            {
                pause();
                return;
            }
        }
    }

    if (!flag)
        cout << "No User With This account number" << endl;
    pause();
}

void totalBalances(vector<account> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    for (account Client : vClients)
    {
        PrintClientBalance(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    pause();
}

void drawTransactionsMenu()
{
    cout << "================================================================" << endl;
    cout << "\tMain Menu Screen" << endl;
    cout << "================================================================" << endl;
    cout << "\t[1] Deposit" << endl;
    cout << "\t[2] Withdraw" << endl;
    cout << "\t[3] Total Balances" << endl;
    cout << "\t[4] Main Menu" << endl;
    cout << "================================================================" << endl;
}

void transactionPage(vector<account> accounts)
{
    while (true)
    {
        drawTransactionsMenu();
        int redirect = -1;
        while (redirect < 1 || redirect > 4)
            redirect = ReadNumber("Choose What do you want to do ? [1 to 4] ?");
        switch (redirect)
        {
        case 1:
            deposit(accounts);
            break;
        case 2:
            withdraw(accounts);
            break;
        case 3:
            totalBalances(accounts);
            break;
        case 4:
            return;
            break;
        }
    }
}

void drawManageScreen()
{
    cout << "================================================================" << endl;
    cout << setw(15) << " Manage Users Screen" << endl;
    cout << "================================================================" << endl;
    cout << "\t[1] List Users" << endl;
    cout << "\t[2] Add New User" << endl;
    cout << "\t[3] Delete User" << endl;
    cout << "\t[4] Update User Info" << endl;
    cout << "\t[5] Find User" << endl;
    cout << "\t[6] Main menu" << endl;
    cout << "================================================================" << endl;
}

void ManageUsers()
{
    vector<user> users = LoadUsersDataFromFile("users.txt");
    while (true)
    {
        drawManageScreen();
        int redirect = -1;
        while (redirect < 1 || redirect > 6)
            redirect = ReadNumber("Choose What do you want to do ? [1 to 8] ?");
        switch (redirect)
        {
        case 1:
            PrintAllUsersData(users);
            break;
        case 2:
            addNewUser(users);
            break;
        case 3:
            deleteUsers(users);
            break;
        case 4:
            updateUsers(users);
            break;
        case 5:
            findUser(users);
            break;
        case 6:
            return;
        default:
            break;
        }
    }
}

void drawMainMenu()
{
    cout << "================================================================" << endl;
    cout << setw(15) << " Main Menu Screen" << endl;
    cout << "================================================================" << endl;
    cout << "\t[1] Show Client List" << endl;
    cout << "\t[2] Add New Client" << endl;
    cout << "\t[3] Delete Client" << endl;
    cout << "\t[4] Update Client Info" << endl;
    cout << "\t[5] Find Client" << endl;
    cout << "\t[6] Transactions" << endl;
    cout << "\t[7] Manage users." << endl;
    cout << "\t[8] Logout." << endl;
    cout << "================================================================" << endl;
}

void MainMenu(string perms)
{
    vector<account> accounts = LoadClientsDataFromFile("account.txt");
    bool bl = false;
    string arr[7];
    if (perms == "-1")
        bl = true;
    else
    {

        perms = decimalToBinary(perms);
        for (int i = 0; i < 7; i++)
        {
            if (i < perms.length())
            {
                if (perms[i] == '1')
                    arr[i] = '1';
            }
            else
                arr[i] = '0';
        }
    }
    while (true)
    {
        drawMainMenu();
        int redirect = -1;
        while (redirect < 1 || redirect > 8)
            redirect = ReadNumber("Choose What do you want to do ? [1 to 8] ?");
        switch (redirect)
        {
        case 1:
            if (bl || arr[0] == "1")
                PrintAllClientsData(accounts);
            else
                cout << "no permission to access this service" << endl;
            break;
        case 2:
            if (bl || arr[1] == "1")
                addNewClient(accounts);
            else
                cout << "no permission to access this service" << endl;
            break;
        case 3:
            if (bl || arr[2] == "1")
                deleteClients(accounts);
            else
                cout << "no permission to access this service" << endl;
            break;
        case 4:
            if (bl || arr[3] == "1")
                updateClient(accounts);
            else
                cout << "no permission to access this service" << endl;
            break;
        case 5:
            if (bl || arr[4] == "1")
                findClient(accounts);
            else
                cout << "no permission to access this service" << endl;
            break;
        case 6:
            if (bl || arr[5] == "1")
                transactionPage(accounts);
            else
                cout << "no permission to access this service" << endl;
            break;
        case 7:
            if (bl || arr[6] == "1")
                ManageUsers();
            else
                cout << "no permission to access this service" << endl;
            break;
        case 8:
            return;
        default:
            break;
        }
    }
}

string logIn()
{
    vector<user> users = LoadUsersDataFromFile("users.txt");
    cout << "================================================================" << endl;
    cout << "Log In Screen" << endl;
    cout << "================================================================" << endl;
    bool logged = false;
    while (!logged)
    {
        string username = ReadString("enter username :");
        for (user u : users)
        {
            if (u.name == username)
            {
                string password = ReadString("enter password :");
                if (password == u.password)
                {
                    logged = true;
                    return u.perms;
                }
                else
                {
                    cout << "Invalid username/password: " << endl;
                    break;
                }
            }
        }
        cout << "this username does not exist" << endl;
    }
    return "-1";
}

int main()
{
    MainMenu(logIn());
    return 0;
}