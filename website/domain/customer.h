#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__

#include<iostream>

#include"user.h"
#include"exceptions.h"

class Customer : public User {
public:
    Customer(std::string name,std::string mail,unsigned long password,std::string type);
    std::string print_products(std::vector<Product*> products);
    std::string get_wallet(int count);
    std::string print_order(Order order);
protected:
    double credit_;
    std::vector<double> wallet_;
};

#endif
