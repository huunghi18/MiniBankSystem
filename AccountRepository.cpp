#include <fstream>
#include "AccountRepository.h"

bool AccountRepository::load()
{
    std::ifstream inFile(m_dbPath);
    if(!inFile.is_open()) {
        m_database = json::object();
        return true;
    }
    try {
        inFile >> m_database;  
    }
    catch(...) {
        std::cout << "Error to parse File";
        return false;
    }
    m_dbMap.clear();
    for (auto& [username, info] : m_database.items()) {
        User user;
        user.accNum = info.value("accNum", std::string());
        user.balance = info.value("balance", 0u);
        user.password = info.value("password", std::string());
        m_dbMap[username] = user;
    }
    return true;
}

bool AccountRepository::save() {
    m_database = json::object();
    for (auto& [username, info] : m_dbMap) {
        m_database[username] = {
            {"accNum",   info.accNum},
            {"balance",  info.balance},
            {"password", info.password}
        };
    }
    try {
        std::ofstream outFile(m_dbPath);
        if (outFile.is_open())
        {
            outFile << m_database.dump(4);
            outFile.close();
        }

    } catch(...) {
        std::cerr << "Error when parse data to file";
        return false;
    }
    std::cout << "Save data to Json File \n";
    return true;
}

bool AccountRepository::existsUsername(const std::string &username) const
{
    if(m_dbMap.find(username) != m_dbMap.end()) 
    {
        std::cerr << "ERROR: Exist Username\n";
        return true;
    }
    return false;
}

bool AccountRepository::existsAccNum(const std::string &accNum) const
{
    for (auto& [key, info] : m_dbMap) {
        if(info.accNum == accNum) {
            std::cerr << "ERROR:  Exist Account Number\n";
            return true;
        }
    }
    return false;
}

bool AccountRepository::addUser(const std::string &username, const User &user, const std::string& accNum)
{
    if (existsUsername(username) || existsAccNum(accNum)) {
        return false;
    }
    m_dbMap[username] = user;
    return save();
}

bool AccountRepository::getUser(const std::string &username, const std::string &password, User &out) const
{
    auto it = m_dbMap.find(username);
    if (it == m_dbMap.end()) return false;
    out = it->second;
    if (out.password != password) return false;
    return true;
}

std::string AccountRepository::findUsernameByAccNum(const std::string &accNum) const
{
    for (auto & [username, user] : m_dbMap) {
        if (user.accNum == accNum) return username;
    }
    return std::string();
}

bool AccountRepository::updateUser(const std::string &username, const User &user)
{
    auto it = m_dbMap.find(username);
    if (it == m_dbMap.end()) return false;
    it->second = user;
    return save();
}

void AccountRepository::notifyTranfer(const std::string &username, const uint32_t &moneyToTransfer)
{
    auto it = m_dbMap.find(username);
    if(it == m_dbMap.end()) {
        return;
    }
    it->second.balance += moneyToTransfer;
    bool ret = save();
    return;
}
