#include "Page.h"

Page::PAGENUM Page::getPage() const
{
    return m_page;
}
void Page::setPage(PAGENUM page)
{
    m_page = page;
}
void Page::processingPage()
{
    switch (m_page)
    {
    case PAGENUM::START_PAGE:
    {
        std::cout << "\r\n--- WELCOME TO MINI BANK ---";
        std::cout << "\r\n1. Login";
        std::cout << "\r\n2. Register";
        std::cout << "\r\n3. Exit";
        std::cout << "\r\nSelection: ";

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
        Account acc;
        uint8_t ret = acc.login();

        if (ret)
        {
            std::cout << "Login successful!";
            m_page = PAGENUM::MAIN_PAGE;
        }
        else
        {
            std::cout << "\r\n----------------------------------\r\n";
        }
        break;
    }
    case PAGENUM::REGISTER_PAGE:
    {
        std::cout << "\r\n-----------------REGISTER-----------------\r\n";
        Account acc;
        uint8_t ret = acc.registerNewAccount();
        if (ret)
        {
            std::cout << "Register successful! Returning to Start Page...";
        }
        else
        {
            std::cout << "Register failed! Returning to Start Page...";
        }
        m_page = PAGENUM::START_PAGE;
        std::cout << "\r\n----------------------------------\r\n";
        break;
    }
    case PAGENUM::MAIN_PAGE:
    {
        std::cout << "\r\n-----------------MAIN PAGE-----------------\r\n";

        std::cout << "\r\n1. Transaction";
        std::cout << "\r\n2. Check Balance";
        std::cout << "\r\n3. Exit";
        std::cout << "\r\nSelection: ";

        int choice;
        std::cin >> choice;
                
        break;
    }
    default:
        m_page = PAGENUM::START_PAGE;
        break;
    }
}