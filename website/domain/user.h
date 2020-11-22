#ifndef __USER_H__
#define __USER_H__

#include<iostream>
#include<string>
#include<vector>

#include"product.h"
#include"comment_classifier.h"
#include"exceptions.h"

typedef std::pair<std::pair<Offer*,int>, double> Order;

class User {
public:
    virtual ~User() {};
    virtual std::string get_type() = 0;
    virtual std::string get_username() {return username_;}
    virtual int get_id() {return id_;}
    virtual std::string get_mail() {return mail_;}
    virtual unsigned long get_password() {return password_;}
    virtual std::vector<Offer*> get_offers() {throw PermissionDenied();}
    virtual void sell_order(Order order) {throw PermissionDenied();}
    virtual void charge_wallet(double credit) {throw PermissionDenied();}
    virtual void empty_cart() {throw PermissionDenied();}

    virtual void import_products(std::vector<Product*>& products, std::string type, std::string path)
                                                    {throw PermissionDenied();}
    virtual std::string print_offers(std::vector<Offer*> offers, std::string order="DESCEND", std::string field="offerId")
                                                    {throw PermissionDenied();}

    virtual std::string print_products(std::vector<Product*> products) {throw PermissionDenied();}
    virtual void set_offer(Offer* new_offer) {throw PermissionDenied();}
    virtual std::string print_my_offers() {throw PermissionDenied();}
    virtual void change_offer(int offer_id, double unit_price, int amount) {throw PermissionDenied();}
    virtual void generate_discount(int offer_id, double percent, int num) {throw PermissionDenied();}
    virtual std::string get_offer_buyers() {throw PermissionDenied();}

    virtual std::string get_offers_on_product(Product* product) {throw PermissionDenied();}
    virtual std::string get_product_detail(Product* product) {throw PermissionDenied();}
    virtual std::string get_product_comments(Product* product) {throw PermissionDenied();}
    virtual void add_to_cart(Offer* offer,int amount,std::string discount_code="NO_DISCOUNT") {throw PermissionDenied();}
    virtual std::string get_cart() {throw PermissionDenied();}
    virtual std::vector< std::pair<int,Order> > submit_cart() {throw PermissionDenied();}
    virtual std::string get_orders(int count) {throw PermissionDenied();}
    virtual std::string get_wallet(int count) {throw PermissionDenied();}
    virtual void add_comment(Product* product, std::string comment, CommentClassifier* cc) {throw PermissionDenied();}
    virtual std::string compare(Product* product1, Product* product2) {throw PermissionDenied();}
    virtual double calculate_cart_cost() {throw PermissionDenied();}

protected:
    User(std::string username, std::string mail, unsigned long password, std::string type) : username_(username), mail_(mail), password_(password),
                                                      id_(++last_user_id_), type_(type) {};
    std::string username_;
    std::string mail_;
    unsigned long password_;
    int id_;
    std::string type_;
private:
    static int last_user_id_;
};

#endif
