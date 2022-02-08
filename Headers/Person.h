#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <conio.h>
#include <cstdio>
#include <cstring>

using namespace std;

// N is the number of goods we sell.
#define N (10)

// Forward declaration of classes
class Person;
class Employee;
class Customer;
class Admin;
class Goods;
class Cash;

// Non-member functions and variables:
void welcome(void)
{
    cout << setw(60) << "WELCOME TO MSM GROCERY CENTER!" << endl << endl;
}
void heading(const string& head)
{
    cout << setw(40) << "" << head << endl << endl;
}

struct DATE
{
    int day, month, year;
};

const string customerFile = "customer.txt";
const string adminFile = "admin.txt";
const string empFile = "emp.txt";

class Person
{
    protected:
        string name, CNIC, email, phone_num, username, password;
        char sex;
        int age;
        double balance = 0;
        DATE DOB;
        string lookup;

        bool input(const string& fileName);
        void input_name(string& name);
        void input_age(int& age);
        void input_sex(char& sex);
        void input_DOB(DATE& DOB, const int& myAge);
        void input_CNIC(string& CNIC);
        void input_email(string& email);
        void input_phone_num(string& phone_num);
        void input_username(string& username);
        void input_password(string& password);
        bool transfer_to_file(const string& fileName);

        // Method for validation
        bool check_name(const string& name);
        bool check_age (const int& age);
        bool check_sex (const char& sex);
        bool check_DOB (const DATE& DOB);
        bool check_CNIC(const string& CNIC);
        bool check_email(const string& email);
        bool check_phone_num(const string& phone_num);
        bool check_password(const string& password);
        bool check_username(const string& username); // no definition provided
        
        // Returns true if entered date of birth is consistent with entered age
        bool consistency(const DATE& DOB, const int& myAge);
        // pure virtual function
        virtual void home() = 0; 

        // *
        // Methods for initialaizing and updating
        bool initialize_goods(Goods* goods);
        bool initialize_balance(string fileName);
        bool initialize_cash(Cash& cash);
        bool update_goods(Goods* goods);
        bool update_balance(string fileName);
        bool update_cash(Cash& cash);

        // Other methods
        void profile(string f);
        void buy(string f);
        //*

    public:
        void login(const string& fileName);   
};
