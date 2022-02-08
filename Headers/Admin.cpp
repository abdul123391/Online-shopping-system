#include "Admin.h"
#include "Goods.h"
#include "Cash.h"

void Admin::home()
{
    bool go = true;
    int ans;

    while(go)
    {
        system("cls");

        heading("HOME");
        cout<< " You want to:\n"
            << "\t1) Buy goods\n"
            << "\t2) Answer complaints\n"
            << "\t3) View profile\n"
            << "\t4) Add employees\n"
            << "\t5) View customer records\n"
            << "\t6) View employee records\n"
            << "\t7) Stock\n"
            << "\t8) Accounts\n"
            << "\t9) Back\n";
        
        cout << "\n Your choice > ";
        cin >> ans;
        fflush(stdin);

        switch (ans)
        {
        case 1:
            buy(adminFile);
            getch();
            break;
        
        case 2:
            answer();
            getch();
            break;
        
        case 3:
            profile(adminFile);
            break;

        case 4:
            add_employee();
            break;

        case 5:
            view(customerFile);
            break;

        case 6:
            view(empFile);
            break;

        case 7:
            stock();
            break;

        case 8:
            accounts();
            break;
            
        case 9:
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

void Admin::add_employee(void) // Makes an employee's account
{
    system("cls");
    heading("EMPLOYEE ACCOUNT");

    if (input(empFile))
        cout << endl << "\nEmployee account has been successfuly made.\nPress Z to go back: ";
    else
        cout << endl << "\nSorry! An error occured while processing the data.\nPress Z to go back: ";
    char c;
    cin >> c;
    fflush(stdin);
    if (c != 'Z') // Validation
    {
        do
        {
            cout << "Invalid character! Please re-enter: ";
            cin >> c;
            fflush(stdin);
        }
        while (c != 'Z');
    }
}

void Admin::view(string f) // Displays records of customers or employees
{
    system("cls");
    if (f == customerFile)
        heading("CUSTOMER RECORDS");
    else
        heading("EMPLOYEE RECORDS");
    ifstream file(f); // Opening the file
    if (!file.is_open()) // Ensuring that file opens correctly
    {
        cout << "Sorry! An error occured while processing the data.\nPress any key to exit.";
        getch();
        exit(1);
    }
    // Reading and displaying the file
    string s;
    while (getline(file, s))
        cout << s << endl;
    if (file.fail()) // Ensuring that the reading operation was carried out successfully
    {
        cout << endl << "Sorry! An error occured while processing the data.\nPress any key to exit.";
        getch();
        return;
    }
    file.close(); // Closes the file
    cout << endl << "Press S to search, or Z to go back: ";
    char c;
    cin >> c;
    fflush(stdin);
    if (c != 'Z' && c != 'S') // Validation
    {
        do
        {
            cout << "Invalid character! Please re-enter: ";
            cin >> c;
            fflush(stdin);
        }
        while (c != 'Z' && c != 'S');
    }
    if (c == 'Z')
        return;
    else
    {
        cout << endl << "1) Search by CNIC\n2) Search by email\n3) Search by phone number" <<
        "\n4) Search by username\n5) Search by password\n\nOption: ";
        cin >> c;
        fflush(stdin);
        if (c < '1' || c > '5') // Validation
        {
            do
            {
                cout << "Invalid choice! Re-enter: ";
                cin >> c;
                fflush(stdin);
            }
            while (c < '1' || c > '5');
        }
        system("cls");
        heading("SEARCHING");
        switch(c)
        {
            case '1':
                search("CNIC", f, 6);
                break;
            case '2':
                search("Email", f, 5);
                break;
            case '3':
                search("Phone number", f, 4);
                break;
            case '4':
                search("Username", f, 3);
                break;
            default:
                search("Password", f, 2);
                break;    
        }
    }
}

void Admin::search(string s, string f, int i) // Searches for the record that matches the provided detail
{
    string ans, read;
    bool b = true; // serves as a flag
    cout << s << ": ";
    getline(cin, ans);
    fflush(stdin);
    ifstream file(f); // Opening the file
    if (!file.is_open()) // Ensuring that file opens correctly
    {
        cout << "Sorry! An error occured while processing the data.\nPress any key to exit.";
        getch();
        return;
    }
    int l = 1, n = 1; // l stores the line number, n stores the record number
    while (!file.eof())
    {
        char c = file.get();
        if (c == '\n')
            l++;
        if (l == 11 * n - i)
        {
            file.seekg(s.length() + 2, ios::cur);
            c = file.get();
            while (c != '\n')
            {
                read.push_back(c);
                c = file.get();
            }
            l++;
            if (read != ans)
                n++;
            else
            {
                b = false;
                cout << endl;
                file.seekg(0); // Taking the read pointer to the start of the file
                l = 1;
                while (getline(file, read)) // Printing the record
                {
                    if (l >= (11 * n - 10) && l <= (11 * n - 1))
                        cout << s << endl;
                    l++;
                }
                if (file.fail()) // Ensuring that the reading operation was carried out successfully
                {
                    cout << endl << "Sorry! An error occured while processing the data.\nPress any key to exit.";
                    getch();
                    return;
                }
                file.close(); // Closes the file
                if (f == customerFile)
                    cout << endl << "Press B to update balance, N to ban, and Z to go back: ";
                else
                    cout << endl << "Press B to update balance, N to fire, and Z to go back: ";
                cin >> c;
                fflush(stdin);
                if (c != 'B' && c != 'N' && c != 'Z') // Validation
                {
                    do
                    {
                        cout << "Invalid choice! Please re-enter: ";
                        cin >> c;
                        fflush(stdin);
                    }
                    while (c != 'B' && c != 'N' && c != 'Z');
                }
                switch(c)
                {
                    case 'B':
                        balance(f, n);
                        break;
                    case 'N':
                        ban(f, n);
                        break;
                    default:
                        break;
                }
                break;
            }
        }
    }
    if (b)
    {
        cout << "Incorrect " << s << ". Please re-enter. ";
        read.clear();
        file.close(); // Closes the file
        search(s, f, i);
    }
}

void Admin::balance(string f, int r) // Updates the balance of the record passed as argument
{
    double bal;
    cout << fixed << showpoint << setprecision(2);
    cout << endl << "Enter new balance: $";
    cin >> bal;
    if (bal < 0) // Validation
    {
        do
        {
            cout << "Balance cannot be negative. Please re-enter: $";
            cin >> bal;
        }
        while (bal < 0);
    }
    ifstream old_file(f);
    ofstream new_file("tmp.txt");
    if (!old_file.is_open() || !new_file.is_open()) // Ensuring that the files opened correctly
    {
        cout << endl << "Sorry! An error occured while processing the data.\nPress any key to exit.";
        getch();
        return;
    }
    int l = 1; // stores line number
    string s;
    while (!old_file.eof()) // Updating balance and copying the rest of the contents
    {
        getline(old_file, s);
        if (l == 11 * r - 1)
            new_file << "Balance: " << bal << endl;
        else
            new_file << s << endl;
        l++;
    }
    old_file.close(); // closes the file
    new_file.close(); // closes the file
    remove(f.c_str()); // deletes the old file
    rename("tmp.txt", f.c_str()); // renames the new file to the name of the old file
    cout << endl << "Balance updated successfully! Press Z to go back: ";
    char c;
    cin >> c;
    fflush(stdin);
    if (c != 'Z') // Validation
    {
        do
        {
            cout << "Invalid character! Please re-enter: ";
            cin >> c;
            fflush(stdin);
        }
        while (c != 'Z');
    }
}

void Admin::ban(string f, int r) // Deletes the record passed as argument
{
    ifstream old_file(f);
    ofstream new_file("tmp.txt");
    if (!old_file.is_open() || !new_file.is_open()) // Ensuring that the files opened correctly
    {
        cout << endl << "Sorry! An error occured while processing the data.\nPress any key to exit.";
        getch();
        return;
    }
    int l = 0; // stores line number
    string s;
    while (!old_file.eof()) // Deleting the record and copying the rest of the records
    {
        getline(old_file, s);
        l++;
        if (l >= 11 * r - 10 && l <= 11 * r - 1)
            continue;
        new_file << s << endl;
    }
    old_file.close(); // closes the file
    new_file.close(); // closes the file
    remove(f.c_str()); // deletes the old file
    rename("tmp.txt", f.c_str()); // renames the new file to the name of the old file
    if (f == "customer.txt")
        cout << endl << "Customer banned! Press Z to go back: ";
    else
        cout << endl << "Employee fired! Press Z to go back: ";
    char c;
    cin >> c;
    fflush(stdin);
    if (c != 'Z') // Validation
    {
        do
        {
            cout << "Invalid character! Please re-enter: ";
            cin >> c;
            fflush(stdin);
        }
        while (c != 'Z');
    } 
}

void Admin::stock(void) // Displays details of goods and allows modification and re-ordering
{
    system("cls");
    heading("STOCK REPORT");
    Goods g[N];
    if (!initialize_goods(g))
    {
        cout << "Sorry! An error occured while processing the data.\nPress any key to exit.";
        getch();
        return;
    }
    for (int i = 0; i < N; i++)
    {
        cout << "Name: " << g[i].name << endl << "Stock: " << g[i].stock << endl << "Cost: " << g[i].cost
        << endl << "Price: " << g[i].price << endl << "Reorder Level: " << g[i].reorder_level << endl <<
        "Reorder Amount: " << g[i].reorder_amount << endl << endl;
    }
    char c;
    string s;
    int a, index;
    while (true)
    {
        cout << "Press O to order, M to modify or Z to go back: ";
        cin >> c;
        fflush(stdin);
        if (c != 'O' && c != 'M' && c != 'Z') // Validation
        {
            do
            {
                cout << "Invalid character! Please re-enter: ";
                cin >> c;
                fflush(stdin);
            }
            while (c != 'O' && c != 'M' && c != 'Z');
        }
        if (c == 'Z')
            break;
        else
        {
            cout << endl << "Name of good: ";
            getline(cin, s);
            fflush(stdin);
            bool b = false; // false if entered name is incorrect
            for (int i = 0; i < N; i++)
            {
                if (g[i].name.compare(s) == 0)
                {
                    b = true;
                    index = i;
                    break;
                }
            }
            if (!b) // Displays error if incorrect name entered
            {
                cout << endl << "No such good in inventory! Press Z to go back: ";
                cin >> c;
                fflush(stdin);
                if (c != 'Z') // Validation
                {
                    do
                    {
                        cout << "Invalid character! Please re-enter: ";
                        cin >> c;
                        fflush(stdin);
                    }
                    while (c != 'Z');
                }
                break;
            }
            else
            {
                if (c == 'O') // Manual re-order
                {        
                    Cash csh;
                    if (!initialize_cash(csh))
                    {
                        cout << "Sorry! An error occured while processing the data.\nPress any key to exit.";
                        getch();
                        return;
                    }
                    cout << endl << "Quantity to order: ";
                    cin >> a;
                    fflush(stdin);
                    if (a <= 0 || csh.get_final_cash() < (a * g[index].cost)) // Validation
                    {
                        do
                        {
                            if (a <= 0)
                                cout << "Number must be positive. Please re-enter: ";
                            else
                                cout << "Not enough cash! Cash: $" << csh.get_final_cash() << "\nPlease re-enter: ";
                            cin >> a;
                            fflush(stdin);
                        }
                        while (a <= 0);
                    }
                    g[index].stock += a; // Increasing stock
                    csh - (a * g[index].cost); // Decreasing cash
                    if (!update_goods(g) || !update_cash(csh))
                    {
                        cout << "Sorry! An error occured while processing the data.\nPress any key to exit.";
                        getch();
                        return;
                    }
                    cout << endl << "Order has been successfully placed! Press Z to go back: ";
                    cin >> c;
                    fflush(stdin);
                    if (c != 'Z') // Validation
                    {
                        do
                        {
                            cout << "Invalid character! Please re-enter: ";
                            cin >> c;
                            fflush(stdin);
                        }
                        while (c != 'Z');
                    }
                    break;
                }
                else // Modifying
                {
                    cout << endl << "New price: $";
                    cin >> g[index].price;
                    if (g[index].price <= 0) // Validation
                    {
                        do
                        {
                            cout << "Price must be positive. Please re-enter: $";
                            cin >> g[index].price;
                            fflush(stdin);
                        }
                        while (g[index].price <= 0);
                    }
                    cout << "New re-order level: ";
                    cin >> g[index].reorder_level;
                    if (g[index].reorder_level <= 0) // Validation
                    {
                        do
                        {
                            cout << "Reorder level must be positive. Please re-enter: ";
                            cin >> g[index].reorder_level;
                            fflush(stdin);
                        }
                        while (g[index].reorder_level <= 0);
                    }
                    cout << "New re-order amount: ";
                    cin >> g[index].reorder_amount;
                    fflush(stdin);
                    if (g[index].reorder_amount <= 0) // Validation
                    {
                        do
                        {
                            cout << "Reorder amount must be positive. Please re-enter: ";
                            cin >> g[index].reorder_amount;
                            fflush(stdin);
                        }
                        while (g[index].reorder_amount <= 0);
                    }
                    if (!update_goods(g))
                    {
                        cout << "Sorry! An error occured while processing the data.\nPress any key to exit.";
                        getch();
                        return;
                    }
                    cout << endl << "Changes successfully made! Press Z to go back: ";
                    cin >> c;
                    fflush(stdin);
                    if (c != 'Z') // Validation
                    {
                        do
                        {
                            cout << "Invalid character! Please re-enter: ";
                            cin >> c;
                            fflush(stdin);
                        }
                        while (c != 'Z');
                    }
                    break;
                }
            }
        }
    }
}

void Admin::accounts(void) // Displays financial details
{
    system("cls");
    heading("FINANCIAL REPORT");
    ifstream file("cash.txt"); // Opening the file
    if (!file.is_open()) // Ensuring that the file opened correctly
    {
        cout << "Sorry! An error occured while processing the data.\nPress any key to exit.";
        getch();
        return;
    }
    string s;
    while (getline(file, s)) // Printing the contents of the file
        cout << s << endl;
    if (file.fail()) // Ensuring that the reading operation was carried out successfully
    {
        cout << endl << "Sorry! An error occured while processing the data.\nPress any key to exit.";
        getch();
        return;
    }
    file.close(); // Closes the file
    cout << "\nPress Z to go back: ";
    char c;
    cin >> c;
    fflush(stdin);
    if (c != 'Z') // Validation
    {
        do
        {
            cout << "Invalid character! Please re-enter: ";
            cin >> c;
            fflush(stdin);
        }
        while (c != 'Z');
    }
}
