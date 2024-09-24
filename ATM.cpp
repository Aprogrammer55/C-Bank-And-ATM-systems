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

void structToStringVector(vector<account> &vClients, vector<string> &vStrings)
{
    for (account &client : vClients)
    {
        vStrings.push_back(convertToString(client));
    }
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

void drawQuickWithdraw()
{
    cout << "================================================================" << endl;
    cout << "\t\tQuick Withdraw" << endl;
    cout << "================================================================" << endl;
    cout << "\t[1] 20\t[2] 50" << endl;
    cout << "\t[3] 100\t[4] 200" << endl;
    cout << "\t[5] 400\t[6] 600" << endl;
    cout << "\t[7] 800\t[8] 1000" << endl;
    cout << "\t[9] Exit" << endl;
    cout << "================================================================" << endl;
}

void quickWithdraw(account &ac)
{
    bool success = true;
    while (true)
    {
        drawQuickWithdraw();
        cout << "Your Balance is : " << ac.accountBalance << endl;
        int redirect = -1;
        while (redirect < 1 || redirect > 9)
            redirect = ReadNumber("Choose What do you want to do ? [1 to 9] ?");
        switch (redirect)
        {
        case 1:
            if (ac.accountBalance >= 20)
            {
                ac.accountBalance -= 20;
                success = true;
            }
            else
                success = false;
            break;
        case 2:
            if (ac.accountBalance >= 50)
            {
                ac.accountBalance -= 50;
                success = true;
            }
            else
                success = false;
            break;
        case 3:
            if (ac.accountBalance >= 100)
            {
                ac.accountBalance -= 100;
                success = true;
            }
            else
                success = false;
            break;
        case 4:
            if (ac.accountBalance >= 200)
            {
                ac.accountBalance -= 200;
                success = true;
            }
            else
                success = false;
            break;
        case 5:
            if (ac.accountBalance >= 400)
            {
                ac.accountBalance -= 400;
                success = true;
            }
            else
                success = false;
            break;
        case 6:
            if (ac.accountBalance >= 600)
            {
                ac.accountBalance -= 600;
                success = true;
            }
            else
                success = false;
            break;
        case 7:
            if (ac.accountBalance >= 800)
            {
                ac.accountBalance -= 800;
                success = true;
            }
            else
                success = false;
            break;
        case 8:
            if (ac.accountBalance >= 1000)
            {
                ac.accountBalance -= 1000;
                success = true;
            }
            else
                success = false;
            break;
        case 9:
            return;
            break;
        }
        if (success)
            break;
        cout << "Error: You don't have enough money " << endl;
    }

    vector<account> vAccounts = LoadClientsDataFromFile("account.txt");
    for (account &client : vAccounts)
    {
        if (client.accountNumber == ac.accountNumber)
        {
            client = ac;
            vector<string> it;
            structToStringVector(vAccounts, it);
            saveFromVector("account.txt", it);
            vAccounts = LoadClientsDataFromFile("account.txt");
            pause();
            return;
        }
    }

    pause();
}

void normalWithdraw(account &ac)
{
    bool success = true;
    while (true)
    {
        int money = ReadNumber("Please enter the amount you want to withdraw : ");
        cout << "Your Balance is : " << ac.accountBalance << endl;
        if (ac.accountBalance >= money)
        {
            ac.accountBalance -= money;
            break;
        }

        cout << "Error: You don't have enough money " << endl;
    }

    vector<account> vAccounts = LoadClientsDataFromFile("account.txt");
    for (account &client : vAccounts)
    {
        if (client.accountNumber == ac.accountNumber)
        {
            client = ac;
            vector<string> it;
            structToStringVector(vAccounts, it);
            saveFromVector("account.txt", it);
            vAccounts = LoadClientsDataFromFile("account.txt");
            pause();
            return;
        }
    }

    pause();
}

void deposit(account &ac)
{
    int money = 0;
    cout << "Please enter the amount you want to deposit :";
    cin >> money;
    cout << "\n You sure you want to deposit ?" << endl;
    char ch = ReadChar();
    if (ch == 'y' || ch == 'Y')
    {
        ac.accountBalance += money;
    }
    else
    {
        pause();
        return;
    }

    vector<account> vAccounts = LoadClientsDataFromFile("account.txt");
    for (account &client : vAccounts)
    {
        if (client.accountNumber == ac.accountNumber)
        {
            client = ac;
            vector<string> it;
            structToStringVector(vAccounts, it);
            saveFromVector("account.txt", it);
            vAccounts = LoadClientsDataFromFile("account.txt");
            pause();
            return;
        }
    }

    pause();
}

void CheckBalances(account ac)
{
    cout << "==========================================================" << endl;
    cout << "Check Balance Screen" << endl;
    cout << "==========================================================" << endl;
    cout << "Your Balance is :" << ac.accountBalance << endl;
    pause();
}

void drawATMMenu()
{
    cout << "================================================================" << endl;
    cout << "\tMain Menu Screen" << endl;
    cout << "================================================================" << endl;
    cout << "\t[1] Quick Withdraw" << endl;
    cout << "\t[2] Normal Withdraw" << endl;
    cout << "\t[3] Deposit" << endl;
    cout << "\t[4] Check Balances" << endl;
    cout << "\t[5] Log Out" << endl;
    cout << "================================================================" << endl;
}

void ATMPage(account ac)
{
    while (true)
    {
        drawATMMenu();
        int redirect = -1;
        while (redirect < 1 || redirect > 5)
            redirect = ReadNumber("Choose What do you want to do ? [1 to 5] ?");
        switch (redirect)
        {
        case 1:
            quickWithdraw(ac);
            break;
        case 2:
            normalWithdraw(ac);
            break;
        case 3:
            deposit(ac);
            break;
        case 4:
            CheckBalances(ac);
            break;
        case 5:
            return;
            break;
        }
    }
}

account logIn()
{
    vector<account> vAccounts = LoadClientsDataFromFile("account.txt");
    cout << "================================================================" << endl;
    cout << "Log In Screen" << endl;
    cout << "================================================================" << endl;
    bool logged = false;
    while (!logged)
    {
        string accountNumber = ReadString("enter Account Number :");
        for (account u : vAccounts)
        {
            if (u.accountNumber == accountNumber)
            {
                string pinNumber = ReadString("enter Pin Code :");
                if (pinNumber == u.pinCode)
                {
                    logged = true;
                    return u;
                }
                else
                {
                    cout << "Invalid Account Number/pin Number: " << endl;
                    break;
                }
            }
        }
        cout << "this Account Number does not exist" << endl;
    }
    account c;
    return c;
}

int main()
{
    ATMPage(logIn());
}