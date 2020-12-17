#include "Wallet.h"
using namespace std;

//Calculate income and expenditure and "stores" the money left. 

bool Wallet::take(int price)
{
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
