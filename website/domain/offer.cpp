#include"offer.h"

using namespace std;


void Offer::generate_discount(double percent,int num)
{
    srand(time(NULL));
    for(int i=0;i<num;i++)
    {
        string random_code="";
        for(int j=0;j<10;j++)
            random_code+=alphanum[ rand() % (sizeof(alphanum)-1) ];
        if( !has_discount(random_code) )
            discount_codes_.push_back(make_pair(random_code,percent));
        else
            i--;
    }
    return;
}
bool Offer::has_discount(string code)
{
    for(int i=0;i<discount_codes_.size();i++)
        if(discount_codes_[i].first==code)
            return true;
    return false;
}
double Offer::use_discount(string code)
{
    if(has_discount(code)) {
        for(int i=0;i<discount_codes_.size();i++)
            if(discount_codes_[i].first==code)
            {
                double percent=discount_codes_[i].second;
                discount_codes_.erase( discount_codes_.begin()+i );
                return percent;
            }
    }
    return 0.0;
}

int Offer::last_offer_id_=0;
