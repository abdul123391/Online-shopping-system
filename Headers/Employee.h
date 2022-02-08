#pragma once
#include "Person.h"

class Employee: public Person
{
    const string empFile;
    void home() override;

    protected:
        void answer(void);
    public:
        Employee(const string& fileName) : empFile(fileName) {}
};
