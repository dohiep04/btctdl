#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

// Cau truc du lieu cho san pham
struct Product {
    string name;  // Ten san pham
    int quantity; // So luong
    double price; // Gia cua moi san pham
};

// Cau truc du lieu cho gio hang
struct Cart {
    int customerID;             // ID cua khach hang
    vector<Product> products;   // Danh sach san pham
    double totalAmount;         // Tong tien cua gio hang
};

// Hang doi thanh toan
queue<Cart> checkoutQueue;

// Them gio hang vao hang doi
void addToQueue(int customerID, const vector<Product>& products) {
    double totalAmount = 0.0;
    for (size_t i = 0; i < products.size(); ++i) {
        totalAmount += products[i].quantity * products[i].price;
    }
    Cart cart = {customerID, products, totalAmount};
    checkoutQueue.push(cart);
}

// Xu ly thanh toan khach hang dau tien trong hang doi
void checkoutNextCustomer(queue<Cart>& queue) {
    if (!queue.empty()) {
        Cart customer = queue.front();
        cout << "Khach hang " << customer.customerID << " da thanh toan xong. Tong tien: " 
             << customer.totalAmount << " VND.\n";
        queue.pop();
    } else {
        cout << "Hang doi rong. Khong con khach hang de thanh toan.\n";
    }
}

// Tinh tong doanh thu cua thu ngan
double calculateTotalRevenue(queue<Cart> queue) {
    double totalRevenue = 0.0;
    while (!queue.empty()) {
        totalRevenue += queue.front().totalAmount;
        queue.pop();
    }
    return totalRevenue;
}

// Dem so luong san pham da ban
int countProductSold(queue<Cart> queue, const string& productName) {
    int totalCount = 0;
    while (!queue.empty()) {
        const Cart& cart = queue.front();
        for (size_t i = 0; i < cart.products.size(); ++i) {
            if (cart.products[i].name == productName) {
                totalCount += cart.products[i].quantity;
            }
        }
        queue.pop();
    }
    return totalCount;
}

// Ham chinh
int main() {
    // Tao du lieu mau
    vector<Product> products1;
    products1.push_back({"Milk", 2, 1.5});
    products1.push_back({"Bread", 1, 2.0});

    vector<Product> products2;
    products2.push_back({"Milk", 1, 1.5});
    products2.push_back({"Eggs", 12, 0.1});

    vector<Product> products3;
    products3.push_back({"Bread", 2, 2.0});
    products3.push_back({"Juice", 1, 3.0});

    // Them du lieu vao hang doi
    addToQueue(1, products1);
    addToQueue(2, products2);
    addToQueue(3, products3);

    // Xu ly thanh toan khach hang dau tien
    cout << "\n--- Xu ly thanh toan ---\n";
    checkoutNextCustomer(checkoutQueue);

    // Tinh tong doanh thu con lai
    double totalRevenue = calculateTotalRevenue(checkoutQueue);
    cout << "\nTong doanh thu: " << totalRevenue << " VND.\n";

    // Tinh lai so luong san pham "Milk" da ban
    addToQueue(1, products1);
    addToQueue(2, products2);
    addToQueue(3, products3);

    int milkSold = countProductSold(checkoutQueue, "Milk");
    cout << "Tong so luong san pham 'Milk' da ban: " << milkSold << " don vi.\n";

    return 0;
}

