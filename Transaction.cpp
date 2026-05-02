#include "Transaction.h"
#include <stdint.h>
#include "Account.h"

void Transaction::deposit()
{
    std::cout << "Input money to deposit: ";
    uint32_t money;
    std::cin >> money; 
    Account &acc = Account::AccountInstance();
    acc.setBalance((acc.getBalance() + money));
    std::cout << "New balance: " << acc.getBalance();
}

void Transaction::withdraw()
{
    Account &acc = Account::AccountInstance();
    uint32_t now_balance = acc.getBalance();
    std::cout << "Input money to withdraw (less than balance): ";
    uint32_t money;
    do
    {
        std::cin >> money;
    } while (money > now_balance);
    
    acc.setBalance(now_balance - money);
    std::cout << "New balance: " << acc.getBalance();
}

bool Transaction::transac()
{
    std::cout << "Please input account number to transact: ";
    std::string ret;   
    std::string acc_num;
    if (!(std::cin >> acc_num))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input!\n";
        return false;
    }
    
    Account &acc = Account::AccountInstance();
    ret = acc.getAccountByNumber(acc_num);
    if(ret != "") {
        std::cout << "Find account succesfull: " << ret;
    }
    else {
        std:: cout << "Cannot find person";
        return false;
    }
    
    return true;
}

uint32_t Transaction::checkBalance() const
{
    Account &acc = Account::AccountInstance();
    return acc.getBalance();
}
