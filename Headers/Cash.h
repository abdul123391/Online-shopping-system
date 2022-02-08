#pragma once

class Cash
{
    double initial, in, out, finl;
    friend class Person;

    public:
        double get_final_cash(void);
        
        // Operator overloading
        void operator +(double i); // Cash in
        void operator -(double i); // Cash out
};

void Cash::operator +(double i) // Operator for Cash in
{
    in += i;
}

void Cash::operator -(double i) // Operator for Cash out
{
    out += i;
}

inline double Cash::get_final_cash(void) // Returns final cash
{  
    return finl;
}
