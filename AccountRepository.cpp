#include <fstream>
#include "AccountRepository.h"

bool AccountRepository::load()
{
    std::ifstream inFile(m_database);
    if(!inFile.is_open()) {
        m_database = json::object();
        return true;
    }
    try {
        inFile >> m_database;  
    }
    catch(...) {
        inFile >> m_database;
        std::cout << "Error to parse File";
        return false;
    }
    for (auto& [username, info] : m_database.items()) {
        User user;
        user.accNum = info["accNum"].get<std::string>();
        user.balance = info["balance"].get<int>();
        user.password = info["password"].get<std::string>();
        m_dbMap[username] = user;
    }
    return true;
}

bool AccountRepository::save() {
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
        std::cout << "Error when parse data to file";
        return false;
    }

    return true;
}

bool AccountRepository::existsUsername(const std::string &username)
{

    return false;
}
