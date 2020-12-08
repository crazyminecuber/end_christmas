#ifndef WALLET_H
#define WALLET_H
#include "iostream"



class Wallet
{
public:
    Wallet(){};
    Wallet(int starting_cash): cash{starting_cash}
    {
        std::cout << "made a wallet" << std::endl;

    }

    bool take(int price);
    void add(int income);
    int getCash();

private:
    int cash{};
};

#endif //ENTITY_H

