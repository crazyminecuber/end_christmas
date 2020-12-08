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
    return true;
}

void Wallet::add(int income)
{
    cout << "Added to wallet : "<< income << endl;
    cash += income;

}

int Wallet::getCash()
{
    return cash;
}
