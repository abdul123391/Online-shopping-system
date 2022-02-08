#include "Employee.h"
#include "Complaint_E.h"

void Employee::home()
{

    bool go = true;
    int ans;

    while(go)
    {
        system("cls");

        heading("HOME");
        cout<< " You want to:\n"
            << "\t1) Buy goods\n"
            << "\t2) Answer a complaint\n"
            << "\t3) View profile\n"
            << "\t4) Log out\n";
        
        cout << "\n Your choice > ";
        cin >> ans;
        fflush(stdin);

        switch (ans)
        {
        case 1:
            buy(empFile);
            getch();
            break;
        
        case 2:
            answer();
            getch();
            break;
        
        case 3:
            profile(empFile);
            getch();
            break;
            
        case 4:
            go = false;
            break;
    
        default:
            cout << " Invalid choice!";
            cout << " Press any key to go enter again...\n";
            getch();
            break;
        }
    }
}

void Employee::answer(void)
{
    Complaint_E complaint("complaint.dat");
    bool Go = true;
    int Ans;

    while(Go)
    {
        system("cls");
        
        cout << " Employee's options:\n";
        cout << "\t1) See a complaint\n";
        cout << "\t2) See a complaint anonymously\n";
        cout << "\t3) Answer a complaint\n";
        cout << "\t4) View all complaintees\n";
        cout << "\t5) View all complaints\n";
        cout << "\t6) Clear all complaints\n";
        cout << "\t7) Go back\n";
        cout << " Choose > ";
        fflush(stdin);
        cin >> Ans;

        switch (Ans)
        {
        case 1:
            {
                char name[500];
                Complaint readIn;

                cout << " Enter the name of customer > ";
                fflush(stdin);
                cin.getline(name, sizeof(name) + 1);

                if (complaint.see(readIn, name, true))
                    complaint.Complaint_Base::view(readIn);
                else
                    cerr << " \"" << name << "\" has no complaint" << endl;
                fflush(stdin);
                cin.get();
            }
            break;
        
        case 2:
            {
                char name[500];
                Complaint readIn;

                cout << " Enter the name of customer > ";
                fflush(stdin);
                cin.getline(name, sizeof(name) + 1);

                if (complaint.see(readIn, name, false))
                    complaint.Complaint_Base::view(readIn);
                else
                    cerr << " \"" << name << "\" has no complaint" << endl;
                fflush(stdin);
                cin.get();
            }
            break;
        
        case 3:
            {
                char name[500], ans[500];

                cout << " Enter the name of customer > ";
                fflush(stdin);
                cin.getline(name, sizeof(name) + 1);

                cout << " Enter the response\n > ";
                fflush(stdin);
                cin.getline(ans, sizeof(ans) + 1);

                if (complaint.answer(ans, name))
                    cout << " The complaint has been answered\n";
                else
                    cerr << " \"" << name << "\" has no complaint" << endl;
                fflush(stdin);
                cin.get();
            }
            break;
        
        case 4:
            complaint.view(false);
            fflush(stdin);
            cin.get();
            break;
        
        case 5:
            complaint.view(true);
            fflush(stdin);
            cin.get();
            break;
        
        case 6:
            complaint.clear();
            cout << " All records are cleared\n";
            fflush(stdin);
            cin.get();
            break;
        
        case 7:
            Go = false;
            break;
        
        default:
            cerr << " Invalid input!\n";
            fflush(stdin);
            cin.get();
            break;
        }
    }
}
