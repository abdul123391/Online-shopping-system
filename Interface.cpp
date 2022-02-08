#include "Headers/Admin.h"
#include "Headers/Admin.cpp"
#include "Headers/Employee.h"
#include "Headers/Employee.cpp"
#include "Headers/Customer.h"
#include "Headers/Customer.cpp"
#include "Headers/Person.h"
#include "Headers/Person.cpp"

int main()
{
    bool go = true;
    int ans;

    while(go)
    {        
        system("cls");
        welcome();
        cout<< " Proceed as:\n"
            << "\t1) Admin\n"
            << "\t2) Employee\n"
            << "\t3) Customer\n"
            << "\t4) Exit\n";
        
        cout << "\n Your choice > ";
        cin >> ans;
        fflush(stdin);

        switch (ans)
        {
        case 1:
            {
                Admin admin(adminFile);
                admin.login(adminFile);
                getch();
            }
            break;
        
        case 2:
            {
                Employee employee(empFile);
                employee.login(empFile);
                getch();
            }
            break;
        
        case 3:
            {
                Customer customer(customerFile);
                customer.start();
            }
            break;
        
        case 4:
            go = false;
            break;
    
        default:
            cout << " Invalid choice!";
            getch();
            break;
        }

        fflush(stdin);
    }

    return 0;
}