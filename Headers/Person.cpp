#include "Person.h"
#include "Goods.h"
#include "Cash.h"

bool Person::input(const string& fileName)
{
    input_username(username);
    input_password(password);
    input_name(name);
    input_age(age);
    input_sex(sex);
    input_DOB(DOB, age);
    input_CNIC(CNIC);
    input_email(email);
    input_phone_num(phone_num);
    return transfer_to_file(fileName);
}

void Person::input_name(string& name)
{
    cout << "\n Name: ";
    getline(cin, name);
    fflush(stdin);

    if (check_name(name))
        return;

    input_name(name);
}

bool Person::check_name(const string& name)
{
    // Ensuring only letters and spaces are allowed in name
	for (const char& c : name) 
	{
		if ((c < 'A' && c != ' ') || (c > 'Z' && c < 'a') || c > 'z')
		{
			cout << " Name must only contain letters and spaces.\n";
			return false;
		}
	}
    return true;
}

void Person::input_age(int& age)
{
    cout << " Age: ";
	cin >> age;
    fflush(stdin);

    if (check_age(age))
        return;
    
    input_age(age);
}

bool Person::check_age (const int& age)
{
    if (age < 10 || age > 99)
    {	
        if (age < 0)
            cout << " Age cannot be negative.\n";
        else if (age >= 0 && age < 10)
            cout << " You must be at least 10 years old.\n";
        else
            cout << " You must be between 10 and 99 inclusive.\n";
        return false;
    }
    else
        return true;
}

void Person::input_sex(char& sex)
{
    cout << " Sex (M or F or O): ";
	cin >> sex;
    fflush(stdin);
    
    if (check_sex(sex))
        return;
    
    input_sex(sex);
}

bool Person::check_sex (const char& sex)
{
	if (sex == 'M' || sex == 'F' || sex == 'O')
        return true;
    
    cout << " Invalid input\n";
    return false;
}

void Person::input_DOB(DATE& DOB, const int& myAge)
{
    cout << " Date of birth (mm/dd/yyyy): ";
	scanf("%d/%d/%d", &DOB.month, &DOB.day, &DOB.year);
    fflush(stdin);

    if (check_DOB(DOB))
        if (consistency(DOB, myAge))
            return;

	input_DOB(DOB, myAge);
}

bool Person::check_DOB (const DATE& DOB)
{
     // Validation for year
    if (DOB.year > 2011 || DOB.year < 1921)
	{
		cout << " Year must be between 1921 and 2011 inclusive.\n";
        return false;
	}

     // Validation for month
	if (DOB.month > 12 || DOB.month < 1)
	{
		cout << " Month must be between 1 and 12 inclusive.\n";
		return false;
	}

     // Validation for day
	switch(DOB.month)
	{
	    case 1:
	    case 3:
	    case 5:
	    case 7:
	    case 8:
	    case 10:
	    case 12:
	    	if (DOB.day < 1 || DOB.day > 31)
	    	{
	    		cout << " Day must be between 1 and 31.\n";
		        return false;
			}
            break;

		case 4:
		case 6:
		case 9:
		case 11:
			if (DOB.day < 1 || DOB.day > 30)
	    	{
	    		cout << " Day must be between 1 and 30.\n";
                return false;
			}
            break;

		default:
             // Assuming no lunar year
			if (DOB.day < 1 || DOB.day > 28)
			{
				cout << " Day must be between 1 and 28.\n";
                return false;
			}
            break;
	}
    return true;    
}

bool Person::consistency(const DATE& DOB, const int& myAge)
{
    // Determining current date/time based on current system
    // 'now' now stores the number of seconds elapsed since Jan 1, 1970
    time_t now = time(0);

    // Returns a pointer to the tm structure (defined in ctime)  
    // representing local time and date

    tm* t = localtime(&now); 
    // t->tm_mday stores day, t->tm_mon stores month (from 0 to 11) and t->tm_year stores years since 1900
   
    // Calculating age
    int age;
    if (DOB.month < (t->tm_mon + 1))
        age = (t->tm_year + 1900) - DOB.year;
    else if (DOB.month > (t->tm_mon + 1))
        age = (t->tm_year + 1900) - DOB.year - 1; // Person's birthday this year is yet to arrive
    else
    {
        if (DOB.day > t->tm_mday)
            age = (t->tm_year + 1900) - DOB.year - 1; // Person's birthday this year is yet to arrive
        else
            age = (t->tm_year + 1900) - DOB.year;
    }

    // Comparing age
    if (age == myAge)
        return true;

    cout << "Date of birth is not consistent with entered age.\n";
    return false;
}

void Person::input_CNIC(string& CNIC)
{
    cout << " CNIC: ";
    getline(cin, CNIC);
    fflush(stdin);

    if (check_CNIC(CNIC))
        return;

    input_CNIC(CNIC);
}

bool Person::check_CNIC(const string& CNIC)
{
    // Ensuring CNIC contains 15 characters
    if (CNIC.length() != 15)
    {
        cout << " CNIC must be contain 15 characters.\n";
        return false;
    }

    // Ensuring only numbers and - allowed in CNIC
	for (const char& c : CNIC) 
	{
		if ((c < '0' && c != '-') || c > '9')
		{
			cout << " CNIC must contain only numbers and -\n";
			return false;
		}
	}
    
    // Ensuring correct pattern
    for (int i = 0, l = CNIC.length(); i < l; i++)
    {
        if (i == 5 || i == 13)
        {
            if (CNIC[i] != '-')
            {
                cout << "Incorrect pattern.\n";
			    return false;
            }
        }
        else if (CNIC[i] == '-')
        {
            cout << "Incorrect pattern.\n";
            return false;
        }
    }

    return true;
}

void Person::input_email(string& email)
{
    cout << " Email: ";
    getline(cin, email);
    fflush(stdin);

    if (check_email(email))
        return;
    
    input_email(email);
}

bool Person::check_email(const string& email)
{
    bool found = false;

    // Ensuring there is an '@' in the email
    for (const char& c : email)
    {
        if (c == '@')
        {
            found = true;
            break;
        }
    }

    if(!found)
    {
        cout << " Email address must contain a '@'\n";
        return false;
    }

    return true;
}

void Person::input_phone_num(string& phone_num)
{
    cout << " Phone Number: ";
    getline(cin, phone_num);
    fflush(stdin);
    
    if (check_phone_num(phone_num))
        return;

    input_phone_num(phone_num);
}

bool Person::check_phone_num(const string& phone_num)
{
    // Ensuring only numbers, *, #, and - are allowed in phone number
	for (const char& c : phone_num) 
    {
        if ((c < '0' && c != '-' && c != '*' && c != '#') || c > '9')
		{
			cout << " Phone number can only contain numbers, *, #, and -\n";
            return false;
		}
    }
    return true;
}

inline void Person::input_username(string& username)
{
    cout << " Username: ";
    getline(cin, username);
    fflush(stdin);
}

void Person::input_password(string& password)
{
	cout << " Password: ";
    
    char c;
    password.clear();
	while (1)
	{    
    	c = getch();

        if (c == 13)     // 13 is ASCII code of Enter
            break;

		cout << "*";
		password.push_back(c);
	}

    if (check_password(password))
        return;
    
    input_password(password);
}

bool Person::check_password(const string& password)
{
	// Confirming password
	cout << "\n Confirm Password: ";

	string confirm;
	char c;
	while (1)
	{    
    	c = getch();

        if (c == 13)     // 13 is ASCII code of Enter
            break;

		cout << "*";
		confirm.push_back(c);
	}

	// Comparing the two passwords
	if (password != confirm)
	{
		cout << "\n Password must be same.\n";
        return false;
	}

    return true;
}

bool Person::transfer_to_file(const string& fileName)
{
    ofstream file(fileName, ios::app); // Opening the file in append mode

    if (!file.is_open()) // Ensuring that the file opened successfully
        return false; // Indicates error

    // Writing to file
    file << "Username: " << username << endl
        << "Password: " << password << endl 
        << "Name: " << name << endl 
        << "Age: " << age << endl 
        << "Sex: " << sex << endl
        << "Date of birth: " << DOB.month 
        << "/" << DOB.day 
        << "/" << DOB.year << endl 
        << "CNIC: " << CNIC << endl 
        << "Email: " << email << endl 
        << "Phone number: " << phone_num << endl 
        << "Balance: " << 0 << endl 
        << endl;

    // Ensuring that the writing operation was carried out successfully
    if (file.fail())
    {
        file.close();
        return false; // Indicates error
    }
    else
    {
        file.close();
        return true; // Indicates successful termination
    }
}

void Person::login(const string& fileName)
{
    cout << " Username : ";
    getline(cin, username);
    fflush(stdin);
	
	cout << " Password : ";
    char c;
    password.clear();
    while (1)
	{    
    	c = getch();

        if (c == 13)     // 13 is ASCII code of Enter
            break;

		cout << "*";
		password.push_back(c);
	}

    ifstream file(fileName); // Opening the file
    string line;
    bool userFound = false, passFound = false;
    
    if (!file.is_open()) // Ensuring that the file opened successfully
    {
        cout << endl << "\nSorry! An error occured while processing the data.\nPress any key to exit.";
        getch();
        return;
    }
    
    while(!file.eof())
    {
        getline(file, line);
        if(line == ("Username: " + username))
        {
            userFound = true;
            getline(file, line);
            if(line == ("Password: " + password))
            {
                passFound = true;
                this->lookup = "Username: " + username;
                file.close();
                home();
                return;
            }

        }
    }

    if (!userFound && !passFound)
        cout << "\n Incorrect username" << endl;

    else if (userFound && !passFound)
        cout << "\n Incorrect password" << endl;

    file.close();
    login(fileName);
}

void Person::profile(string fileName) // Displays profile
{
    system("cls");
    heading("PROFILE");

    ifstream file(fileName); // Opens the file
    if (!file.is_open()) // Ensuring that the file opened successfully
    {
        cout << "Sorry! An error occured while processing the data.\nPress any key to exit.";
        getch();
        return ;
    }

    // Reading and displaying the required record
    string line;
    while (!file.eof())
    {
        getline(file, line);
        if (line == this->lookup)
        {
            while(1)
            {
                cout << " --> " << line << endl;
                getline(file, line);
                if (line == "")
                    break;
            }
            break;
        }
    }
}

bool Person::initialize_goods(Goods* goods) // Initializes array of goods from file
{
    ifstream file("goods.txt"); // Opening the file

    if (!file.is_open()) // Ensuring that the file opened correctly
        return false; // Indicates error

    string str;
    for(int i = 0; i < N; i++) // Populating array of goods
    {
        file >> str;
        file >> str;
        goods[i].name = str;

        file >> str;
        file >> str;
        goods[i].stock = stoi(str);

        file >> str;
        file >> str;
        goods[i].cost = stod(str);

        file >> str;
        file >> str;
        goods[i].price = stod(str);        

        file >> str;
        file >> str;
        file >> str;
        goods[i].reorder_level = stoi(str);
        
        file >> str;
        file >> str;
        file >> str;
        goods[i].reorder_amount = stoi(str);

        goods[i].bought = false;
    }
    file.close();
    return true; // Indicates successful termination
}

bool Person::initialize_balance(string fileName) // Initializes balance from file
{
    ifstream file(fileName); // Opening the file
    
    if (!file.is_open()) // Ensuring that the file opened correctly
        return false; // Indicates error

    string str;
    while (!file.eof()) // Intializing balance
    {
        getline(file, str);
        if (str == this->lookup)
        {
            while(getline(file, str))
            {
                if (str.substr(0, 7) == "Balance")
                {
                    this->balance = stod(str.substr(9));
                    break;
                }
            }
            break;
        }
    }
    file.close();
    return true;
}

bool Person::initialize_cash(Cash& cash) // Initializes cash from file
{
    ifstream file("cash.txt"); // Opening the file

    if (!file.is_open()) // Ensuring that the file opened correctly
        return false; // Indicates error

    string str;

    file >> str;
    file >> str;
    file >> str;
    cash.initial = stod(str);
    
    file >> str;
    file >> str;
    file >> str;
    cash.in = stod(str);
    
    file >> str;
    file >> str;
    file >> str;
    cash.out = stod(str);
    
    file >> str;
    file >> str;
    file >> str;
    cash.finl = stod(str);

    file.close();
    return true; // Indicates successful termination
}

bool Person::update_goods(Goods* goods) // Updates goods.txt
{
    ofstream file("goods.txt", ios::trunc); // deletes old file's content
    
    if (!file.is_open()) // Ensuring that the file opened correctly
        return false; // Indicates error
    
    for (int i = 0; i < N; i++) // Writing new content to file
    {
        file << "Name: " << goods[i].name << endl 
            << "Stock: " << goods[i].stock << endl 
            << "Cost: " << goods[i].cost << endl 
            << "Price: " << goods[i].price << endl 
            << "Reorder Level: " << goods[i].reorder_level << endl 
            << "Reorder Amount: " << goods[i].reorder_amount << endl 
            << endl;
    }
    file.close();
    return true; // Indicates successful termination
}

bool Person::update_balance(string fileName) // Updates balance to file passed as argument
{
    ifstream old_file(fileName); // Opening the files
    ofstream new_file("tmp.txt");

    if (!old_file.is_open() || !new_file.is_open()) // Ensuring that the files opened correctly
        return false; // Indicates error

    string str;
    while (!old_file.eof())
    {
        getline(old_file, str);
        if (str == this->lookup)
        {
            new_file << str << endl;
            while(getline(old_file, str))
            {
                if (str.substr(0, 7) == "Balance")
                {
                    new_file << "Balance: " << balance << endl;
                    break;
                }
                new_file << str << endl;
            }
            continue;
        }
        new_file << str << endl;
    }

    old_file.close();
    new_file.close();
    remove(fileName.c_str());
    rename("tmp.txt", fileName.c_str());
    return true; // Indicates successful termination
}

bool Person::update_cash(Cash& cash) // Updates cash.txt
{
    ofstream file("cash.txt", ios::trunc); // Opens the file and deletes old file

    if (!file.is_open()) // Ensuring that the file opened correctly
        return false; // Indicates error
    
    file << "Initial cash: " << cash.initial << endl 
        << "Cash in: " << cash.in << endl 
        << "Cash out: " << cash.out << endl 
        << "Final cash: " << cash.finl;
    file.close();
    return true; // Indicates successful termination
}

void Person::buy(string f) // Displays menu and allows customers to make purchases
{
    Goods goods[N]; // Array of goods
    Cash cash;
    
    // Initializing
    if (!initialize_goods(goods) || !initialize_balance(f) || !initialize_cash(cash))
    {
        cout << "Sorry! An error occured while processing the data.\nPress any key to exit.";
        getch();
        return;
    }

    char c;
    bool go = true;
    int a, b, ans;
    while (go)
    {
        system("cls");
        heading("MENU");
        
        cout << left << setw(3) << " " << setw(15) << "Name" << "Price($)" << endl << endl;
        for (int i = 0; i < N; i++)
            cout << setw(3) << i + 1 << setw(15) << goods[i].name << goods[i].price << endl;
        cout << endl << "Your balance: $" << balance << right << endl;
        
        cout << "\nYou want to:\n"
            << "1) Add items to order" << endl
            << "2) Confirm order" << endl
            << "3) Go Back" << endl;

        cin >> ans;
        fflush(stdin);

        switch(ans)
        {
            case 1:
                cout << endl << " Item number: ";
                cin >> a;
                if (a < 1 || a > 10)
                {
                    do
                    {
                        cout << "Number must be between 1 and 10. Please re-enter: ";
                        cin >> a;
                        fflush(stdin);
                    }
                    while (a < 1 || a > 10);
                }

                cout << "Quantity: ";
                cin >> b;
                if (b <= 0 || b > goods[a - 1].stock)
                {
                    do
                    {
                        if (b <= 0)
                            cout << "Number must be positive.\n Please re-enter: ";
                        else
                            cout << "Not enough quantity in stock!\n Please re-enter: ";
                        cin >> b;
                        fflush(stdin);
                    }
                    while (b <= 0 || b > goods[a - 1].stock);
                }

                goods[a - 1].bought = true;
                goods[a - 1].quantity = b;
                getch();
                break;

            case 2:

                bool order = false; // false if no order has been placed yet, true otherwise
                double ordercost = 0; // stores the cost of the order

                for (int i = 0; i < N; i++)
                {
                    if (goods[i].bought)
                    {
                        order = true;
                        if (f == "customer.txt")
                            ordercost += goods[i].price * goods[i].quantity;
                        else
                            ordercost += goods[i].price * goods[i].quantity * 0.80; // employees and admin avail a 20% discount
                    }
                }

                if (!order) // Display error if no order has been placed
                {
                    cout << endl << "Sorry! No order has been placed yet!" << endl;
                    getch();
                    break;
                }

                else if (ordercost > balance) // Display error if cost exceeds balance
                {
                    cout << endl << "Sorry! You do not have enough balance!" << endl 
                        << "Your balance: $" << balance << endl 
                        << "Cost of the order: $" << ordercost << endl;
                    getch();
                    break;
                }

                balance -= ordercost; // Deducting balance
                cash + ordercost; // Increasing cash

                if (!update_cash(cash) || !initialize_cash(cash))
                {
                    cout << "Sorry! An error occured while processing the data.\nPress any key to exit.";
                    getch();
                    break;
                }

                // Automatic reorder logic
                for (int i = 0; i < N; i++)
                {
                    if (goods[i].bought)
                    {
                        goods[i].stock -= goods[i].quantity;

                        if ((goods[i].stock <= goods[i].reorder_level) && ((goods[i].cost * goods[i].reorder_amount) <= cash.get_final_cash()))
                        {
                            goods[i].stock += goods[i].reorder_amount; // Stock increases
                            cash - (goods[i].cost * goods[i].reorder_amount); // Cash decrease
                            
                            if (!update_cash(cash) || !initialize_cash(cash))
                            {
                                cout << "Sorry! An error occured while processing the data.\nPress any key to exit.";
                                getch();
                                break;
                            }
                        }
                    }
                }
                if (!update_balance(f) || !update_goods(goods))
                {
                    cout << "Sorry! An error occured while processing the data.\nPress any key to exit.";
                    getch();
                    break;
                }
                cout << endl << "Order successfully placed!" << endl 
                    << "Cost of the order: $" << ordercost << endl 
                    << "Your new balance: $" << balance << endl;
                fflush(stdin);
                getch();
                break;

            case 3:
                go = false;
                break;

            default :
                cout << " Invalid choice!";
                cout << "\n Press any key to go enter again...\n";
                getch();
                break;
        }
    }
}
