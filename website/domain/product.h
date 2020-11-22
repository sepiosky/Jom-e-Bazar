#ifndef __Product_H__
#define __Product_H__

#include<iostream>
#include<string>
#include<vector>
#include<fstream>

#include"offer.h"

class Product {
    struct Comment{
        Comment(std::string username,std::string comment) : username_(username), comment_(comment) {} ;
        std::string username_;
        std::string comment_;
    };
public:
    virtual ~Product() {};
    virtual std::string get_product_detail() = 0;
    virtual std::string get_name() { return name_; }
    virtual int get_id() { return id_; }
    virtual std::string get_comments();
    virtual std::vector<Offer*> get_offers() {return offers_;}
    virtual void add_comment(std::string name,std::string comment) { comments_.push_back( Comment(name,comment) ); }
    virtual void set_offer(Offer* new_offer) {offers_.push_back(new_offer);}
    virtual std::string print_offers();
    virtual std::vector< std::pair<std::string,std::string> > get_detail_vector()=0;
protected:
    Product(std::string name) : name_(name) , id_(++last_Product_id_) {};
    std::string name_;
    int id_;
    std::vector<Offer*> offers_;
    std::vector<Comment> comments_;
private:
    static int last_Product_id_;
};

#endif
