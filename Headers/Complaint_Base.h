#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <string.h>
using namespace std;

struct Complaint 
{
    char text[500] = "\0";
    char answer[500] = "\0";
    char client[500] = "\0";
    bool seen = false;
    bool answered = false;
};

class Complaint_Base
{
protected:
    Complaint complaint;
    const string fileName;

public:    
    Complaint_Base(const string& FileName) : fileName(FileName) {}

    bool write(const char text[500], const char client[500])
    {
        ifstream fileRead(fileName, ios::in | ios::binary);        
        fileRead.seekg(0, ios::end);
        const size_t size = fileRead.tellg();
        fileRead.seekg(0, ios::beg);

        bool unique = true;
        while(fileRead.tellg() < size)
        {
            fileRead.read(reinterpret_cast<char*> (&complaint), sizeof(complaint));

            if (string(complaint.client) == string(client))
            {
                unique = false;
                break;
            }
        }
        fileRead.close();

        if (unique)
        {
            strcpy(complaint.text, text);
            strcpy(complaint.client, client);
            strcpy(complaint.answer, "*no answer*");
            complaint.answered = false;
            complaint.seen = false;

            ofstream fileWrite(fileName, ios::out | ios::binary | ios::app);
            fileWrite.write(reinterpret_cast<const char*> (&complaint), sizeof(complaint));
            fileWrite.close();        
        }
        return unique;
    }
    
    void view(const Complaint& complaint)
    {
        cout << endl;
        cout << left << setw(25) << "\tName of client";
        cout << " : " << complaint.client << endl;
        cout << left << setw(25) << "\tComplaint";
        cout << " : " << complaint.text << endl;
        cout << left << setw(25) << "\tAnswer status";
        cout << " : " << boolalpha << complaint.answered << endl;
        cout << left << setw(25) << "\tSeen status";
        cout << " : " << boolalpha << complaint.seen << endl;
        cout << left << setw(25) << "\tResponse by Company" ;
        cout << " : " << complaint.answer << endl;
    }

    bool see(Complaint& readIn, const char client[500], bool seenStatus)
    {
        fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
        
        file.seekg(0, ios::end);
        int size = file.tellg();

        file.seekg(0, ios::beg);
        file.seekp(0, ios::beg);

        bool found = false;
        size_t previous;

        while(file.tellg() < size)
        {
            previous = file.tellp();
            file.read(reinterpret_cast<char*> (&readIn), sizeof(readIn));

            if (string(readIn.client) == string(client))
            {
                if (seenStatus)
                {
                    readIn.seen = true;
                    file.seekp(previous, ios::beg);
                    file.write(reinterpret_cast<const char*> (&readIn), sizeof(readIn));
                }

                found = true;
                break;
            }
        }

        file.close();
        return found;
    }

    bool update(const char newComplaint[500], const char client[500], bool& status)
    {
        fstream file(fileName, ios::out | ios::in | ios::binary | ios::ate);
        
        file.seekg(0, ios::end);
        int size = file.tellg();

        file.seekg(0, ios::beg);
        file.seekp(0, ios::beg);

        bool found = false;
        status = false;
        size_t previous;

        while(file.tellg() < size)
        {
            previous = file.tellp();
            file.read(reinterpret_cast<char*> (&complaint), sizeof(complaint));

            if (string(complaint.client) == string(client))
            {   
                if (complaint.answered)
                    status = true;
                else
                {
                    strcpy(complaint.text, newComplaint);
                    file.seekp(previous, ios::beg);
                    file.write(reinterpret_cast<const char*> (&complaint), sizeof(complaint));
                    found = true;
                }
                break;
            }
        }

        file.close();
        return found;
    }

};