#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class ElectronicProduct {
protected:
    int id;
    string name;
    string brand;
    double price;
    int quantity;

public:
    ElectronicProduct(int i, string n, string b, double p, int q)
        : id(i), name(n), brand(b), price(p), quantity(q) {}

    virtual void display() const {
        cout << left << setw(8) << id
             << setw(22) << name
             << setw(15) << brand
             << setw(12) << price
             << setw(10) << quantity << endl;
    }

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    int getQuantity() const {
        return quantity;
    }

    void updateQuantity(int q) {
        quantity += q;
    }

    virtual double getDiscount() const {
        return 0;
    }

    virtual ~ElectronicProduct() {}
};

class Smartphone : public ElectronicProduct {
    string operatingSystem;

public:
    Smartphone(int i, string n, string b, double p, int q, string os)
        : ElectronicProduct(i, n, b, p, q), operatingSystem(os) {}

    void display() const override {
        ElectronicProduct::display();
        cout << "   OS: " << operatingSystem << endl;
    }

    double getDiscount() const override {
        return price * 0.10;
    }
};

class Laptop : public ElectronicProduct {
    int ram;

public:
    Laptop(int i, string n, string b, double p, int q, int r)
        : ElectronicProduct(i, n, b, p, q), ram(r) {}

    void display() const override {
        ElectronicProduct::display();
        cout << "   RAM: " << ram << " GB" << endl;
    }

    double getDiscount() const override {
        return price * 0.15;
    }
};

class Television : public ElectronicProduct {
    double screenSize;

public:
    Television(int i, string n, string b, double p, int q, double s)
        : ElectronicProduct(i, n, b, p, q), screenSize(s) {}

    void display() const override {
        ElectronicProduct::display();
        cout << "   Screen: " << screenSize << " inches" << endl;
    }

    double getDiscount() const override {
        return price * 0.12;
    }
};

class ProductManager {
private:
    vector<ElectronicProduct*> products;

public:
    ~ProductManager() {
        for (auto p : products)
            delete p;
    }

    void addProduct() {
        int type, id, quantity;
        string name, brand;
        double price;

        cout << "\n1. Smartphone\n2. Laptop\n3. Television\n";
        cout << "Enter product type: ";
        cin >> type;

        cout << "Enter ID: ";
        cin >> id;

        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter brand: ";
        getline(cin, brand);

        cout << "Enter price: ";
        cin >> price;

        cout << "Enter quantity: ";
        cin >> quantity;

        if (type == 1) {
            string os;
            cout << "Enter Operating System: ";
            cin >> os;
            products.push_back(
                new Smartphone(id, name, brand, price, quantity, os)
            );
        }
        else if (type == 2) {
            int ram;
            cout << "Enter RAM (GB): ";
            cin >> ram;
            products.push_back(
                new Laptop(id, name, brand, price, quantity, ram)
            );
        }
        else if (type == 3) {
            double size;
            cout << "Enter Screen Size (inches): ";
            cin >> size;
            products.push_back(
                new Television(id, name, brand, price, quantity, size)
            );
        }
        else {
            cout << "Invalid product type.\n";
            return;
        }

        cout << "Product added successfully.\n";
    }

    void displayProducts() const {
        if (products.empty()) {
            cout << "\nNo products available.\n";
            return;
        }

        cout << "\n";
        cout << left << setw(8) << "ID"
             << setw(22) << "Name"
             << setw(15) << "Brand"
             << setw(12) << "Price"
             << setw(10) << "Quantity" << endl;

        cout << string(67, '-') << endl;

        for (const auto& p : products)
            p->display();
    }

    ElectronicProduct* findProduct(int id) {
        for (auto p : products) {
            if (p->getId() == id)
                return p;
        }
        return nullptr;
    }

    void searchProduct() {
        int id;
        cout << "Enter product ID: ";
        cin >> id;

        ElectronicProduct* p = findProduct(id);

        if (p) {
            cout << "\nProduct Found:\n";
            p->display();
        }
        else {
            cout << "Product not found.\n";
        }
    }

    void updateStock() {
        int id, quantity;

        cout << "Enter product ID: ";
        cin >> id;

        ElectronicProduct* p = findProduct(id);

        if (!p) {
            cout << "Product not found.\n";
            return;
        }

        cout << "Enter quantity to add/remove: ";
        cin >> quantity;

        if (p->getQuantity() + quantity < 0) {
            cout << "Insufficient stock.\n";
            return;
        }

        p->updateQuantity(quantity);
        cout << "Stock updated successfully.\n";
    }

    void purchaseProduct() {
        int id, quantity;

        cout << "Enter product ID: ";
        cin >> id;

        ElectronicProduct* p = findProduct(id);

        if (!p) {
            cout << "Product not found.\n";
            return;
        }

        cout << "Enter quantity: ";
        cin >> quantity;

        if (quantity <= 0 || quantity > p->getQuantity()) {
            cout << "Invalid quantity.\n";
            return;
        }

        double total = p->getPrice() * quantity;
        double discount = p->getDiscount() * quantity;
        double finalAmount = total - discount;

        p->updateQuantity(-quantity);

        cout << fixed << setprecision(2);
        cout << "\nPurchase Details\n";
        cout << "Product: " << p->getName() << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Total: " << total << endl;
        cout << "Discount: " << discount << endl;
        cout << "Final Amount: " << finalAmount << endl;
        cout << "Purchase successful.\n";
    }

    void deleteProduct() {
        int id;
        cout << "Enter product ID: ";
        cin >> id;

        for (auto it = products.begin(); it != products.end(); ++it) {
            if ((*it)->getId() == id) {
                delete *it;
                products.erase(it);
                cout << "Product deleted successfully.\n";
                return;
            }
        }

        cout << "Product not found.\n";
    }

    void showMenu() {
        int choice;

        do {
            cout << "\n========== SMART ELECTRONIC PRODUCT MANAGEMENT SYSTEM ==========\n";
            cout << "1. Add Product\n";
            cout << "2. Display All Products\n";
            cout << "3. Search Product\n";
            cout << "4. Update Stock\n";
            cout << "5. Purchase Product\n";
            cout << "6. Delete Product\n";
            cout << "7. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addProduct();
                    break;
                case 2:
                    displayProducts();
                    break;
                case 3:
                    searchProduct();
                    break;
                case 4:
                    updateStock();
                    break;
                case 5:
                    purchaseProduct();
                    break;
                case 6:
                    deleteProduct();
                    break;
                case 7:
                    cout << "Program terminated.\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } while (choice != 7);
    }
};

int main() {
    ProductManager manager;
    manager.showMenu();
    return 0;
}
