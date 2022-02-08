#pragma once
#include "Person.h"

class Customer: public Person
{
    const string customerFile;

    void signup(void);
    void home() override;
    void complain(void);

    public:
        Customer(const string& fileName) : customerFile(fileName) {}
        void start(void);
};
