#include "Account.h"
#include <fstream>
#include "json.hpp"
#include "AccountRepository.h"

using json = nlohmann::json;

bool Account::registerNewAccount(AccountRepository& accountRepo)
{
    std::string username;
    std::string password;
    std::string acc_num;

    std::cout << "Enter Username: ";
    if (!std::getline(std::cin >> std::ws, username)) {
        std::cerr << "ERROR: Input error reading username\n";
        return false;
    }

    std::cout << "Enter PassWord: ";
    if (!std::getline(std::cin >> std::ws, password)) {
        std::cerr << "ERROR: Input error reading password\n";
        return false;
    }

    std::cout << "Enter Account Number: ";
    if (!std::getline(std::cin >> std::ws, acc_num)) {
        std::cerr << "ERROR: Input error reading account number\n";
        return false;
    }

    if (username.empty() || password.empty() || acc_num.empty())
    {
        std::cerr << "ERROR: Username or Password or Account number is empty";
        return false;
    }


    AccountRepository::User user;
    user.accNum = acc_num;
    user.balance = 0;
    user.password = password;

    if (!accountRepo.addUser(username, user, acc_num)) {
        std::cerr << "ERROR: Failed to add user\n";
        return false;
    }
    std::cout << "Register successful! \n";
    return true;
}

bool Account::login(AccountRepository& accountRepo)
{
    std::string username;
    std::string password;
    std::cout << "Enter Username: ";
    std::getline(std::cin >> std::ws, username);
    std::cout << "Enter PassWord: ";
    std::getline(std::cin >> std::ws, password);

    AccountRepository::User user;
    if (!accountRepo.getUser(username, password, user)) {
        std::cout << "WRONG Username or Pass! Please Retry!\n";
        return false;
    }

    m_person.username = username;
    m_person.balance = user.balance;
    m_person.accNum = user.accNum;
    m_person.password = user.password;
    std::cout << "Login successful!\n";
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

std::string Account::getAccountByNumber(AccountRepository& accountRepo, std::string acc_num) const{
    return accountRepo.findUsernameByAccNum(acc_num);
}

void Account::logOut(AccountRepository& accountRepo) const
{
    AccountRepository::User user;
    user.accNum = m_person.accNum;
    user.balance = m_person.balance;
    user.password = m_person.password;
    accountRepo.updateUser(m_person.username, user);
}