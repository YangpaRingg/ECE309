#include <iostream>
using namespace std;

#include "ItemToPurchase.h"

int main() {

    string name; // Variables to store item name input
    int price; // Variable to store item price input
    int quantity; // Variable to store item quantity
    int price1; // Variable to store total price of item 1
    int price2; // Variable to store total price of item 2

    ItemToPurchase item1; // Create instance 1 of ItemToPurchase class

    // Ask for item name
    cout << "Item 1" << endl << "Enter the item name:" << endl; // Output prompt
    getline(cin, name); // Receive input for item name
    item1.SetName(name); // Set name to name inputted

    // Ask for item price
    cout << "Enter the item price:" << endl;
    cin >> price;
    item1.SetPrice(price);

    // Ask for item quantity
    cout << "Enter the item quantity:" << endl;
    cin >> quantity;
    item1.SetQuantity(quantity);

    ItemToPurchase item2; // Create instance 2 of ItemToPurchase class
    cin.ignore();

    // Ask for item name
    cout << endl << "Item 2" << endl << "Enter the item name:" << endl; // Output prompt
    getline(cin, name); // Receive input for item name
    item2.SetName(name); // Set name to name inputted

    // Ask for item price
    cout << "Enter the item price:" << endl;
    cin >> price;
    item2.SetPrice(price);

    // Ask for item quantity
    cout << "Enter the item quantity:" << endl;
    cin >> quantity;
    item2.SetQuantity(quantity);

    // Find total cost
    cout << endl << "TOTAL COST" << endl;
    price1 = item1.GetPrice() * item1.GetQuantity(); // Find total cost of item 1
    cout << item1.GetName() << " " << item1.GetQuantity() << " @ $" << item1.GetPrice() << " = $" << price1 << endl;
    price2 = item2.GetPrice() * item2.GetQuantity(); // Find total cost of item 2
    cout << item2.GetName() << " " << item2.GetQuantity() << " @ $" << item2.GetPrice() << " = $" << price2 << endl << endl;
    cout << "Total: $" << price1 + price2 << endl; // Output total

   return 0;
}