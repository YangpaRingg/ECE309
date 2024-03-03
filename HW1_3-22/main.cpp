#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "ShoppingCart.h"

void PrintMenu() {

    cout << "MENU" << endl;
    cout << "a - Add item to cart" << endl;
    cout << "d - Remove item from cart" << endl;
    cout << "c - Change item quantity" << endl;
    cout << "i - Output items' descriptions" << endl;
    cout << "o - Output shopping cart" << endl;
    cout << "q - Quit" << endl << endl;

}

void ExecuteMenu(char option, ShoppingCart& theCart) {

    // Option q
    if (option == 'q') {}

    // Option a
    if (option == 'a') {
        string itemName;
        string itemDesc;
        int itemPrice;
        int itemQuantity;

        cout << "ADD ITEM TO CART" << endl;

        cout << "Enter the item name:" << endl;
        cin.ignore();
        getline(cin, itemName);
        cout << "Enter the item description:" << endl;
        getline(cin, itemDesc);
        cout << "Enter the item price:" << endl;
        cin >> itemPrice;
        cout << "Enter the item quantity:" << endl;
        cin >> itemQuantity;
        cout << endl;

        ItemToPurchase item(itemName, itemDesc, itemPrice, itemQuantity);

        theCart.AddItem(item);
    }

    // Option d
    if (option == 'd') {
        string itemName;

        cout << "REMOVE ITEM FROM CART" << endl;

        cout << "Enter name of item to remove:" << endl;
        cin.ignore();
        getline(cin, itemName);

        theCart.RemoveItem(itemName);
    }

    // Option c
    if (option == 'c') {
        string itemName;
        int newQuantity;

        cout << "CHANGE ITEM QUANTITY" << endl;

        cout << "Enter the item name:" << endl;
        cin.ignore();
        getline(cin, itemName);
        cout << "Enter the new quantity:" << endl;
        cin >> newQuantity;

        ItemToPurchase item;
        item.SetName(itemName);

        theCart.ModifyItem(item, newQuantity);
    }

    // Option i
    if (option == 'i') {
        cout << "OUTPUT ITEMS' DESCRIPTIONS" << endl;
        theCart.PrintDescriptions();
    }

    // Option o
    if (option == 'o') {
        cout << "OUTPUT SHOPPING CART" << endl;
        theCart.PrintTotal();
    }
}

int main() {

    string customerName;
    string date;
    char option;

    cout << "Enter customer's name:" << endl; // Ask for customer's name
    getline(cin, customerName);
    cout << "Enter today's date:" << endl; // Ask for the date
    getline(cin, date);

    ShoppingCart cart(customerName, date); // Create ShoppingCart with inputted parameters
    ShoppingCart &ref = cart; // Create reference to shopping cart

    cout << endl << "Customer name: " << customerName << endl;
    cout << "Today's date: " << date << endl << endl;

    while (option != 'q'){
        PrintMenu();
        cout << "Choose an option:" << endl;
        cin >> option;
        while (!((option == 'q')||(option == 'a')||(option == 'd')||(option == 'c')||(option == 'i')||(option == 'o'))) {
            cout << "Choose an option:" << endl;
            cin >> option;
        }
        ExecuteMenu(option, ref);
    }

    return 0;
}