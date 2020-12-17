#include "Wallet.h"
using namespace std;

/*
 * Takes cash from wallet and call callback to update ui
 */
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
/*
 * Adds cash to wallet and call callback to update ui
 */
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
