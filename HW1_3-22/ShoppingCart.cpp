#include <iostream>
#include <string>
#include <vector>

#include "ShoppingCart.h"
#include "ItemToPurchase.h"

using namespace std;

ShoppingCart::ShoppingCart() {
    customerName = "none";
    currentDate = "January 1, 2016";
}
ShoppingCart::ShoppingCart(string name, string date) {
    customerName = name;
    currentDate = date;
}
string ShoppingCart::GetCustomerName() {
    return customerName;
}
string ShoppingCart::GetDate() {
    return currentDate;
}
void ShoppingCart::AddItem(ItemToPurchase item) {
    cartItems.push_back(item);
}
void ShoppingCart::RemoveItem(string itemName) {
    bool itemRemoved = 0;
    int cartSize = cartItems.size();
    for (int i = 0; i < cartSize; i++) {
        if (cartItems[i].GetName() == itemName) {
            cartItems.erase(cartItems.begin() + i);
            cout << endl;
            itemRemoved = 1;
            break;
        }
    }
    if (itemRemoved == 0) {
        cout << "Item not found in cart. Nothing removed." << endl << endl;
    }
}
void ShoppingCart::ModifyItem(ItemToPurchase item, int newQuant) {
    bool itemModified = 0;
    int cartSize = cartItems.size();
    for (int i = 0; i < cartSize; i++) {
        if (cartItems[i].GetName() == item.GetName()) {
            if (!((cartItems[i].GetDescription() == "none") && (cartItems[i].GetPrice() == 0) && (cartItems[i].GetQuantity() == 0))) {
                cartItems[i].SetQuantity(newQuant);
                itemModified = 1;
            }
        }
    }
    if (itemModified == 0) {
        cout << "Item not found in cart. Nothing modified." << endl << endl;
    }
}
int ShoppingCart::GetNumItemsInCart() {
    int totQuant = 0;
    int cartSize = cartItems.size();
    for (int i = 0; i < cartSize; i++) {
        totQuant = totQuant + cartItems[i].GetQuantity();
    }
    return totQuant;
}
int ShoppingCart::GetCostOfCart() {
    int totCost = 0;
    int cartSize = cartItems.size();
    for (int i = 0; i < cartSize; i++) {
        totCost = totCost + (cartItems[i].GetQuantity() * cartItems[i].GetPrice());
    }
    return totCost;
}
void ShoppingCart::PrintTotal() {
    int totCost = 0;
    int cartSize = cartItems.size();
    int numberOfItems = 0;

    cout << customerName << "'s Shopping Cart - " << currentDate << endl;
    for (int i = 0; i < cartSize; i++) {
        numberOfItems = numberOfItems + cartItems[i].GetQuantity();
    }
    cout << "Number of Items: " << numberOfItems << endl << endl;
    for (int i = 0; i < cartSize; i++) {
        int itemTot = cartItems[i].GetQuantity() * cartItems[i].GetPrice();
        cout << cartItems[i].GetName() << " " << cartItems[i].GetQuantity() << " @ $" << cartItems[i].GetPrice() << " = $" << itemTot << endl;
        totCost = totCost + (cartItems[i].GetQuantity() * cartItems[i].GetPrice());
        numberOfItems = numberOfItems + cartItems[i].GetQuantity();
    }
    if (cartSize == 0) {
        cout << "SHOPPING CART IS EMPTY" << endl;
    }
    cout << endl << "Total: $" << totCost << endl << endl;
}
void ShoppingCart::PrintDescriptions() {
    int cartSize = cartItems.size();
    cout << customerName << "'s Shopping Cart - " << currentDate << endl << endl;
    cout << "Item Descriptions" << endl;
    for (int i = 0; i < cartSize; i++) {
        cout << cartItems[i].GetName() << ": " << cartItems[i].GetDescription() << endl;
    }
    cout << endl;
}