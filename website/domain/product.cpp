#include"product.h"

using namespace std;

string Product::get_comments()
{
    string result=name_ + '\n';
    for(int i=comments_.size()-1;0<=i;i--)
        result+= comments_[i].username_ + " | " + comments_[i].comment_ + '\n';
    return result;
}

string Product::print_offers()
{
    string result="productId | productName | offerId | offerUnitPrice | offerAmount\n";
    string pre=to_string(id_)+" | "+name_+" | ";
    for(int i=0;i<offers_.size();i++)
    {
        string s_unit_price=to_string(offers_[i]->get_unit_price());
        s_unit_price.erase ( s_unit_price.find_last_not_of('0') + 1, std::string::npos );
        if(s_unit_price[s_unit_price.size()-1]=='.')
            s_unit_price.resize(s_unit_price.size()-1);
        result+=pre+to_string(offers_[i]->get_offer_id())+" | "+s_unit_price
                    +" | "+to_string(offers_[i]->get_amount())+'\n';
    }
    return result;
}

int Product::last_Product_id_ =0;
