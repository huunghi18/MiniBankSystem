#pragma once
#include <iostream>
#include <stdint.h>
#include "Account.h"

class Transaction {
public:
    bool deposit(Account &account);
    bool withdraw(Account &account);
    bool transfer(Account &account, AccountRepository &accountRepo);
    void checkBalance(Account &account) const;
};