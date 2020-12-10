#include "Wallet.h"
using namespace std;

bool Wallet::take(int price)
{
    cout << "Taking cash: " << price << endl;
    if (cash - price < 0)
    {
        return false;
    }
    cash -= price;
    update_ui();
    return true;
}

void Wallet::add(int income)
{
    cout << "Added to wallet : "<< income << endl;
    cash += income;
    update_ui();

}

int Wallet::getCash()
{
    return cash;
}

void Wallet::update_ui()
{
    ui_callback(*this);
}
