#include "Account.h"
#include <fstream>
#include "json.hpp"
#include "AccountRepository.h"

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
    std::string acc_num;
    std::cout << "Enter Username: ";
    std::getline(std::cin, username);
    std::cout << "Enter PassWord: ";
    std::getline(std::cin, password);
    std::cout << "Enter Account Number: ";
    std::getline(std::cin, acc_num);
    std::cout << "account number" << acc_num;

    if (username.empty() || password.empty())
    {
        return false;
    }


    if (database.contains(username) || database.contains(username)) {
        std::cout << "Error: Username already exists!\n";
        return false;
    }

    database[username] = {
        {"password", password},
        {"balance", 0},
        {"accNum", acc_num}
    };

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
    m_person.username = username;
    m_person.balance = m_database[username]["balance"];
    return true;
}

void Account::setBalance(uint32_t money)
{
    m_person.balance = money;
}

uint32_t Account::getBalance() const
{
    return m_person.balance; 
}

std::string Account::getAccountByNumber(std::string acc_num) const{
    for (auto &[key,value] : m_database.items()) {
        if(value["accNum"] == acc_num) {
            return key;
        }
    }
    return "";
}
