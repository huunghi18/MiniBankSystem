#pragma once
#include <iostream>
#include <limits>
#include "Account.h"
#include "AccountRepository.h"
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

    // pass current account and repository to keep state
    void processingPage(Account &account, AccountRepository& accountRepo, Transaction& trans);

private:
    PAGENUM m_page;
};