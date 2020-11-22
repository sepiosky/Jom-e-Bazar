#ifndef __BAZAR_H__
#define __BAZAR_H__

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<sstream>
#include<fstream>

#include"product.h"
#include"user.h"
#include"manager.h"
#include"buyer.h"
#include"seller.h"
#include"offer.h"
#include"exceptions.h"
#include"comment_classifier.h"

#define CAR_FILE_PATH "./Data/Car.csv"
#define TV_FILE_PATH "./Data/TV.csv"
#define MOBILE_FILE_PATH "./Data/Mobile.csv"
#define ACCEPTED_REQUESTS "Accepted_Requests.txt"
#define CC_TRAIN_DATA_PATH "domain/train.csv"
#define CC_TEST_DATA_PATH "domain/test.csv"
#define CC_CLASS_PROB_PATH "domain/class probabilities"

class Bazar {
public:
    Bazar();
    ~Bazar();
    std::string handle_request(std::string request);
    std::vector<User*> get_logined_users() {return logined_users_;}
    std::vector<Product*> get_products() {return products_;}
    void set_commander_user(User* user) {commander_=user;}
private:
    std::string request_handler(std::string request);

    std::string signup(std::string username, std::string mail,std::string password,std::string type="buyer");
    std::string login(std::string mail,std::string password);
    std::string logout();

    std::string import_products(std::string type,std::string path);
    std::string print_offers(std::string order="ASCEND", std::string field="offerId");

    std::string print_products();
    std::string set_offer(int product_id, double unit_price, int amount);
    std::string get_my_offers();
    std::string change_offer(int offer_id, double unit_price, int amount);
    std::string generate_discount(int offer_id, double percent, int num);
    std::string get_offer_buyers();

    std::string get_offers_on_product(int product_id);
    std::string get_product_detail(int product_id);
    std::string get_product_comments(int product_id);
    std::string add_to_cart(int offer_id, int amount, std::string discount_code="NO_DISCOUNT");
    std::string get_cart();
    std::string submit_cart();
    std::string get_orders(int count);
    std::string get_wallet(int count);
    std::string charge_wallet(double amount);
    std::string add_comment(int product_id, std::string comment);
    std::string compare(int product_id1, int product_id2);


    int user_exists(std::string mail, unsigned long password);
    int mail_exists(std::string mail);
    int is_user_logined(std::string mail, unsigned long password);
    int username_exists(std::string username);
    unsigned long hash_password(std::string password);


    std::vector<Product*> products_;
    std::vector<User*> users_;
    std::vector<Offer*> offers_;
    User* commander_;
    std::vector<User*> logined_users_;
    CommentClassifier* comment_classifier_;

};

#endif
