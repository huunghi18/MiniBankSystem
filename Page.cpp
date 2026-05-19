#include "Page.h"
#include "Transaction.h"

Page::PAGENUM Page::getPage() const
{
    return m_page;
}
void Page::setPage(PAGENUM page)
{
    m_page = page;
}
void Page::processingPage(Account &account, AccountRepository& accountRepo, Transaction& trans)
{
    switch (m_page)
    {
    case PAGENUM::START_PAGE:
    {
        std::cout << "\r\n--- WELCOME TO MINI BANK ---";
        std::cout << "\r\n-1. Login";
        std::cout << "\r\n-2. Register";
        std::cout << "\r\n-3. Exit";
        std::cout << "\r\n--Selection: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear(); // Xóa lỗi
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Xóa bộ đệm
            std::cout << "Invalid input!";
            break;
        }

        if (choice == 1)
            m_page = PAGENUM::LOGIN_PAGE;
        else if (choice == 2)
            m_page = PAGENUM::REGISTER_PAGE;
        else if (choice >= 3)
            exit(0);
        break;
    }
    case PAGENUM::LOGIN_PAGE:
    {
        std::cout << "\r\n-----------------LOGIN-----------------\r\n";
        bool ret = account.login(accountRepo);

        if (ret)
        {
            m_page = PAGENUM::MAIN_PAGE;
        }
        else
        {
            m_page = PAGENUM::START_PAGE;
        }
        break;
    }
    case PAGENUM::REGISTER_PAGE:
    {
        std::cout << "\r\n-----------------REGISTER-----------------\r\n";
        bool ret = account.registerNewAccount(accountRepo);
        if (ret)
        {
            std::cout << "Returning to Start Page...";
            m_page = PAGENUM::START_PAGE;

        }
        else
        {
            //donothing
        }
        break;
    }
    case PAGENUM::MAIN_PAGE:
    {
        std::cout << "\r\n-----------------MAIN PAGE-----------------\r\n";

        std::cout << "\r\n-1. Deposit";
        std::cout << "\r\n-2. Withdraw";
        std::cout << "\r\n-3. Transaction";
        std::cout << "\r\n-4. Check Balance";
        std::cout << "\r\n-5. Logout";
        std::cout << "\r\n--Selection: ";

        int choice;
        std::cin >> choice;        
        switch(choice) {
            case 1: {
                bool ret = trans.deposit(account);
                break;
            }
            case 2: {
                bool ret = trans.withdraw(account);
                break;
            }
            case 3: {
                bool ret = trans.transfer(account, accountRepo);
                break;
            }
            case 4: {
                trans.checkBalance(account);
                break;
            }
            case 5: {
                account.logOut(accountRepo);
                
                break;
            }
            default:
                break;
        }
        
        break;
    }
    default:
        m_page = PAGENUM::START_PAGE;
        break;
    }
}