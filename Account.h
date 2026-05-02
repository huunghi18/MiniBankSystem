#pragma once
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;

class Account {
public:
    struct Person {
        std::string username;
        uint32_t balance;
    };
    bool registerNewAccount();
    bool login();
    void setBalance(uint32_t money);
    uint32_t getBalance() const;

    std::string getAccountByNumber(std::string acc_num) const;

    static Account& AccountInstance() {
        static Account instance;
        return instance;
    }
    
private:
    Account();
    const std::string m_dbPath = "database.json";
    json m_database;
    Person m_person;
};