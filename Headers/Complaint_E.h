#pragma once
#include "Complaint_Base.h"

class Complaint_E final : public Complaint_Base
{

public:
    Complaint_E(const string& FileName) : Complaint_Base(FileName) {}
   
    bool answer(const char ans[500], const char client[500])
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
            file.read(reinterpret_cast<char*> (&complaint), sizeof(complaint));

            if (string(complaint.client) == string(client))
            {
                strcpy(complaint.answer, ans);
                complaint.seen = true;
                complaint.answered = true;

                file.seekp(previous, ios::beg);
                file.write(reinterpret_cast<const char*> (&complaint), sizeof(complaint));

                found = true;
                break;
            }
        }

        file.close();
        return found;
    }

    void view(bool showDetails)
    {
        ifstream file(fileName, ios::in | ios::binary);
        file.seekg(0, ios::end);
        const size_t size = file.tellg();
        file.seekg(0, ios::beg);

        for(size_t i = 1; file.tellg() < size; i++)
        {
            file.read(reinterpret_cast<char*> (&complaint), sizeof(complaint));
            if (showDetails)
                Complaint_Base::view(complaint);
            else
                cout << left << setw(10) << "\t" << i << ") " << complaint.client << endl;
        }
        
        file.close();
    }

    void clear()
    {
        ofstream file(fileName, ios::trunc);
        file.close();
    }

};