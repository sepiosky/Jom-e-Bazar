#include"customer.h"

using namespace std;


Customer::Customer(string name,string mail,unsigned long password,string type)
 : User(name,mail,password,type)
 {
     credit_=0.0;
     wallet_.clear();
     wallet_.push_back(0.0);
 }

string Customer::print_products(vector<Product*> products)
{
    string result="productId | productName\n";
    for(int i=0;i<products.size();i++)
        result+=to_string(products[i]->get_id())+" | "+products[i]->get_name()+'\n';
    return result;
}

string Customer::get_wallet(int count)
{
    string result="credit\n";
    for(int i=wallet_.size()-1;max((int)wallet_.size()-count,0)<=i;i--)
    {
        string s_wallet=to_string(wallet_[i]);
        s_wallet.erase ( s_wallet.find_last_not_of('0') + 1, std::string::npos );
        if(s_wallet[s_wallet.size()-1]=='.')
            s_wallet.resize(s_wallet.size()-1);
        result+=s_wallet+'\n';
    }
    return result;
}

string Customer::print_order(Order order)
{
    string result="";
    Offer* offer=order.first.first;
    int amount=order.first.second;
    double discount=order.second;
    double price_with_discount=offer->get_unit_price()*((100.0-discount)/100.0);
    string s_unit_price=to_string(price_with_discount);
    s_unit_price.erase ( s_unit_price.find_last_not_of('0') + 1, std::string::npos );
    if(s_unit_price[s_unit_price.size()-1]=='.')
        s_unit_price.resize(s_unit_price.size()-1);
    result+=to_string(offer->get_product_id())+" | "+offer->get_product_name()+" | "+to_string(offer->get_offer_id())
                      +" | "+to_string(offer->get_seller())+" | "+s_unit_price+" | "
                      +to_string(amount)+'\n';
    return result;
}
