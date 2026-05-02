#pragma once
#include <iostream>
#include <limits>
#include "Account.h"
#include "Transaction.h"
class Account;

class Page
{
public:
    enum class PAGENUM
    {
        START_PAGE = 0,
        LOGIN_PAGE,
        REGISTER_PAGE,
        MAIN_PAGE,
    };
    Page(){ m_page = PAGENUM::START_PAGE; }
    PAGENUM getPage() const;
    void setPage(PAGENUM page);

    void processingPage();

private:
    PAGENUM m_page;
};