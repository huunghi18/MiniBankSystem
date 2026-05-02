#pragma once
#include <iostream>
#include <stdint.h>
class Transaction {
public:
    void deposit();
    void withdraw();
    bool transac();
    uint32_t checkBalance() const;
};