#ifndef __BUYER_H__
#define __BUYER_H__

#include<iostream>
#include<vector>
#include<string>

#include"user.h"
#include"comment_classifier.h"
#include"customer.h"
#include"offer.h"
#include"exceptions.h"

class Buyer : public Customer {
public:
    Buyer(std::string name,std::string mail,unsigned long password) : Customer(name,mail,password,"buyer") {cart_.clear();};
    std::string get_type() {return type_;}
    void empty_cart();
    void charge_wallet(double credit);
    double calculate_cart_cost();

    std::string print_offers(std::vector<Offer*> offers, std::string order="DESCEND", std::string field="offerId");

/*    void set_offer(int product_id, int unit_price, int amount) {throw;}
    string print_my_offers() {throw;}
    void change_offer(int offer_id, int unit_price, int amount) {throw;}
    void generate_discount(int offer_id, int percent, int num) {throw;}*/

    std::string get_offers_on_product(Product* product);
    std::string get_product_detail(Product* product);
    std::string get_product_comments(Product* product);
    void add_to_cart(Offer* offer,int amount,std::string discount_code="NO_DISCOUNT");
    std::string get_cart();
    std::vector< std::pair<int,Order> > submit_cart();
    std::string get_orders(int count);
    void add_comment(Product* product, std::string comment, CommentClassifier* cc);
    std::string compare(Product* product1, Product* product2);



private:
    std::vector<Order> cart_;
    std::vector< std::vector<Order> > orders_;
};

#endif
