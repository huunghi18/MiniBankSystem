#pragma once

#include <iostream>
#include "json.hpp"
#include <unordered_map>
#include <string>

using json = nlohmann::json;

class AccountRepository {
public:
    struct User {
        std::string accNum;
        uint32_t balance;
        std::string password;
    };

    bool load();
    bool save();

    bool existsUsername(const std::string &username) const;
    bool existsAccNum(const std::string &accNum) const;
    bool addUser(const std::string &username, const User &user, const std::string& accNum);

    bool getUser(const std::string &username, const std::string &password, User &out) const;
    std::string findUsernameByAccNum(const std::string &accNum) const;
    bool updateUser(const std::string &username, const User &user);

    void notifyTranfer(const std::string &username, const uint32_t &moneyToTransfer);
private:
    json m_database;
    const std::string m_dbPath = "database.json";
    std::unordered_map <std::string,User>  m_dbMap;
};