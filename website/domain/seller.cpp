#include"seller.h"

using namespace std;

string Seller::print_my_offers()
{
    string result="productId | offerId | offerUnitPrice | offerAmount\n";
    for(int i=0;i<offers_.size();i++)
    {
        string s_unit_price=to_string(offers_[i]->get_unit_price());
        s_unit_price.erase ( s_unit_price.find_last_not_of('0') + 1, std::string::npos );
        if(s_unit_price[s_unit_price.size()-1]=='.')
            s_unit_price.resize(s_unit_price.size()-1);
        result+=to_string(offers_[i]->get_product_id()) +" | " + to_string(offers_[i]->get_offer_id())
                +" | "+s_unit_price+" | "+to_string(offers_[i]->get_amount())+'\n';
    }
    return result;
}

void Seller::change_offer(int offer_id, double unit_price, int amount)
{
    bool offer_exists=false;
    for(int i=0;i<offers_.size();i++)
        if(offers_[i]->get_offer_id()==offer_id)
        {
            offer_exists=true;
            offers_[i]->change_offer(unit_price, amount);
        }
    if(!offer_exists)
        throw BadRequest();
}

void Seller::generate_discount(int offer_id, double percent, int num)
{
    bool offer_exists=false;
    for(int i=0;i<offers_.size();i++)
        if(offers_[i]->get_offer_id()==offer_id)
        {
            offer_exists=true;
            offers_[i]->generate_discount(percent, num);
        }
    if(!offer_exists)
        throw BadRequest();
}

void Seller::sell_order(Order order)
{
    orders_.push_back(order);
    credit_+=(order.first.second*order.first.first->get_unit_price()*((100.0-order.second)/100.0));
    wallet_.push_back(credit_);
}

string Seller::get_offer_buyers()
{
    string result="";
    if(orders_.size()==0)
        result="Empty";
    else
    {
        result="productId | offerId | buyerId | soldPrice | amount\n";
        for(int i=0;i<orders_.size();i++)
            result+=print_order(orders_[i]);
    }
    return result;
}
