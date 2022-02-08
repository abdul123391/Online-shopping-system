#include "Customer.h"
#include "Complaint_C.h"

// Customers are asked to choose between signup and login
void Customer::start(void)
{
    bool go = true;
    int ans;

    while(go)
    {
        system("cls");

        welcome();
        cout<< " You want to:\n"
            << "\t1) Sign up\n"
            << "\t2) Login\n"
            << "\t3) Back\n";
        
        cout << "\n Your choice > ";
        cin >> ans;
        fflush(stdin);

        switch (ans)
        {
        case 1:
            signup();
            getch();
            break;
        
        case 2:
            login(customerFile);
            getch();
            break;
        
        case 3:
            go = false;
            break;
    
        default:
            cout << " Invalid choice!";
            cout << "\n Press any key to go enter again...\n";
            getch();
            break;
        }
        fflush(stdin);
    }
}

void Customer::signup(void)
{
    system("cls");
    heading("SIGN-UP");

    if (input(customerFile))
        cout << endl << "\nAccount successfully made.\nPress any key to exit.";
    else
        cout << endl << "\nSorry! An error occured while processing the data.\nPress any key to exit.";
    getch();
}

void Customer::home()
{
    bool go = true;
    int ans;

    while(go)
    {
        system("cls");

        heading("HOME");
        cout<< " You want to:\n"
            << "\t1) Buy goods\n"
            << "\t2) Write a complaint\n"
            << "\t3) View profile\n"
            << "\t4) Log out\n";
        
        cout << "\n Your choice > ";
        cin >> ans;
        fflush(stdin);

        switch (ans)
        {
        case 1:
            buy(customerFile);
            getch();
            break;
        
        case 2:
            complain();
            getch();
            break;
        
        case 3:
            profile(customerFile);
            getch();
            break;
            
        case 4:
            go = false;
            break;
    
        default:
            cout << " Invalid choice!";
            cout << "\n Press any key to go enter again...\n";
            getch();
            break;
        }
        fflush(stdin);
    }
}

void Customer::complain(void)
{
    Complaint_C complaint(username.c_str(), "complaint.dat");
    bool Go = true;
    int Ans;
    
    while(Go)
    {
        system("cls");
        cout << " Customer's options:\n";
        cout << "\t1) Write a complaint\n";
        cout << "\t2) Re-view your complaint\n";
        cout << "\t3) Change a complaint\n";
        cout << "\t4) Go Back\n";
        cout << " Choose > ";

        fflush(stdin);
        cin >> Ans;
        switch (Ans)
        {
        case 1:
            {
                char text[500];

                cout << " Enter the complaint\n > ";
                fflush(stdin);
                cin.getline(text, sizeof(text) + 1);

                if (complaint.write(text))
                    cout << " Your complain has been written\b";
                else
                    cerr << " You have already registered a complaint" << endl;
                fflush(stdin);
                cin.get();
            }
            break;
        
        case 2:
            complaint.reView();
            fflush(stdin);
            cin.get();
            break;
        
        case 3:
            {
                char newText[500];
                bool AnsStatus; 

                cout << " Enter the new complaint\n > ";
                fflush(stdin);
                cin.getline(newText, sizeof(newText) + 1);

                if (complaint.update(newText, AnsStatus))
                    cout << " The complaint has been changed\n";
                else
                {
                    if (AnsStatus)
                        cerr << " Our employee has already answered your complaint";
                    else
                        cerr << " Complaint not found" << endl;
                }
                fflush(stdin);
                cin.get();
            }
            break;
        
        case 4:
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
