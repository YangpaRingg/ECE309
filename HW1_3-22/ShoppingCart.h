#ifndef HW1_3_21_SHOPPINGCART_H
#define HW1_3_21_SHOPPINGCART_H

#endif //HW1_3_21_SHOPPINGCART_H

#include <string>
#include <vector>

#include "ItemToPurchase.h"

using namespace std;

class ShoppingCart {
public:
    ShoppingCart();
    ShoppingCart(string name, string date);
private:
    string customerName;
    string currentDate;
    vector<ItemToPurchase> cartItems;
public:
    string GetCustomerName();
    string GetDate();
    void AddItem(ItemToPurchase item);
    void RemoveItem(string item);
    void ModifyItem(ItemToPurchase item, int newQuant);
    int GetNumItemsInCart();
    int GetCostOfCart();
    void PrintTotal();
    void PrintDescriptions();
};