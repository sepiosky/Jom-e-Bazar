#ifndef __TV_H__
#define __TV_H__

#include<iostream>
#include<string>

#include"product.h"

class TV : public Product {
public:
    TV(std::string name, int screen_size, std::string screen_type, std::string resolution, bool three_d, bool hdr) : Product(name) ,
        screen_size_(screen_size), screen_type_(screen_type), resolution_(resolution), three_d_(three_d), hdr_(hdr) {};
    std::string get_product_detail();
    std::vector< std::pair<std::string,std::string> > get_detail_vector();
private:
    int screen_size_;
    std::string screen_type_;
    std::string resolution_;
    bool three_d_;
    bool hdr_;
};

#endif
