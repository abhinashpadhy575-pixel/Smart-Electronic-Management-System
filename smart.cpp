#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

class ElectronicProduct {
private:
    int id;
    string name;
    string brand;
    double price;
    int stock;

    static int registeredProducts;

public:
    ElectronicProduct() {
        id = 0;
        name = "Unknown";
        brand = "Unknown";
        price = 0.0;
        stock = 0;
    }
    ElectronicProduct(int productId, string productName, string productBrand,
                      double productPrice = 0.0, int productStock = 0) {
        id = productId;
        name = productName;
        brand = productBrand;
        price = productPrice;
        stock = productStock;
    }
    ElectronicProduct(const ElectronicProduct &product) {
        id = product.id;
        name = product.name;
        brand = product.brand;
        price = product.price;
        stock = product.stock;
    }
    ElectronicProduct &operator=(const ElectronicProduct &product) {
        if (this != &product) {
            id = product.id;
            name = product.name;
            brand = product.brand;
            price = product.price;
            stock = product.stock;
        }
        return *this;
    }
    ~ElectronicProduct() {}
    inline int getId() const { return id; }
    inline string getName() const { return name; }
    inline string getBrand() const { return brand; }
    inline double getPrice() const { return price; }
    inline int getStock() const { return stock; }

    bool setPrice(double newPrice) {
        if (newPrice < 0.0)
            return false;

        price = newPrice;
        return true;
    }

    bool setStock(int newStock) {
        if (newStock < 0)
            return false;

        stock = newStock;
        return true;
    }
    void displayCommon(const string &category, const string &extraDetails) const {
        cout << "---------------------------------------------\n";
        cout << "Product ID : " << id << '\n';
        cout << "Name       : " << name << '\n';
        cout << "Brand      : " << brand << '\n';
        cout << "Category   : " << category << '\n';
        cout << "Price      : Rs. " << fixed << setprecision(2) << price << '\n';
        cout << "Stock      : " << stock << '\n';
        cout << extraDetails << '\n';
        cout << "---------------------------------------------\n";
    }
    static void setRegisteredProducts(int count) {
        registeredProducts = count;
    }

    static int getRegisteredProducts() {
        return registeredProducts;
    }
};

int ElectronicProduct::registeredProducts = 0;
class SmartDevice : public ElectronicProduct {
private:
    string connectivity;

public:
    SmartDevice() : ElectronicProduct() {
        connectivity = "Not specified";
    }

    SmartDevice(int id, string name, string brand, double price,
                int stock, string deviceConnectivity)
        : ElectronicProduct(id, name, brand, price, stock) {
        connectivity = deviceConnectivity;
    }

    SmartDevice(const SmartDevice &device)
        : ElectronicProduct(device) {
        connectivity = device.connectivity;
    }

    SmartDevice &operator=(const SmartDevice &device) {
        if (this != &device) {
            ElectronicProduct::operator=(device);
            connectivity = device.connectivity;
        }
        return *this;
    }

    void display() const {
        displayCommon("Smart Device", "Connectivity: " + connectivity);
    }
};
class Accessory : public ElectronicProduct {
private:
    string compatibleWith;

public:
    Accessory() : ElectronicProduct() {
        compatibleWith = "Not specified";
    }

    Accessory(int id, string name, string brand, double price,
                int stock, string compatibleDevice)
        : ElectronicProduct(id, name, brand, price, stock) {
        compatibleWith = compatibleDevice;
    }

    Accessory(const Accessory &accessory)
        : ElectronicProduct(accessory) {
        compatibleWith = accessory.compatibleWith;
    }

    Accessory &operator=(const Accessory &accessory) {
        if (this != &accessory) {
            ElectronicProduct::operator=(accessory);
            compatibleWith = accessory.compatibleWith;
        }
        return *this;
    }

    void display() const {
        displayCommon("Accessory", "Compatible with: " + compatibleWith);
    }
};
struct ProductLocation {
    int category; // 0 = not found, 1 = SmartDevice, 2 = Accessory
    int index;
};

class ProductManager {
private:
    static const int MAX_PRODUCTS = 50;
    SmartDevice smartDevices[MAX_PRODUCTS];
    Accessory accessories[MAX_PRODUCTS];
    int smartCount;
    int accessoryCount;

    bool idExists(int id) const {
        for (int i = 0; i < smartCount; i++) {
            if (smartDevices[i].getId() == id)
                return true;
        }

        for (int i = 0; i < accessoryCount; i++) {
            if (accessories[i].getId() == id)
                return true;
        }

        return false;
    }

    void updateRegisteredCount() const {
        ElectronicProduct::setRegisteredProducts(smartCount + accessoryCount);
    }

public:
    ProductManager() : smartCount(0), accessoryCount(0) {
        addSmartDevice(101, "Smart Watch", "Noise", 2999.00, 10, "Bluetooth");
        addAccessory(102, "Wireless Earbuds", "Boat", 1499.00, 20, "Smartphones");
        addAccessory(103, "Power Bank", "MI", 999.00, 15, "Phones and tablets");
    }

    bool addSmartDevice(int id, string name, string brand, double price,
                        int stock, string connectivity) {
        if (smartCount >= MAX_PRODUCTS || id <= 0 || name.empty() ||
            brand.empty() || connectivity.empty() || price < 0.0 ||
            stock < 0 || idExists(id)) {
            return false;
        }

        smartDevices[smartCount] = SmartDevice(id, name, brand, price,
                                               stock, connectivity);
        smartCount++;
        updateRegisteredCount();
        return true;
    }

    bool addAccessory(int id, string name, string brand, double price,
                      int stock, string compatibleWith) {
        if (accessoryCount >= MAX_PRODUCTS || id <= 0 || name.empty() ||
            brand.empty() || compatibleWith.empty() || price < 0.0 ||
            stock < 0 || idExists(id)) {
            return false;
        }

        accessories[accessoryCount] = Accessory(id, name, brand, price,
                                                stock, compatibleWith);
        accessoryCount++;
        updateRegisteredCount();
        return true;
    }
    ProductLocation searchProduct(int id) const {
        for (int i = 0; i < smartCount; i++) {
            if (smartDevices[i].getId() == id) {
                ProductLocation location = {1, i};
                return location;
            }
        }

        for (int i = 0; i < accessoryCount; i++) {
            if (accessories[i].getId() == id) {
                ProductLocation location = {2, i};
                return location;
            }
        }

        ProductLocation notFound = {0, -1};
        return notFound;
    }

    ProductLocation searchProduct(const string &name) const {
        for (int i = 0; i < smartCount; i++) {
            if (smartDevices[i].getName() == name) {
                ProductLocation location = {1, i};
                return location;
            }
        }

        for (int i = 0; i < accessoryCount; i++) {
            if (accessories[i].getName() == name) {
                ProductLocation location = {2, i};
                return location;
            }
        }

        ProductLocation notFound = {0, -1};
        return notFound;
    }

    void displayProduct(ProductLocation location) const {
        if (location.category == 1 && location.index >= 0)
            smartDevices[location.index].display();
        else if (location.category == 2 && location.index >= 0)
            accessories[location.index].display();
        else
            cout << "Product not found.\n";
    }

    void displayAllProducts() const {
        if (smartCount == 0 && accessoryCount == 0) {
            cout << "\nNo products are available.\n";
            return;
        }

        cout << "\n========== SMART DEVICES ==========" << '\n';
        if (smartCount == 0)
            cout << "No smart devices available.\n";
        for (int i = 0; i < smartCount; i++)
            smartDevices[i].display();

        cout << "\n========== ACCESSORIES =============" << '\n';
        if (accessoryCount == 0)
            cout << "No accessories available.\n";
        for (int i = 0; i < accessoryCount; i++)
            accessories[i].display();
    }

    bool updateProductPrice(int id, double newPrice) {
        if (newPrice < 0.0)
            return false;

        ProductLocation location = searchProduct(id);
        if (location.category == 1)
            return smartDevices[location.index].setPrice(newPrice);
        if (location.category == 2)
            return accessories[location.index].setPrice(newPrice);

        return false;
    }
    bool sellProduct(int id, int quantity, double &bill) {
        bill = 0.0;
        ProductLocation location = searchProduct(id);

        if (quantity <= 0 || location.category == 0)
            return false;

        if (location.category == 1) {
            if (quantity > smartDevices[location.index].getStock())
                return false;

            bill = smartDevices[location.index].getPrice() * quantity;
            smartDevices[location.index].setStock(
                smartDevices[location.index].getStock() - quantity);
            return true;
        }

        if (location.category == 2) {
            if (quantity > accessories[location.index].getStock())
                return false;

            bill = accessories[location.index].getPrice() * quantity;
            accessories[location.index].setStock(
                accessories[location.index].getStock() - quantity);
            return true;
        }

        return false;
    }

    void showInventorySummary() const {
        int totalStock = 0;
        double inventoryValue = 0.0;

        for (int i = 0; i < smartCount; i++) {
            totalStock += smartDevices[i].getStock();
            inventoryValue += smartDevices[i].getPrice() * smartDevices[i].getStock();
        }

        for (int i = 0; i < accessoryCount; i++) {
            totalStock += accessories[i].getStock();
            inventoryValue += accessories[i].getPrice() * accessories[i].getStock();
        }

        cout << "\n========== INVENTORY SUMMARY ==========" << '\n';
        cout << "Registered products : " << ElectronicProduct::getRegisteredProducts() << '\n';
        cout << "Smart devices       : " << smartCount << '\n';
        cout << "Accessories         : " << accessoryCount << '\n';
        cout << "Total units in stock: " << totalStock << '\n';
        cout << "Inventory value     : Rs. " << fixed << setprecision(2) << inventoryValue << '\n';
        cout << "=======================================\n";
    }
};

int main() {
    ProductManager manager;
    int choice = -1;

    do {
        cout << "\n==================================================\n";
        cout << " THINKING SMART ELECTRONIC PRODUCT MANAGEMENT\n";
        cout << "==================================================\n";
        cout << "1. Display All Products\n";
        cout << "2. Add Product\n";
        cout << "3. Search Product by ID\n";
        cout << "4. Search Product by Name\n";
        cout << "5. Update Product Price\n";
        cout << "6. Sell Product\n";
        cout << "7. Inventory Summary\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a menu number.\n";
            continue;
        }

        switch (choice) {
        case 1:
            manager.displayAllProducts();
            break;

        case 2: {
            int type, id, stock;
            double price;
            string name, brand, extra;

            cout << "\nAdd type (1 = Smart Device, 2 = Accessory): ";
            cin >> type;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid product type.\n";
                break;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (type != 1 && type != 2) {
                cout << "Invalid product type.\n";
                break;
            }

            cout << "Enter product ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter product name: ";
            getline(cin, name);
            cout << "Enter brand: ";
            getline(cin, brand);
            cout << "Enter price: ";
            cin >> price;
            cout << "Enter stock quantity: ";
            cin >> stock;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (type == 1) {
                cout << "Enter connectivity (e.g. Bluetooth/Wi-Fi): ";
                getline(cin, extra);
                if (manager.addSmartDevice(id, name, brand, price, stock, extra))
                    cout << "Smart device added successfully.\n";
                else
                    cout << "Could not add product. Check values, ID, and available capacity.\n";
            } else {
                cout << "Compatible with (e.g. smartphones/tablets): ";
                getline(cin, extra);
                if (manager.addAccessory(id, name, brand, price, stock, extra))
                    cout << "Accessory added successfully.\n";
                else
                    cout << "Could not add product. Check values, ID, and available capacity.\n";
            }
            break;
        }

        case 3: {
            int id;
            cout << "Enter product ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            manager.displayProduct(manager.searchProduct(id));
            break;
        }

        case 4: {
            string name;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter exact product name: ";
            getline(cin, name);
            manager.displayProduct(manager.searchProduct(name));
            break;
        }

        case 5: {
            int id;
            double price;
            cout << "Enter product ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter new price: ";
            cin >> price;

            if (price < 0.0)
                cout << "Price cannot be negative.\n";
            else if (manager.updateProductPrice(id, price))
                cout << "Product price updated successfully.\n";
            else
                cout << "Product not found.\n";
            break;
        }

        case 6: {
            int id, quantity;
            double bill;
            cout << "Enter product ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter quantity to sell: ";
            cin >> quantity;

            if (manager.sellProduct(id, quantity, bill)) {
                cout << "\n============= SALES INVOICE =============\n";
                cout << "Product ID : " << id << '\n';
                cout << "Quantity   : " << quantity << '\n';
                cout << "Total bill : Rs. " << fixed << setprecision(2) << bill << '\n';
                cout << "==========================================\n";
            } else {
                cout << "Sale failed: check product ID, quantity, and available stock.\n";
            }
            break;
        }

        case 7:
            manager.showInventorySummary();
            break;

        case 0:
            cout << "\nThank you for using Thinking Smart!\n";
            break;

        default:
            cout << "Invalid choice. Please select a valid menu option.\n";
        }

    } while (choice != 0);

    return 0;
}
