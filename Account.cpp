#include "Account.h"
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

Account::Account()
{
    std::ifstream inFile(m_dbPath);
    if(inFile.is_open()) {
        inFile >> m_database;
        inFile.close();
    }
}

bool Account::registerNewAccount()
{
    std::string username;
    std::string password;
    std::string id;
    std::cout << "Enter Username: ";
    std::cin >> username;
    std::cout << "Enter PassWord: ";
    std::cin >> password;
    std::cout << "Enter ID: ";
    std::cin >> id;

    if (username.empty() || password.empty())
    {
        return false;
    }
    json database;
    std::ifstream inFile(m_dbPath);
    if (inFile.is_open()) {
        inFile >> database;
        inFile.close();
    } 

    if (database.contains(username)) {
        std::cout << "Error: Username already exists!\n";
        return false;
    }

    for (auto it = database.begin(); it != database.end(); ++it) {
        if (it.value()["id"] == id) {
            std::cout << "Error: ID already exists!\n";
            return false;
        }
    }

    database[username] = {
        {"id", id},
        {"password", password},
        {"balance", 0}};

    std::ofstream outFile(m_dbPath);
    if (outFile.is_open())
    {
        outFile << database.dump(4);
        outFile.close();
    }

    return true;
}

bool Account::login()
{
    std::string username;
    std::string password;
    std::cout << "Enter Username: ";
    std::cin >> username;
    std::cout << "Enter PassWord: ";
    std::cin >> password;
    
    if(!(m_database.contains(username) && m_database[username]["password"] == password)) {
        std::cout << "WRONG Username or Pass! Please Retry!\n";
        return false;
    }

    return true;
}
