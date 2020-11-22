#ifndef __MANAGER_H__
#define __MANAGER_H__

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<exception>

#include"user.h"
#include"product.h"
#include"tv.h"
#include"car.h"
#include"mobile.h"
#include"offer.h"
#include"exceptions.h"

class Manager : public User {
public:
    static Manager* signup_manager(std::string username, std::string mail, unsigned long password);
    std::string get_type() { return type_; }
    std::vector<Offer*> get_offers() {throw;}
    void import_products(std::vector<Product*>& products, std::string type, std::string path);
    std::string print_offers(std::vector<Offer*> offers, std::string order="DESCEND", std::string field="offerId");

private:
    Manager(std::string username, std::string mail, unsigned long password) : User(username,mail,password,"manager") {};

    static bool sort_offer_by_id_ascend(Offer*& offer1, Offer*& offer2)
        {return offer1->get_offer_id() < offer2->get_offer_id();}
    static bool sort_offer_by_id_descend(Offer*& offer1, Offer*& offer2)
        {return offer1->get_offer_id() > offer2->get_offer_id();}
    static bool sort_offer_by_price_ascend(Offer*& offer1, Offer*& offer2);
    static bool sort_offer_by_price_descend(Offer*& offer1, Offer*& offer2);
    void add_car_csv(std::vector<Product*>& products, std::string line);
    void add_tv_csv(std::vector<Product*>& products, std::string line);
    void add_mobile_csv(std::vector<Product*>& products, std::string line);
    static Manager* site_manager;
};

#endif
