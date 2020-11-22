#ifndef __OFFER_H__
#define __OFFER_H__

#include<iostream>
#include<string>
#include<vector>

static const char alphanum[] =
"0123456789"
"-_"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

class Offer {
public:
    Offer(int product_id, std::string product_name, double unit_price, int amount, int seller_id) : product_id_(product_id),
            product_name_(product_name), offer_id_(++last_offer_id_), unit_price_(unit_price),
            amount_(amount), seller_id_(seller_id) {discount_codes_.clear();};
    void change_offer(double unit_price,int amount) {amount_=amount;unit_price_=unit_price;};
    void generate_discount(double percent,int num);
    bool has_discount(std::string code);
    double use_discount(std::string code);
    int get_amount() {return amount_;}
    double get_unit_price() {return unit_price_;}
    int get_product_id() {return product_id_;}
    std::string get_product_name() {return product_name_;}
    int get_offer_id() {return offer_id_;}
    void sell(int amount) {amount_-=amount;}
    void charge(int amount) {amount_+=amount;}
    int get_seller() {return seller_id_;}
    std::vector< std::pair<std::string,double> > get_discounts() { return discount_codes_; }
private:
    int product_id_;
    std::string product_name_;
    int offer_id_;
    int seller_id_;
    double unit_price_;
    int amount_;
    std::vector< std::pair<std::string,double> > discount_codes_;
    static int last_offer_id_;
};

#endif
