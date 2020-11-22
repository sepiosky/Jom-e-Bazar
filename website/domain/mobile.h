#ifndef __MOBILE_H__
#define __MOBILE_H__

#include<iostream>
#include<string>

#include"product.h"

class Mobile : public Product {
public:
    Mobile(std::string name, int weight, double cpu_frequency, double built_in_memory, int ram, double display_size,
            double camera_resolution, std::string operating_system) : Product(name), weight_(weight), cpu_frequency_(cpu_frequency),
            built_in_memory_(built_in_memory), ram_(ram), display_size_(display_size), camera_resolution_(camera_resolution),
            operating_system_(operating_system) {} ;
    std::string get_product_detail();
    std::vector< std::pair<std::string,std::string> > get_detail_vector();
private:
    int weight_;
    double cpu_frequency_;
    double built_in_memory_;
    int ram_;
    double display_size_;
    double camera_resolution_;
    std::string operating_system_;
};

#endif
