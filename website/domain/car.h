#ifndef __CAR_H__
#define __CAR_H__

#include<iostream>
#include<string>

#include"product.h"

class Car : public Product {
public:
    Car(std::string name,int weight, int num_of_seats, int num_of_cylinders ,int engine_capacity, bool reverse_parking_sensors):
        Product(name) , weight_(weight), num_of_seats_(num_of_seats), num_of_cylinders_(num_of_cylinders),
        engine_capacity_(engine_capacity), reverse_parking_sensors_(reverse_parking_sensors) {} ;
    std::string get_product_detail();
    std::vector< std::pair<std::string,std::string> > get_detail_vector();
private:
    int weight_;
    int num_of_seats_;
    int num_of_cylinders_;
    int engine_capacity_;
    bool reverse_parking_sensors_;
};

#endif
