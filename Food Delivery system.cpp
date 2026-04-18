#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

/* =======================
   STRUCTURES
   ======================= */

struct Order {
    int orderID;
    string address;
    vector<string> items;
    string status; // Pending, Active, Delivered
};

struct Driver {
    int driverID;
    int availableTime;
};

/* =======================
   MIN HEAP COMPARATOR
   ======================= */

struct DriverCompare {
    bool operator()(Driver const& d1, Driver const& d2) {
        return d1.availableTime > d2.availableTime;
    }
};

/* =======================
   DATA STRUCTURES
   ======================= */

queue<Order> orderQueue;
priority_queue<Driver, vector<Driver>, DriverCompare> driverHeap;
unordered_map<int, Order> orderMap;

/* =======================
   FUNCTION DECLARATIONS
   ======================= */

void placeOrder();
void assignDriver();
void completeDelivery(int orderID);
void viewOrderSummary();

/* =======================
   MAIN FUNCTION
   ======================= */

int main() {

    // Initial drivers
    driverHeap.push({1, 0});
    driverHeap.push({2, 5});
    driverHeap.push({3, 10});

    int choice;

    do {
        cout << "\n--- Online Food Delivery System ---\n";
        cout << "1. Place Order\n";
        cout << "2. Assign Driver\n";
        cout << "3. Complete Delivery\n";
        cout << "4. View Order Summary\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            placeOrder();
            break;

        case 2:
            assignDriver();
            break;

        case 3: {
            int id;
            cout << "Enter Order ID: ";
            cin >> id;
            completeDelivery(id);
            break;
        }

        case 4:
            viewOrderSummary();
            break;

        case 5:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}

/* =======================
   PLACE ORDER
   ======================= */

void placeOrder() {
    Order newOrder;

    cout << "Enter Order ID: ";
    cin >> newOrder.orderID;

    cin.ignore();
    cout << "Enter Address: ";
    getline(cin, newOrder.address);

    int itemCount;
    cout << "Enter number of items: ";
    cin >> itemCount;

    cin.ignore();
    for (int i = 0; i < itemCount; i++) {
        string item;
        cout << "Item " << i + 1 << ": ";
        getline(cin, item);
        newOrder.items.push_back(item);
    }

    newOrder.status = "Pending";

    orderQueue.push(newOrder);
    orderMap[newOrder.orderID] = newOrder;

    cout << "Order placed successfully!\n";
}

/* =======================
   ASSIGN DRIVER
   ======================= */

void assignDriver() {
    if (orderQueue.empty()) {
        cout << "No pending orders!\n";
        return;
    }

    if (driverHeap.empty()) {
        cout << "No drivers available!\n";
        return;
    }

    Order currentOrder = orderQueue.front();
    orderQueue.pop();

    Driver driver = driverHeap.top();
    driverHeap.pop();

    cout << "Driver " << driver.driverID
         << " assigned to Order " << currentOrder.orderID << endl;

    currentOrder.status = "Active";
    orderMap[currentOrder.orderID] = currentOrder;

    driver.availableTime += 30; // delivery time
    driverHeap.push(driver);
}

/* =======================
   COMPLETE DELIVERY
   ======================= */

void completeDelivery(int orderID) {
    if (orderMap.find(orderID) == orderMap.end()) {

            cout << "Order not found!\n";
        return;
    }

    orderMap[orderID].status = "Delivered";
    cout << "Order " << orderID << " marked as Delivered.\n";
}

/* =======================
   VIEW ORDER SUMMARY
   ======================= */

void viewOrderSummary() {
    cout << "\n--- Order Summary ---\n";

    for (auto &pair : orderMap) {
        cout << "Order ID: " << pair.second.orderID
             << " | Status: " << pair.second.status
             << " | Address: " << pair.second.address << endl;
    }
}
