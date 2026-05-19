#pragma once
#include <iostream>
#include "json.hpp"
#include "AccountRepository.h"
using json = nlohmann::json;

class Account {
public:
    struct Person {
        std::string username;
        std::string password;
        uint32_t balance;
        std::string accNum;
    };
    bool registerNewAccount(AccountRepository& accountRepo);
    bool login(AccountRepository& accountRepo);
    void setBalance(uint32_t money);
    uint32_t getBalance() const;
    std::string getAccountByNumber(AccountRepository& accountRepo, std::string acc_num) const;
    void logOut(AccountRepository& accountRepo) const;
    
private:
    Person m_person;
};