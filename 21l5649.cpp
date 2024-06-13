#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<ctime>
#include<vector>
using namespace std;

class SalesManager {
private:
    //Item items[100]; // array to store items
    //int itemCount = 0; // current number of items

public:
    virtual void read_item(string line) {}
    virtual void addItem() {}

    virtual void updateItem() {}

    virtual void printItem() {}

    virtual void removeItem() {}
    virtual bool same_sku(string suk) const
    {
        return false;
    }

    virtual void readCustomer(string line) {}
    virtual void addCustomer() {}

    virtual void updateCustomer() {}

    virtual void printCustomer() {}

    virtual void removeCustomer() {}
    virtual bool same_cnic(string suk) const
    {
        return false;
    }

    virtual void get_customer(string& cnic, string& name, string& email, string& number, string& status, float& discount, int& sale_limit) const
    {
    }

    virtual void get_item(string& sku, string& description, double& price, int& quantity, string& creationDate) const
    {
    }
};

class Item : public SalesManager
{
    string sku;
    string description;
    double price;
    int quantity;
    string creationDate;

public:

    Item() {}

    virtual void get_item(string& sku, string& description, double& price, int& quantity, string& creationDate) const
    {
        sku = this->sku;
        description = this->description;
        price = this->price;
        quantity = this->quantity;
        creationDate.assign(this->creationDate);
    }

    Item(string& sku, string& description, double& price, int& quantity, string& creationDate)
    {
        this->sku = sku;
        this->description = description;
        this->price = price;
        this->quantity = quantity;
        this->creationDate.assign(creationDate);
    }

    Item(Item* obj)
    {
        this->sku = obj->sku;
        this->description = obj->description;
        this->price = obj->price;
        this->quantity = obj->quantity;
        this->creationDate.assign(obj->creationDate);
    }

    void read_item(string line)
    {
        istringstream iss(line);
        string data;

        getline(iss, data, ',');
        sku = data;

        getline(iss, data, ',');
        description = data;

        getline(iss, data, ',');
        price = stod(data);

        getline(iss, data);
        quantity = stoi(data);

        time_t currentTime = time(nullptr);
        tm localtime_struct;
        localtime_s(&localtime_struct, &currentTime);
        char buffer[11];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localtime_struct);
        creationDate.assign(buffer);
    }

    void addItem() {
        cout << "Enter SKU: ";
        cin >> sku;
        cout << "Enter description: ";
        cin.ignore();
        getline(cin, description);
        cout << "Enter price: ";
        cin >> price;
        cout << "Enter quantity: ";
        cin >> quantity;

        time_t currentTime = time(nullptr);
        tm localtime_struct;
        localtime_s(&localtime_struct, &currentTime);
        char buffer[11];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localtime_struct);
        creationDate.assign(buffer);

        ofstream file("items.txt", ios::app);
        if (file.is_open()) {
            file << "\n";
            file << sku << "," << description << "," << price << "," << quantity;
            cout << "Item added successfully!\n";
        }
        else {
            cout << "Error: Unable to open file.\n";
        }
        file.close();
    }

    void updateItem()
    {
        int opt = -1;
        while (opt != 0)
        {
            cout << "Press 0 to quit" << endl;
            cout << "What do you want to change: " << endl;
            cout << "1 : Description" << endl;
            cout << "2 : price" << endl;
            cout << "3 : Quantity" << endl;
            cout << ">> ";
            cin >> opt;

            if (opt == 1)
            {
                cout << "Enter new description: ";
                cin.ignore();
                getline(cin, description);
            }
            else if (opt == 2)
            {
                cout << "Enter New price: ";
                cin >> price;
            }
            else if (opt == 3)
            {
                cout << "Enter New Quantity: ";
                cin >> price;
            }
        }

        ifstream infile("items.txt");
        ofstream outfile("temp.txt");

        while (!infile.eof())
        {
            string line;
            getline(infile, line);
            istringstream iss(line);
            string data;
            getline(iss, data, ',');
            string sku = data;
            if (sku == this->sku)
            {
                outfile << this->sku << "," << this->description << "," << this->price << "," << this->quantity;
                outfile << '\n';
                cout << "Update Successful" << endl;
            }
            else
            {
                outfile << line;
                outfile << '\n';
            }

        }
        infile.close();
        outfile.close();
        outfile.open("items.txt", ios::trunc);
        outfile.close();
        infile.open("temp.txt");
        outfile.open("items.txt");
        while (!infile.eof())
        {
            string line;
            getline(infile, line);
            outfile << line << endl;
        }
        infile.close();
        outfile.close();
        outfile.open("temp.txt", ios::trunc);
        outfile.close();
    }

    void removeItem()
    {
        ifstream infile("items.txt");
        ofstream outfile("temp.txt");
        while (!infile.eof())
        {
            string line;
            getline(infile, line);
            istringstream iss(line);
            string data;
            getline(iss, data, ',');
            string sku = data;
            if (sku == this->sku)
            {
                cout << "Remove Successful" << endl;
            }
            else
            {
                outfile << line;
                outfile << '\n';
            }

        }
        infile.close();
        outfile.close();
        outfile.open("items.txt", ios::trunc);
        outfile.close();
        infile.open("temp.txt");
        outfile.open("items.txt");
        while (!infile.eof())
        {
            string line;
            getline(infile, line);
            outfile << line << endl;
        }
        infile.close();
        outfile.close();
        outfile.open("temp.txt", ios::trunc);
        outfile.close();
    }

    void printItem()
    {
        cout << "SKU: " << this->sku << endl;
        cout << "Description: " << this->description << endl;
        cout << "price: " << this->price << endl;
        cout << "Quantity: " << this->quantity << endl;
    }

    bool same_sku(string sku) const override
    {
        if (this->sku == sku)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    double get_price()
    {
        return price;
    }
    string get_sku()
    {
        return sku;
    }
    string get_decr()
    {
        return description;
    }

};

class Customer : public SalesManager
{
    string cnic;
    string name;
    string email;
    string number;
    string status;
    float discount;
    int sale_limit;


public:

    Customer() {
        sale_limit = 40000;
        discount = 0;
    }

    void readCustomer(string line)
    {
        istringstream iss(line);
        string data;

        getline(iss, data, ',');
        cnic = data;

        getline(iss, data, ',');
        name = data;

        getline(iss, data, ',');
        email = data;

        getline(iss, data, ',');
        number = data;

        getline(iss, data);
        status = data;

        if (status == "Silver")
        {
            sale_limit = 40000;
            discount = 0;
        }
        else if (status == "Gold")
        {
            sale_limit = 100000;
            discount = 0.3;
        }
        else if (status == "Platinum")
        {
            sale_limit = 250000;
            discount = 0.5;
        }

    }

    void addCustomer() {
        cout << "Enter CNIC: ";
        cin.ignore();
        getline(cin, cnic);
        cout << "Enter name: ";
        //cin.ignore();
        getline(cin, name);
        cout << "Enter email: ";
        //cin.ignore();
        getline(cin, email);
        cout << "Enter number: ";
        //cin.ignore();
        getline(cin, number);
        cout << "Enter status: ";
        //cin.ignore();
        getline(cin, status);

        if (status == "Silver")
        {
            sale_limit = 40000;
            discount = 0;
        }
        else if (status == "Gold")
        {
            sale_limit = 100000;
            discount = 0.3;
        }
        else if (status == "Platinum")
        {
            sale_limit = 250000;
            discount = 0.5;
        }

        ofstream file("customer.txt", ios::app);
        if (file.is_open()) {
            file << "\n";
            file << cnic << "," << name << "," << email << "," << number << "," << status;
            cout << "Item added successfully!\n";
        }
        else {
            cout << "Error: Unable to open file.\n";
        }
        file.close();
    }

    void updateCustomer()
    {
        int opt = -1;
        while (opt != 0)
        {
            cout << "Press 0 to quit" << endl;
            cout << "What do you want to change: " << endl;
            cout << "1 : Name" << endl;
            cout << "2 : Email" << endl;
            cout << "3 : Number" << endl;
            cout << "4 : Status" << endl;
            cout << ">> ";
            cin >> opt;

            if (opt == 1)
            {
                cout << "Enter new name: ";
                cin.ignore();
                getline(cin, name);
            }
            else if (opt == 2)
            {
                cout << "Enter New email: ";
                cin.ignore();
                getline(cin, email);
            }
            else if (opt == 3)
            {
                cout << "Enter New number: ";
                cin.ignore();
                getline(cin, number);
            }
            else if (opt == 4)
            {
                cout << "Enter New status: ";
                cin.ignore();
                getline(cin, status);
            }

        }

        ifstream infile("customer.txt");
        ofstream outfile("temp.txt");

        while (!infile.eof())
        {
            string line;
            getline(infile, line);
            istringstream iss(line);
            string data;
            getline(iss, data, ',');
            string cnic = data;
            if (cnic == this->cnic)
            {
                outfile << this->cnic << "," << this->name << "," << this->email << "," << this->number << "," << this->status;
                outfile << '\n';
                cout << "Update Successful" << endl;
            }
            else
            {
                outfile << line;
                outfile << '\n';
            }

        }
        infile.close();
        outfile.close();
        outfile.open("customer.txt", ios::trunc);
        outfile.close();
        infile.open("temp.txt");
        outfile.open("customer.txt");
        while (!infile.eof())
        {
            string line;
            getline(infile, line);
            outfile << line << endl;
        }
        infile.close();
        outfile.close();
        outfile.open("temp.txt", ios::trunc);
        outfile.close();
    }

    void removeCustomer()
    {
        ifstream infile("customer.txt");
        ofstream outfile("temp.txt");
        while (!infile.eof())
        {
            string line;
            getline(infile, line);
            istringstream iss(line);
            string data;
            getline(iss, data, ',');
            string sku = data;
            if (sku == this->cnic)
            {
                cout << "Remove Successful" << endl;
            }
            else
            {
                outfile << line;
                outfile << '\n';
            }

        }
        infile.close();
        outfile.close();
        outfile.open("customer.txt", ios::trunc);
        outfile.close();
        infile.open("temp.txt");
        outfile.open("customer.txt");
        while (!infile.eof())
        {
            string line;
            getline(infile, line);
            outfile << line << endl;
        }
        infile.close();
        outfile.close();
        outfile.open("temp.txt", ios::trunc);
        outfile.close();
    }

    void printCustomer()
    {
        cout << "cnic: " << this->cnic << endl;
        cout << "Name: " << this->name << endl;
        cout << "Email: " << this->email << endl;
        cout << "Number: " << this->number << endl;
        cout << "Status: " << this->status << endl;
    }

    bool same_cnic(string cnic) const override
    {
        if (this->cnic == cnic)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Customer(string& cnic, string& name, string& email, string& number, string& status, float& discount, int& sale_limit)
    {
        this->cnic = cnic;
        this->name = name;
        this->email = email;
        this->number = number;
        this->status = status;
        this->discount = discount;
        this->sale_limit = sale_limit;
    }

    void get_customer(string& cnic, string& name, string& email, string& number, string& status, float& discount, int& sale_limit) const override
    {
        cnic = this->cnic;
        name = this->name;
        email = this->email;
        number = this->number;
        status = this->status;
        discount = this->discount;
        sale_limit = this->sale_limit;
    }

    string get_name()
    {
        return name;
    }
    string get_cnic()
    {
        return cnic;
    }
    string get_status()
    {
        return status;
    }

    double get_disc()
    {
        return discount;
    }

};

class Sale
{
    int sale_id;
    vector<Item*> items;
    vector <int> i_quant;
    Customer* customer;
    double sub_total;
    string date_time;
    int amount_paid;

public:

    Sale(Customer* cust, int sid, string datt)
    {
        sale_id = sid;
        customer = cust;
        date_time = datt;
        sub_total = 0;
    }

    void inpt_cust(Customer* cust)
    {
        customer = cust;
    }

    void add_item(Item* itm, int quant)
    {
        items.push_back(new Item(itm));
        i_quant.push_back(quant);
    }

    void set_total(float st)
    {
        sub_total += st;
        sub_total -= float(sub_total * customer->get_disc());
    }

    void print_sale()
    {
        cout << "Sale Id: " << sale_id << endl;
        cout << "Cnic: " << customer->get_cnic() << endl;
        cout << "Date: " << date_time << endl;
        cout << "Name: " << customer->get_name() << endl;
        cout << "Status: " << customer->get_status() << endl;

        for (int i = 0; i < items.size(); i++)
        {
            cout << i + 1 << ") " << items[i]->get_sku() << " " << items[i]->get_decr() << " " << i_quant[i] << " " << items[i]->get_price() << endl;
        }
        cout << "Subtotal: " << sub_total << endl;
    }

    void print_items()
    {
        for (int i = 0; i < items.size(); i++)
        {
            cout << items[i]->get_sku() << " " << items[i]->get_decr() << " " << i_quant[i] << " " << items[i]->get_price() << endl;
        }
    }

    void remove_item(int ind)
    {
        if (ind <= items.size() && ind >= 0)
        {
            sub_total -= items[ind]->get_price() * i_quant[ind];
            items.erase(items.begin() + ind);
            i_quant.erase(i_quant.begin() + ind);
        }
    }

    void make_payment()
    {
        int amount;
        cout << "Sales_ID: " << sale_id << endl;
        cout << "Customer Name: " << customer->get_name() << endl;
        cout << "Sub Total: " << sub_total << endl;
        cout << "Amount Paid: " << amount_paid << endl;
        cout << "Amount to be paid: ";
        cin >> amount;
        amount_paid += amount;
    }
};


int main()
{
    time_t currentTime = time(nullptr);
    tm localtime_struct;
    localtime_s(&localtime_struct, &currentTime);
    char buffer[11];
    vector <Sale*> sales;
    vector <SalesManager*> Item_man;
    vector <SalesManager*> customer_man;
    int n_items = 0;
    int n_customers = 0;
    int sale_id = 0;
    Item* itm = nullptr;
    Customer* cust;
    int sale_opt = -1;
    ifstream file("items.txt");
    string sku;
    string description;
    double price;
    int quantity;
    string creationDate;

    string cnic;
    string name;
    string email;
    string number;
    string status;
    float discount;
    int sale_limit;


    for (int i = n_items; !file.eof(); n_items++, i++)
    {
        Item_man.push_back(new Item());
        string line;
        getline(file, line);
        Item_man[i]->read_item(line);
    }
    file.close();

    file.open("customer.txt");

    for (int i = n_customers; !file.eof(); n_customers++, i++)
    {
        customer_man.push_back(new Customer());
        string line;
        getline(file, line);
        customer_man[i]->readCustomer(line);
    }


    int choice;
    do
    {
        cout << "Main Menu\n"
            << "1- Manage Items\n"
            << "2- Manage Customers\n"
            << "3- Make New Sale\n"
            << "4- Make Payment\n"
            << "5- Exit\n"
            << "Press 1 to 5 to select an option: ";
        cin >> choice;
        string sku;
        string cnic;
        string datt;
        switch (choice)
        {
        case 1:
            int itemsChoice;
            do {
                cout << "Items Menu\n"
                    << "1- Add new Item\n"
                    << "2- Update Item details\n"
                    << "3- Find Items\n"
                    << "4- Remove Existing Item\n"
                    << "5- Back to Main Menu\n"
                    << "Press 1 to 5 to select an option: ";
                cin >> itemsChoice;

                switch (itemsChoice)
                {
                case 1:
                    Item_man.push_back(new Item());
                    Item_man[n_items]->addItem();
                    n_items++;
                    break;
                case 2:
                    cout << "Enter SKU: ";
                    cin.ignore();
                    getline(cin, sku);
                    for (int i = 0; i <= n_items; i++)
                    {
                        if (i < n_items)
                        {
                            if (Item_man[i]->same_sku(sku) == true)
                            {
                                Item_man[i]->updateItem();
                                break;
                            }
                        }
                        else
                        {
                            cout << "Item Not Found" << endl << endl;
                        }
                    }
                    break;
                case 3:
                    cout << "Enter SKU: ";
                    cin.ignore();
                    getline(cin, sku);
                    for (int i = 0; i <= n_items; i++)
                    {
                        if (i < n_items)
                        {
                            if (Item_man[i]->same_sku(sku) == true)
                            {
                                Item_man[i]->printItem();
                                break;
                            }
                        }
                        else
                        {
                            cout << "Item Not Found" << endl << endl;
                        }
                    }
                    break;
                case 4:
                    cout << "Enter SKU: ";
                    cin.ignore();
                    getline(cin, sku);
                    for (int i = 0; i <= n_items; i++)
                    {
                        if (i < n_items)
                        {
                            if (Item_man[i]->same_sku(sku) == true)
                            {
                                Item_man[i]->removeItem();
                                Item_man.erase(Item_man.begin() + i);
                                n_items--;
                                break;
                            }
                        }
                        else
                        {
                            cout << "Item Not Found" << endl << endl;
                        }
                    }
                    break;
                case 5:                   
                    cout << "Going back to Main Menu.\n";
                    break;
                default:
                    cout << "Invalid choice, please try again.\n";
                    break;
                }
            } while (itemsChoice != 5);
            break;
        case 2:
            int customerChoice;
            do {
                cout << "Customers Menu\n"
                    << "1- Add new Customer\n"
                    << "2- Update Customer details\n"
                    << "3- Find Customers\n"
                    << "4- Remove Existing Customers\n"
                    << "5- Back to Main Menu\n"
                    << "Press 1 to 5 to select an option: ";
                cin >> customerChoice;

                switch (customerChoice)
                {
                case 1:
                    customer_man.push_back(new Customer());
                    customer_man[n_customers]->addCustomer();
                    n_customers++;
                    break;
                case 2:
                    cout << "Enter CNIC: ";
                    cin.ignore();
                    getline(cin, cnic);
                    for (int i = 0; i <= n_customers; i++)
                    {
                        if (i < n_customers)
                        {
                            if (customer_man[i]->same_cnic(cnic) == true)
                            {
                                customer_man[i]->updateCustomer();
                                break;
                            }
                        }
                        else
                        {
                            cout << "Customer Not Found" << endl << endl;
                        }
                    }
                    break;
                case 3:
                    cout << "Enter cnic: ";
                    cin.ignore();
                    getline(cin, cnic);
                    for (int i = 0; i <= n_customers; i++)
                    {
                        if (i < n_customers)
                        {
                            if (customer_man[i]->same_cnic(cnic) == true)
                            {
                                customer_man[i]->printCustomer();
                                break;
                            }
                        }
                        else
                        {
                            cout << "Customer Not Found" << endl << endl;
                        }
                    }
                    break;
                case 4:
                    cout << "Enter cnic: ";
                    cin.ignore();
                    getline(cin, cnic);
                    for (int i = 0; i <= n_customers; i++)
                    {
                        if (i < n_customers)
                        {
                            if (customer_man[i]->same_cnic(cnic) == true)
                            {
                                customer_man[i]->removeCustomer();
                                customer_man.erase(customer_man.begin() + i);
                                n_customers--;
                                break;
                            }
                        }
                        else
                        {
                            cout << "Customer Not Found" << endl << endl;
                        }
                    }
                    break;
                case 5:
                    cout << "Going back to Main Menu.\n";
                    break;
                default:
                    cout << "Invalid choice, please try again.\n";
                    break;
                }
            } while (customerChoice != 5);
            break;
        case 3:
            cout << "sale id: " << sale_id << endl;
            localtime_s(&localtime_struct, &currentTime);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localtime_struct);
            datt.assign(buffer);
            cout << "Date/Time: " << datt << endl;
            cout << "Enter cnic: ";
            cin.ignore();
            getline(cin, cnic);
            for (int i = 0; i <= n_customers; i++)
            {
                if (i < n_customers)
                {
                    if (customer_man[i]->same_cnic(cnic) == true)
                    {
                        customer_man[i]->get_customer(cnic, name, email, number, status, discount, sale_limit);
                        cust = new Customer(cnic, name, email, number, status, discount, sale_limit);
                        sales.push_back(new Sale(cust, sale_id, datt));
                        sale_id++;
                        sale_opt = -1;
                        while (sale_opt != 0)
                        {
                            cout << "Sale Menu\n"
                                << "0- quit\n"
                                << "1- Add new Item\n"
                                << "2- End Sale\n"
                                << "3- Remove Existing Item from sale\n"
                                << "4- Cancel Sale\n";
                            cout << ">> ";
                            cin >> sale_opt;

                            if (sale_opt == 1)
                            {
                                cout << "Enter SKU: ";
                                cin.ignore();
                                getline(cin, sku);
                                for (int i = 0; i <= n_items; i++)
                                {
                                    if (i < n_items)
                                    {
                                        if (Item_man[i]->same_sku(sku) == true)
                                        {
                                            Item_man[i]->get_item(sku, description, price, quantity, creationDate);
                                            delete itm;
                                            itm = new Item(sku, description, price, quantity, creationDate);
                                            int quant;
                                            cout << "Enter Quantity: ";
                                            cin >> quant;
                                            sales[sale_id - 1]->add_item(itm, quant);
                                            sales[sale_id - 1]->set_total(float(quant * itm->get_price()));
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        cout << "Item Not Found" << endl << endl;
                                    }
                                }

                            }
                            else if (sale_opt == 2)
                            {
                                sales[sale_id - 1]->print_sale();
                            }
                            else if (sale_opt == 3)
                            {
                                int ind;
                                sales[sale_id - 1]->print_sale();
                                cout << "Enter the index of item: ";
                                cin >> ind;
                                sales[sale_id - 1]->remove_item(ind - 1);
                            }
                            else if (sale_opt == 4)
                            {
                                sales.erase(sales.begin() + (sale_id - 1));
                                sale_id--;
                            }
                        }
                        break;
                    }
                }
                else
                {
                    cout << "Customer Not Found" << endl << endl;

                }
            }
            break;
        case 4:

            int s_id;
            cout << "Enter sale_id: ";
            cin >> s_id;
            if (s_id >= 0 && s_id <= sale_id && sales.size() != 0)
            {
                sales[s_id]->make_payment();
            }
            else
            {
                cout << "Invalid Sales Id" << endl;
            }

            break;
        case 5:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice, please try again.\n";
            break;
        }
    } while (choice != 5);

    //system("pause");
    return 0;
}