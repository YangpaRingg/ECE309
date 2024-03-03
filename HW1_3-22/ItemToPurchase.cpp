#include <iostream>
using namespace std;

#include "ItemToPurchase.h"

ItemToPurchase::ItemToPurchase() {
    itemName = "none";
    itemDescription = "none";
    itemPrice = 0;
    itemQuantity = 0;
}
ItemToPurchase::ItemToPurchase(string name, string description, int price = 0, int quantity = 0) {
    itemName = name;
    itemDescription = description;
    itemPrice = price;
    itemQuantity = quantity;
}
void ItemToPurchase::SetName(string name) {
    itemName = name;
}
string ItemToPurchase::GetName() {
    return itemName;
}
void ItemToPurchase::SetPrice(int price) {
    itemPrice = price;
}
int ItemToPurchase::GetPrice() {
    return itemPrice;
}
void ItemToPurchase::SetQuantity(int quantity) {
    itemQuantity = quantity;
}
int ItemToPurchase::GetQuantity() {
    return itemQuantity;
}
void ItemToPurchase::SetDescription(string description) {
    itemDescription = description;
}
string ItemToPurchase::GetDescription() {
    return itemDescription;
}
void ItemToPurchase::PrintItemCost() {
    cout << itemName << " " << itemQuantity << " @ $" << itemPrice << " = $" << itemQuantity * itemPrice;
}
void ItemToPurchase::PrintItemDescription() {
    cout << itemName << ": " << itemDescription;
}