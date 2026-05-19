#include "Transaction.h"
#include <stdint.h>
#include "Account.h"

bool Transaction::deposit(Account &account)
{
    std::cout << "Input money to deposit: ";
    uint32_t money;
    std::cin >> money; 

    account.setBalance((account.getBalance() + money));
    std::cout << "New balance: " << account.getBalance();
    return true;
}

bool Transaction::withdraw(Account &account)
{
    uint32_t money;
    uint32_t now_balance = account.getBalance();
    std::cout << "Balance: " << now_balance << std::endl;
    std::cout << "Input money to withdraw (Less than Balance): ";

    std::cin >> money;
    if (money > now_balance) {
        std::cout << "ERROR: money to withdraw is more than balance";
        return false;
    }
    account.setBalance(now_balance - money);
    std::cout << "New balance: " << account.getBalance();
    return true;
}

bool Transaction::transfer(Account &account, AccountRepository &accountRepo)
{
    std::cout << "Please input account number to transfer: ";
    std::string usernameToTransfer;   
    std::string acc_num;
    uint32_t moneyToTransfer;
    uint32_t now_balance = account.getBalance();

    if (!(std::cin >> acc_num))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input!\n";
        return false;
    }
    
    usernameToTransfer = account.getAccountByNumber(accountRepo, acc_num);

    if (acc_num == account.getAccountNumber()) {
        std::cout << "ERROR: Cannot transfer to yourself!\n";
        return false;
    }

    if(usernameToTransfer != "") {
        std::cout << "Find account succesfull: " << usernameToTransfer << std::endl;
    }
    else {
        std:: cout << "Cannot find person\n";
        return false;
    }
    std::cout << "Please input money to transfer: ";
    if (!(std::cin >> moneyToTransfer))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input!\n";
        return false;
    }
    if (moneyToTransfer > now_balance) {
        std::cout << "ERROR: money to transfer is more than balance\n";
        return false;
    }
    account.setBalance(now_balance - moneyToTransfer);
    std::cout << "Transfer to: " << usernameToTransfer << " with " << moneyToTransfer << " successfully! \n";
    std::cout << "New balance: " << account.getBalance() << std::endl;

    accountRepo.notifyTranfer(usernameToTransfer, moneyToTransfer);
    return true;
}

void Transaction::checkBalance(Account &account) const
{
    std::cout << "Balance: "<< account.getBalance() << std::endl;
}
