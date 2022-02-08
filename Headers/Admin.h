#pragma once
#include "Employee.h"

class Admin: public Employee
{
    const string adminFile;
    void home() override;

    //*
    void add_employee(void);
    void view(string f);
    void search(string s, string f, int i);
    void balance(string f, int r);
    void ban(string f, int r);
    void accounts(void);

    public:
        void stock(void); // friend of goods
        Admin(const string& fileName) : adminFile(fileName), Employee(fileName) {}
    //*
};