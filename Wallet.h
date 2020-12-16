#ifndef WALLET_H
#define WALLET_H
#include <iostream>
#include <functional>



class Wallet
{
public:
    Wallet(){};
    Wallet(int starting_cash): cash{starting_cash}
    {}

    bool take(int price);
    void add(int income);
    int getCash();
    void update_ui();
    std::function<void(Wallet & w)> ui_callback{};
private:
    int cash{};
};

#endif //ENTITY_H
