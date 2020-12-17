#ifndef WALLET_H
#define WALLET_H
#include <iostream>
#include <functional>


class Wallet
{
public:
    Wallet(){};
    Wallet(int starting_cash): cash{starting_cash}
    {
        std::cout << "Wallet created" << std::endl;
    }

    bool take(int price);
    void add(int income);
    int getCash();
    void update_ui();
    void set_ui_callback(std::function<void(Wallet const & w)> const & f){ui_callback = f;}
private:
    std::function<void(Wallet const & w)> ui_callback{};
    int cash{};
};

#endif //ENTITY_H
