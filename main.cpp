#include <iostream>
#include "Page.h"
#include "Account.h"
#include "AccountRepository.h"
#include "Transaction.h"

int main() {

    Page page;
    Account account;
    AccountRepository accountRepo;
    Transaction trans;
    // load repository once
    accountRepo.load();

    while(true) {
        page.processingPage(account, accountRepo, trans);
    }
    
    return 0;
}