#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <windows.h>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <conio.h>
#include <stack>
#include<thread>
#include<chrono>
#include<algorithm>
#include<ctime>
using namespace std;
int top;
class User
{
    string name;
    string password;

public:
    User() {}

    string getName()
    {
        return name;
    }

    string getPassword()
    {
        return password;
    }

    void setName(string n)
    {
        name = n;
    }

    void setPassword(string p)
    {
        password = p;
    }

    void registerUser()
    {
        int i, j;
        string str = "WE ARE HEADING YOU TO THE LOGIN PAGE PLEASE WAIT...";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        cout << endl << endl
            << setw(55) << "Enter name: ";
        cin >> name;
        cout<<endl << setw(59) << "Enter password: ";

        // Use conio.h library to hide password input
        char ch;
        while ((ch = _getch()) != '\r')
        {
            password += ch;
            cout << '*';
        }

        // Open the file to write user information
        ofstream outFile("users.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << name << " " << password << endl;
            outFile.close();
            cout << setw(67) << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
            cout<<endl << "REGISTRATION SUCCESSFUL!" << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            cout << setw(44);
            cout << endl
                << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
            for (i = 0; str[i] != '\0'; i++)
            {
    
                cout << str[i];
                Sleep(35);
            }
            Sleep(100);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            system("cls");
            cout << "\n\n";
            loginuser();
        }
        else
        {
            cout << endl
                << "Error: Unable to open file." << endl;
        }
    }

    void loginuser()
    {
        int error = 0, i;
        bool islogin;
        do
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            cout << endl<<endl<<endl
                << setw(75) << "KINDLY ENTER YOUR CREDENTIALS" << endl;
            cout<<endl << setw(57) << "Enter name:";
            string name;
            cin >> name;
            setName(name);
            cout<<endl << setw(62) << "Enter password: ";
            // Use conio.h library to hide password input
            char ch;
            string password;
            while ((ch = _getch()) != '\r')
            {
                password += ch;
                cout << '*';
            }
            setPassword(password);

            // Check user credentials
            islogin = checkCredentials();

            // Check if user credentials are correct
            if (islogin)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
                cout << setw(63) << endl<<endl<<endl
                    << "LOGIN SUCCESSFUL!" << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
                Sleep(500);
                system("cls");
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
                cout << endl
                    << setw(59)
                    << "LOGIN FAILED!" << endl;
                Sleep(500);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
                error++;
                if (error >= 3)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
                    cout << endl
                        << setw(85) << "LOGIN LIMIT HAS BEEN REACHED. REGISTER YOURSELF NOW!";
             
                    system("cls");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
                    registerUser();
                }
            }
        } while (!islogin);
    }

    bool checkCredentials()
    {
        // Open the file to read user information
        ifstream inFile("users.txt");
        if (inFile.is_open())
        {
            string nameFromFile, passwordFromFile;
            while (inFile >> nameFromFile >> passwordFromFile)
            {
                if (nameFromFile == name && passwordFromFile == password)
                {
                    inFile.close();
                    return true;
                }
            }
            inFile.close();
        }
        else
        {
            cout << endl
                << "Error: Unable to open file." << endl;
        }
        return false;
    }

    bool userExists(string username)
    {
        ifstream inFile("users.txt");
        if (inFile.is_open())
        {
            string nameFromFile, passwordFromFile;
            while (inFile >> nameFromFile >> passwordFromFile)
            {
                if (nameFromFile == username)
                {
                    inFile.close();
                    return true;
                }
            }
            inFile.close();
        }
        return false;
    }

    void createUserFile()
    {
        ofstream userFile(name + ".csv");
        userFile.close();
    }
};
class Contact
{
public:
    Contact* next;
    string name, city, address, group, number;

    Contact(string n, string c, string a, string num)
    {
        name = n;
        city = c;
        address = a;
        number = num;
        next = NULL;
        group = "";
    }

    void changename(string n) { name = n; }
    void changecity(string c) { city = c; }
    void changeaddress(string ad) { address = ad; }
    void addingroup(string grp) { group = grp; }
};
class PhoneBook
{
public:
    User u1;
    static const int size = 26;
    Contact* list[size];
    stack<Contact*>s1;
    stack<Contact*>temp;
    PhoneBook(User user)
    {
        u1 = user;
        for (int i = 0; i < size; i++)
        {
            list[i] = NULL;
        }
        loadContactsFromCSV();
    }

    ~PhoneBook()
    {
        saveContactsToCSV();
    }

    void insertContact(string n, string c, string a, string num);
    void displayContact();
    void searchContact(string searchName);
    void deleteContact(string deleteName);
    void displayContactsByGroup(string group);
    void customSort(string sortField, bool ascending);
    void loadContactsFromCSV();
    void saveContactsToCSV();
    void recentlydeleted();
    void updateContact(string name);
};

void PhoneBook::insertContact(string n, string c, string a, string num)
{
    Contact* newcontact = new Contact(n, c, a, num);
    int index = n[0] - 65;

    Contact* temp = list[index];
    if (temp == NULL)
    {
        list[index] = newcontact;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newcontact;
    }

    saveContactsToCSV();
}

void PhoneBook::displayContact()
{
    bool flag = 0;
    cout << endl << endl << endl << endl;
    cout << setw(80) << "-----------------------------------------" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 246);
    for (int i = 0; i < size; i++)
    {
        Contact* temp = list[i];
        if (temp != NULL)
        {
            while (temp != NULL)
            {
                flag = 1;
                cout<<setw(45) << temp->name << "\t" << temp->number << "\t" << temp->city << "\t" << temp->address << "\t" << temp->group << endl;
                temp = temp->next;
            }
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
    if (flag==0)
    {
        cout << setw(67) << "NO CONTACTS FOUND." << endl;
    }
    cout << setw(80) << "-----------------------------------------" << endl;
    cout<<endl << setw(75) << "PRESS ENTER KEY TO CONTINUE...";
    cin.get();
    system("cls");
}

void PhoneBook::searchContact(string searchName)
{
    bool contactFound = false;
    int index = searchName[0] - 65;
    int s = 0;

        Contact* temp = list[index];
        cout << endl << endl << endl << endl;
        cout << setw(80) << "-----------------------------------------" << endl;
        while (temp != NULL)
        {
            if (temp->name == searchName)
            {
                if (s == 0)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
                    cout << setw(70) << "-----CONTACT FOUND-----" << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);


                }
                cout << setw(45) << temp->name << "\t" << temp->number << "\t" << temp->city << "\t" << temp->address << "\t" << temp->group << endl;
                contactFound = true;
                s++;
            }
            temp = temp->next;
        }

    if (!contactFound)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
        cout << setw(75) << "-----CONTACT NOT FOUND-----" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
    }
    cout << setw(80) << "-----------------------------------------" << endl;
    cout << endl << setw(75) << "PRESS ENTER KEY TO CONTINUE...";
    cin.get();
    system("cls");
}

void PhoneBook::displayContactsByGroup(string group)
{
    cout << "Contacts in Group '" << group << "':\n";
    for (int i = 0; i < size; i++)
    {
        Contact* temp = list[i];
        while (temp != NULL)
        {
            if (temp->group == group)
            {
                cout << temp->name << " " << temp->number << " " << temp->city << " " << temp->address << " " << temp->group << endl;
            }
            temp = temp->next;
        }
    }
}

void PhoneBook::deleteContact(string deleteName)
{
    string str = "CONTACT DELETED SUCCESSFULLY";
    cout << endl << endl << endl << endl;
    cout << setw(80) << "-----------------------------------------" << endl;

    for (int i = 0; i < size; i++)
    {
        Contact* current = list[i];
        Contact* previous = NULL;
        while (current != NULL)
        {
            if (current->name == deleteName)
            {
                // Copy details before deleting
                Contact* deletedContact = new Contact(current->name, current->city, current->address, current->number);

                if (previous == NULL)
                {
                    list[i] = current->next;
                }
                else
                {
                    previous->next = current->next;
                }

                s1.push(deletedContact);  // Push the copied contact onto the stack

                cout << endl << setw(45);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
                for (int s = 0; str[s] != '\0'; s++)
                {
                    cout << str[s];
                    Sleep(30);
                }
                cout << endl;
                cout << setw(80) << "-----------------------------------------" << endl;
                cout << endl << setw(75) << "PRESS ENTER KEY TO CONTINUE...";
                cin.get();
                system("cls");
                saveContactsToCSV();
                return;
            }

            previous = current;
            current = current->next;
        }
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
    cout << setw(70) << "Contact not found.\n";
    cout << setw(80) << "-----------------------------------------" << endl;
    cout << endl << setw(75) << "PRESS ENTER KEY TO CONTINUE...";
    cin.get();
    system("cls");
}


void PhoneBook::customSort(string sortField, bool ascending)
{
    for (int i = 0; i < size; i++)
    {
        for (Contact* outer = list[i]; outer != NULL; outer = outer->next)
        {
            for (Contact* inner = outer->next; inner != NULL; inner = inner->next)
            {
                bool swapitplease = false;

                if (sortField == "name")
                {
                    swapitplease = (ascending) ? (outer->name > inner->name) : (outer->name < inner->name);
                }
                else if (sortField == "number")
                {
                    swapitplease = (ascending) ? (outer->number > inner->number) : (outer->number < inner->number);
                }
                else if (sortField == "city")
                {
                    swapitplease = (ascending) ? (outer->city > inner->city) : (outer->city < inner->city);
                }
                else if (sortField == "address")
                {
                    swapitplease = (ascending) ? (outer->address > inner->address) : (outer->address < inner->address);
                }
                else if (sortField == "group")
                {
                    swapitplease = (ascending) ? (outer->group > inner->group) : (outer->group < inner->group);
                }

                if (swapitplease)
                {
                    swap(outer->name, inner->name);
                    swap(outer->number, inner->number);
                    swap(outer->city, inner->city);
                    swap(outer->address, inner->address);
                    swap(outer->group, inner->group);
                }
            }
        }
    }

    saveContactsToCSV();
}

void PhoneBook::loadContactsFromCSV()
{
    ifstream file(u1.getName() + ".csv");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string name, city, address, group, number;
            ss >> name >> number >> city >> address >> group;
            insertContact(name, city, address, number);
            list[name[0] - 65]->group = group;
        }
        file.close();
    }
}

void PhoneBook::saveContactsToCSV()
{
    ofstream file(u1.getName() + ".csv");
    if (file.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            Contact* temp = list[i];
            while (temp != NULL)
            {
                file << temp->name << "\t" << temp->number << "\t" << temp->city << "\t" << temp->address << "\t" << temp->group << endl;
                temp = temp->next;
            }
        }
        file.close();
    }
}
void PhoneBook::recentlydeleted()
{

    cout << endl << endl << endl << endl;
    cout << setw(80) << "-----------------------------------------" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 246);
    temp = s1;
    if (temp.empty())
    {
        cout << setw(70) << "NO DELETED CONTACTS FOUND" << endl;
    }
    while (!temp.empty())
    {
        cout << setw(45) << temp.top()->name << "\t" << temp.top()->number << "\t" << temp.top()->city << "\t" << temp.top()->address << "\t" << temp.top()->group << endl;
        temp.pop();
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
    cout << setw(80) << "-----------------------------------------" << endl;
    cout << endl << setw(75) << "PRESS ENTER KEY TO CONTINUE...";
    cin.get();
    system("cls");
}
void PhoneBook::updateContact(string name)
{
    bool change = 0;
    string str = "INFORMATION UPDATED SUCCESSFULLY";
    string newname, newcity, newaddress, newnumber;
    bool contactFound = false;
    int index =name[0] - 65;
    int s = 0;
    int choice;
    Contact* temp = list[index];
    cout << endl << endl;
    cout << setw(80) << "-----------------------------------------" << endl << endl;
    while (temp != NULL)
    {
        if (temp->name == name)
        {
            contactFound = true;
            if (s == 0)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
                cout << setw(70) << "-----CONTACT FOUND-----" << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);

            }
            do
            {
                cout << setw(85) << "SELECT WHAT YOU WANT TO UPDATE (PRESS 0 TO GO BACK)" << endl << endl;
                cout << "\t\t\t\t1. NAME\t\t2. NUMBER\t3. CITY\t 4. ADDRESS" << endl;
                cout << endl << setw(56) << "KINDLY ENTER:";
                cin >> choice;
                cin.ignore();
                switch (choice)
                {
                case 1:
                    cout << endl << setw(62) << "ENTER THE NEW NAME:";
                    cin >> newname;
                    cin.ignore();
                    change = 1;
                    insertContact(newname, temp->city, temp->address, temp->number);
                    break;
                case 2:
                    do
                    {
                        cout << endl << setw(94) << "Enter The New Number Of Your Contact (UP TO 11 DIGITS): ";
                        cin >> newnumber;
                        if (newnumber.length() != 11)
                        {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
                            cout << setw(56) << "INAVLID FORMAT";
                        }
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
                        Sleep(50);
                        cout << "\r";
                    } while (newnumber.length() != 11);
                    cin.ignore();
                    temp->number = newnumber;
                    break;
                case 3:
                    cout << endl << setw(59) << "ENTER THE NEW CITY:";
                    cin >> newcity;
                    cin.ignore();
                    temp->city = newcity;
                    break;
                case 4:

                    cout << endl << setw(61) << "ENTER THE NEW ADDRESS:";
                    cin >> newaddress;
                    cin.ignore();
                    temp->address = newaddress;
                    break;
                default:
                    if(change)
                    { deleteContact(name);}
                    
                    saveContactsToCSV();
        
                    cout << endl << setw(42);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
                    for (int s = 0; str[s] != '\0'; s++)
                    {
                        cout << str[s];
                        Sleep(30);
                    }
                    cout << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
                }
            } while (choice != 0);
        }
        temp = temp->next;
    }

    if (!contactFound)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
        cout << setw(75) << "-----CONTACT NOT FOUND-----" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
    }
    cout << setw(80) << "-----------------------------------------" << endl;
    cout << endl << setw(75) << "PRESS ENTER KEY TO CONTINUE...";
    cin.get();
    system("cls");

}
int main()
{
    char response;
    bool isRegistered = false;
    bool isLogin;
    string username;
    system("color F0");
    cout << setw(20);
    string intro = "DATA STRUCTURES PROJECT";
    string intro2 = "PHONE DIRECTORY";
    string str1 = "*********** WELCOME TO YOUR PERSONAL PHONEBOOK ***********";
    string str2 = "CONTACT ADDED SUCCESSFULLY";
    string str3 = "DISPLAYING YOUR CONTACTS";
    string str4 = "VIEWING RECENTLY DELETED CONTACTS";
    cout << endl << endl << endl << endl << endl << endl << endl;
    cout << setw(45);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 241);
    for (int z = 0; intro[z] != '\0'; z++)
    {
        cout << intro[z];
        Sleep(40);
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 244);
    cout << endl << endl << setw(48);
    for (int z = 0; intro2[z] != '\0'; z++)
    {
        cout << intro2[z];
        Sleep(40);
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
    cout << endl << endl << setw(68) << "-----TEAM MEMBERS ARE-----" << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
    cout << setw(71) << "1. IBRAHIM AHMED (22K-4341)";
    cout << endl << endl;
    cout << setw(69) << "2. SAAD YOUSUF (22K-4572)";
    cout << endl << endl;
    cout << setw(74) << "3. ABDULHADI YASEEN (22K-4250)";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 244);
    cout << endl<<endl<<endl<< setw(73) << "PRESS ENTER KEY TO CONTINUE...";
    cin.get();
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
    cout << endl << endl << endl
        << setw(70)
        << "Are you a new user? (Y/N): ";
    cin >> response;

    User user;

    if (response == 'Y' || response == 'y')
    {
        // Register a new user
        user.registerUser();
        user.createUserFile();
        isRegistered = true;
    }
    else
    {
        cout<<endl <<setw(64)<< "Enter your username: ";
        cin >> username;

        if (!user.userExists(username))
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
            cout << endl << setw(76) << "User not found. Please register.\n";
            Sleep(1000);
            system("cls");
            user.registerUser();
            user.createUserFile();
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
            cout << endl << setw(53) << "User Found" << endl;
            Sleep(1000);
            system("cls");
        }

        user.setName(username);
        user.loginuser();
        isLogin = true;
    }

    PhoneBook p1(user);
    int choice;
    string name, address, city, number;
    cout << endl << endl << setw(30);
    for (int i = 0; str1[i] != '\0'; i++)
    {

        cout << str1[i];
        Sleep(30);
    }
    do
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
        cout << "\n\n\n\n\t\t\t\t\t*****Select What You Want To Do*****";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 244);
        cout<<endl<<endl << "\n\t\t\t\t1) ADD CONTACT\n\t\t\t\t2) DISPLAY CONTACTS\n\t\t\t\t3) Search Any Contact\n\t\t\t\t4) Delete any contact\n\t\t\t\t5. View Recently Deleted\n\t\t\t\t6. UPDATE CONTACT\n\t\t\t\t0) EXIT"
            << endl
            << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        cout << setw(38) << "ENTER:";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            system("cls");
            cout << endl << endl << endl << endl << endl;

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            cout<<setw(75) << "Enter The Name Of Your Contact:  ";
            cin >> name;
            do
            {
                cout << endl << setw(88) << "Enter The Number Of Your Contact (11 DIGITS): ";
                cin >> number;
                if (number.length() != 11)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
                    cout << setw(56) << "INAVLID FORMAT";
                }
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
                Sleep(50);
                cout << "\r";
            } while (number.length() != 11);
            cout<<endl<< setw(74) << "Enter The City Of Your Contact: ";
            cin >> city;
            cout<<endl<< setw(77) << "Enter The Address Of Your Contact: ";
            cin >> address;
            if (name[0] >= 97 && name[0] <= 122)
            {
                name[0] -= 32;
            }
            p1.insertContact(name, city, address, number);
            cout << endl<<endl<<endl<< setw(50);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
            for (int z = 0; str2[z] != '\0'; z++)
            {
                cout << str2[z];
                Sleep(30);
            }
            Sleep(85);
            system("cls");
            break;
        case 2:
            system("cls");
            cout << endl << endl << endl << setw(50);
            for (int z = 0; str3[z] != '\0'; z++)
            {
                cout << str3[z];
                Sleep(30);
            }
            p1.displayContact();
            cout << endl
                << endl;
            break;
        case 3:
            system("cls");
            cout << endl << endl << endl << endl << endl;

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 245);
            cout << setw(85) << "Enter The Name Of Your Contact You Want To Search:  ";
            cin >> name;
            cin.ignore();
            p1.searchContact(name);
            break;
        case 4:
            system("cls");
            cout << endl << endl << endl << endl << endl;

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 245);
            cout<<setw(85)<< "Enter The Name Of The Contact You Want To Delete: ";
            cin >> name;
            cin.ignore();
            p1.deleteContact(name);
            break;
        case 5:
            system("cls");
            cout << endl << endl << endl << setw(45);
            for (int z = 0; str4[z] != '\0'; z++)
            {
                cout << str4[z];
                Sleep(30);
            }
            p1.recentlydeleted();
            cout << endl
                << endl;
            break;
        case 6:
            system("cls");
            cout << endl << endl << endl << endl << endl;

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 245);
            cout << setw(85) << "Enter The Name Of Your Contact You Want To Update:  ";
            cin >> name;
            cin.ignore();
            p1.updateContact(name);
            break;
        default:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
            cout<<endl<<endl<<setw(50) << "THANK YOU " << user.getName() << "! WILL SEE YOU SOON" << endl;
            break;
        }

    } while (choice != 0);

    return 0;
}
