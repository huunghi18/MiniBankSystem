#pragma once

#include <iostream>
#include "json.hpp"
#include <unordered_map>

using json = nlohmann::json;

class AccountRepository {
public:
    bool load();
    bool save();
    bool existsUsername(const std::string &username);
private:
    struct User {
        std::string accNum;
        int balance;
        std::string password;
    };

    json m_database;
    const std::string m_dbPath = "database.json";
    std::unordered_map <string,User>  m_dbMap;

};