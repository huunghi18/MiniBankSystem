#pragma once
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;

class Account {
public:
    Account();
    bool registerNewAccount();
    bool login();
private:
    const std::string m_dbPath = "database.json";
    json m_database;
};