#ifndef __SELLER_H__
#define __SELLER_H__

#include<iostream>
#include<vector>
#include<string>

#include"user.h"
#include"customer.h"
#include"offer.h"
#include"exceptions.h"

class Seller : public Customer {
public:
    Seller(std::string name,std::string mail,unsigned long password) : Customer(name,mail,password,"seller") {};
    std::string get_type() {return type_;}
    std::vector<Offer*> get_offers() {return offers_;}
    void sell_order(Order order);


    void set_offer(Offer* new_offer) {offers_.push_back(new_offer);}
    std::string print_my_offers();
    void change_offer(int offer_id, double unit_price, int amount);
    void generate_discount(int offer_id, double percent, int num);
    std::string get_offer_buyers();

private:
    std::vector<Offer*> offers_;
    std::vector<Order> orders_;
};

#endif
