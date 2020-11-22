#include"buyer.h"

using namespace std;

void Buyer::empty_cart()
{
    for(int i=0;i<cart_.size();i++)
        cart_[i].first.first->charge(cart_[i].first.second);
    cart_.clear();
    return;
}

string Buyer::print_offers(vector<Offer*> offers, string order, string field)
{
    string result="productId | productName | offerId | offerUnitPrice | offerAmount\n";
    for(int i=0;i<offers.size();i++)
    {
        string s_unit_price=to_string(offers[i]->get_unit_price());
        s_unit_price.erase ( s_unit_price.find_last_not_of('0') + 1, std::string::npos );
        if(s_unit_price[s_unit_price.size()-1]=='.')
            s_unit_price.resize(s_unit_price.size()-1);
        result+=to_string(offers[i]->get_product_id()) +" | "+ offers[i]->get_product_name() +" | "
                + to_string(offers[i]->get_offer_id()) +" | "+ s_unit_price+" | "
                +to_string(offers[i]->get_amount())+'\n';
    }
    return result;
}

string Buyer::get_offers_on_product(Product* product)
{
    return product->print_offers();
}

string Buyer::get_product_detail(Product* product)
{
    return product->get_product_detail();
}

string Buyer::get_product_comments(Product* product)
{
    return product->get_comments();
}

void Buyer::add_to_cart(Offer* offer,int amount,string discount_code)
{
    if( offer->has_discount(discount_code) || discount_code=="NO_DISCOUNT" )
    {
        if( amount > offer->get_amount() )
            throw BadRequest();
        offer->sell(amount);
        cart_.push_back( make_pair( make_pair(offer,amount), offer->use_discount(discount_code)) );
    }
    else
        throw BadRequest();
}

string Buyer::get_cart()
{
    string result;
    if(cart_.size()==0)
        result="Empty";
    else
    {
        result="productId | productName | offerId | sellerId | totalPriceConsideringDiscount | amount\n";
        for(int i=0;i<cart_.size();i++)
        {
            result+=print_order(cart_[i]);
        }
    }
    return result;
}

double Buyer::calculate_cart_cost()
{
    double cart_price=0.0;
    for(int i=0;i<cart_.size();i++)
        cart_price+=(cart_[i].first.second*cart_[i].first.first->get_unit_price()*((100.0-cart_[i].second)/100.0));
    return cart_price;
}

vector< pair<int,Order> > Buyer::submit_cart()
{
    double cart_price=0.0;
    for(int i=0;i<cart_.size();i++)
        cart_price+=(cart_[i].first.second*cart_[i].first.first->get_unit_price()*((100.0-cart_[i].second)/100.0));
    if(cart_price>credit_)
        throw BadRequest();
    credit_-=cart_price;
    wallet_.push_back(credit_);
    vector< pair<int,Order> > sellers_payments;
    for(int i=0;i<cart_.size();i++)
        sellers_payments.push_back( make_pair(cart_[i].first.first->get_seller(), cart_[i]) );
    orders_.push_back(cart_);
    cart_.clear();
    return sellers_payments;
}

string Buyer::get_orders(int count)
{
    if(orders_.size()==0)
        throw NotFound();
    string result="productId | productName | offerId | sellerId | soldPrice | amount\n";
    for(int i=orders_.size()-1;max((int)orders_.size()-count,0)<=i;i--)
    {
        for(int j=0;j<orders_[i].size();j++)
            result+=print_order(orders_[i][j]);
        if(i>max((int)orders_.size()-count,0))
            result+="****\n";
    }
    return result;
}

void Buyer::charge_wallet(double credit)
{
    if(credit-0.001 <= 0.0001 )
        throw BadRequest();
    credit_+=credit;
    wallet_.push_back(credit_);
}

void Buyer::add_comment(Product* product, string comment, CommentClassifier* cc)
{
    if( !cc->classify_comment(comment) )
        product->add_comment(username_, comment);
    else
        throw BadComment();
    return;
}

string Buyer::compare(Product* product1, Product* product2)
{
    vector< pair<string,string> > detail1,detail2;
    detail1=product1->get_detail_vector();
    detail2=product2->get_detail_vector();
    bool are_same_products=true;
    if( detail1.size()!=detail2.size() )
        are_same_products=false;
    else
        for(int i=0;i<detail1.size();i++)
            if(detail1[i].first!=detail2[i].first)
                are_same_products=false;
    if(!are_same_products)
        throw BadRequest();
    string result=detail1[0].second+" | "+detail2[0].second+'\n';
    for(int i=1;i<detail1.size();i++)
        result+=detail1[i].first+": "+detail1[i].second+" | "+detail2[i].second+'\n';
    return result;
}
