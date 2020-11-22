#include"car.h"

using namespace std;

string Car::get_product_detail()
{
    string result=name_+'\n';
    result+="Weight: "+to_string(weight_)+'\n';
    result+="Num. of Seats: "+to_string(num_of_seats_)+'\n';
    result+="Num. of Cylinders: "+to_string(num_of_cylinders_)+'\n';
    result+="Engine Capacity: "+to_string(engine_capacity_)+'\n';
    result+="Reverse Parking Sensors: "+to_string(reverse_parking_sensors_)+'\n';
    return result;
}

vector< pair<string,string> > Car::get_detail_vector()
{
    vector< pair<string,string> > result;
    result.push_back( make_pair("Name",this->name_) );
    result.push_back( make_pair("Weight",to_string(this->weight_)) );
    result.push_back( make_pair("Num. of Seats",to_string(this->num_of_seats_)) );
    result.push_back( make_pair("Num. of Cylinders",to_string(this->num_of_cylinders_)) );
    result.push_back( make_pair("Engine Capacity",to_string(this->engine_capacity_)) );
    result.push_back( make_pair("Reverse Parking Sensors",to_string(this->reverse_parking_sensors_)) );
    return result;
}
