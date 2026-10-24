#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Product {
protected:
    int id, quantity;
    string name, brand;
    double price;

public:
    Product() {
        id = 0;
        quantity = 0;
        price = 0;
    }

    Product(int i, string n, string b, double p, int q) {
        id = i;
        name = n;
        brand = b;
        price = p;
        quantity = q;
    }

    virtual ~Product() {}

    virtual void display() {
        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nBrand: " << brand;
        cout << "\nPrice: " << price;
        cout << "\nQuantity: " << quantity << endl;
    }

    void addStock(int q) {
        quantity += q;
    }

    void sellProduct(int q) {
        if (q <= quantity)
            quantity -= q;
        else
            cout << "Insufficient stock!\n";
    }

    int getId() {
        return id;
    }
};
class Smartphone : public Product {
    string os;
    int storage;

public:
    Smartphone(int i, string n, string b, double p,
               int q, string o, int s)
        : Product(i, n, b, p, q) {
        os = o;
        storage = s;
    }

    ~Smartphone() {}

    void display() override {
        Product::display();
        cout << "OS: " << os;
        cout << "\nStorage: " << storage << " GB\n";
    }
};

class Laptop : public Product {
    string processor;
    int ram;

public:
    Laptop(int i, string n, string b, double p,
           int q, string cpu, int r)
        : Product(i, n, b, p, q) {
        processor = cpu;
        ram = r;
    }

    ~Laptop() {}

    void display() override {
        Product::display();
        cout << "Processor: " << processor;
        cout << "\nRAM: " << ram << " GB\n";
    }
};

class Inventory {
    Product* products[50];
    int count;

public:
    Inventory() {
        count = 0;
    }

    ~Inventory() {
        for (int i = 0; i < count; i++)
            delete products[i];
    }

    void addProduct(Product* p) {
        if (count < 50) {
            products[count++] = p;
            cout << "\nProduct added successfully!\n";
        }
    }

    void displayAll() {
        if (count == 0) {
            cout << "\nNo products available.\n";
            return;
        }

        for (int i = 0; i < count; i++) {
            cout << "\n--------------------\n";
            products[i]->display();
        }
    }

    Product* searchProduct(int id) {
        for (int i = 0; i < count; i++) {
            if (products[i]->getId() == id)
                return products[i];
        }

        return nullptr;
    }

    void sell(int id, int q) {
        Product* p = searchProduct(id);

        if (p != nullptr)
            p->sellProduct(q);
        else
            cout << "Product not found.\n";
    }

    void restock(int id, int q) {
        Product* p = searchProduct(id);

        if (p != nullptr)
            p->addStock(q);
        else
            cout << "Product not found.\n";
    }
};

void menu() {
    cout << "\n============================================";
    cout << "\n SMART ELECTRONIC PRODUCT MANAGEMENT SYSTEM";
    cout << "\n============================================";
    cout << "\n1. Add Smartphone";
    cout << "\n2. Add Laptop";
    cout << "\n3. Display All Products";
    cout << "\n4. Search Product";
    cout << "\n5. Sell Product";
    cout << "\n6. Restock Product";
    cout << "\n7. Exit";
    cout << "\nEnter choice: ";
}

int main() {

    Inventory inventory;

    void (Inventory::*ptr)() = &Inventory::displayAll;

    int choice;

    do {

        menu();

        while (!(cin >> choice)) {
            cout << "Invalid input! Enter a number from 1 to 7: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {

        case 1: {
            int id, quantity, storage;
            string name, brand, os;
            double price;

            cout << "\nEnter ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Name: ";
            getline(cin, name);

            cout << "Enter Brand: ";
            getline(cin, brand);

            cout << "Enter Price: ";
            cin >> price;

            cout << "Enter Quantity: ";
            cin >> quantity;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Operating System: ";
            getline(cin, os);

            cout << "Enter Storage (GB): ";
            cin >> storage;

            inventory.addProduct(
                new Smartphone(
                    id,
                    name,
                    brand,
                    price,
                    quantity,
                    os,
                    storage
                )
            );

            break;
        }

        case 2: {
            int id, quantity, ram;
            string name, brand, processor;
            double price;

            cout << "\nEnter ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Name: ";
            getline(cin, name);

            cout << "Enter Brand: ";
            getline(cin, brand);

            cout << "Enter Price: ";
            cin >> price;

            cout << "Enter Quantity: ";
            cin >> quantity;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Processor: ";
            getline(cin, processor);

            cout << "Enter RAM (GB): ";
            cin >> ram;

            inventory.addProduct(
                new Laptop(
                    id,
                    name,
                    brand,
                    price,
                    quantity,
                    processor,
                    ram
                )
            );

            break;
        }

        case 3:
            (inventory.*ptr)();
            break;

        case 4: {
            int id;

            cout << "\nEnter Product ID: ";
            cin >> id;

            Product* p = inventory.searchProduct(id);
            if (p != nullptr)
                p->display();
            else
                cout << "Product not found.\n";

            break;
        }
        case 5: {
            int id, quantity;

            cout << "\nEnter Product ID: ";
            cin >> id;

            cout << "Enter Quantity: ";
            cin >> quantity;
            inventory.sell(id, quantity);
            break;
        }

        case 6: {
            int id, quantity;

            cout << "\nEnter Product ID: ";
            cin >> id;

            cout << "Enter Quantity: ";
            cin >> quantity;

            inventory.restock(id, quantity);

            break;
        }

        case 7:
            cout << "\nProgram exited successfully.\n";
            break;

        default:
            cout << "\nInvalid choice! Please select 1-7.\n";
        }

    } while (choice != 7);

    return 0;
}
