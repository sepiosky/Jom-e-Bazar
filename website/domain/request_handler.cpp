#include"bazar.h"

string Bazar::request_handler(string request)
{
    vector<string> datas;
    istringstream handler(request);
    string data;
    while( getline(handler,data,' ') )
        datas.push_back(data);
    for(int i=0;i<datas.size();i++)
        cerr<<datas[i]<<"-";
    cerr<<endl;
    if(datas[0]!="POST" && datas[0]!="GET")
        throw BadRequest();
    if(datas.size()>1 && datas[0]=="POST" && datas[1]=="signup")
        if( datas[2]=="?" && datas[3]=="email" && datas[5]=="username" && datas[7]=="password")
        {
            if(datas.size()==9)
                return signup(datas[6],datas[4],datas[8]);
            else if(datas.size()==11 && datas[9]=="type")
                return signup(datas[6],datas[4],datas[8],datas[10]);
            else
                throw BadRequest();
        }
    if(datas.size()>1 && datas[0]=="POST" && datas[1]=="login")
    {
        if(datas.size()==7 && datas[2]=="?" && datas[3]=="email" && datas[5]=="password")
            return login(datas[4],datas[6]);
        else
            throw BadRequest();
    }
    if(datas.size()>1 && datas[0]=="POST" && datas[1]=="logout")
    {
        if(datas.size()==2)
            return logout();
        else
            throw BadRequest();
    }

    if(datas.size()>1 && datas[0]=="POST" && datas[1]=="importProducts")
    {
        if(datas.size()==7 && datas[2]=="?" && datas[3]=="type" && datas[5]=="filePath")
            return import_products(datas[4],datas[6]);
        else
            throw BadRequest();
    }
    if(datas.size()>1 && datas[0]=="GET" && datas[1]=="offers")
    {
        if(datas.size()==7 && datas[2]=="?" && datas[3]=="order" && datas[5]=="field")
        {
            if(datas[4]!="ASCEND" || datas[4]!="DESCEND" || datas[6]!="offerId" || datas[6]!="offerPrice")
                throw;
            return print_offers(datas[4],datas[6]);
        }
        else
            throw BadRequest();
    }


    if(datas.size()>1 && datas[0]=="GET" && datas[1]=="getProducts")
    {
        if(datas.size()==2)
            return print_products();
        else
            throw BadRequest();
    }
    if(datas.size()>1 && datas[0]=="POST" && datas[1]=="offer")
    {
        if(datas.size()==9 && datas[2]=="?" && datas[3]=="productId" && datas[5]=="offerUnitPrice" && datas[7]=="offerAmount")
            return set_offer(stoi(datas[4]),stod(datas[6]),stoi(datas[8]));
        else
            throw BadRequest();
    }
    if(datas.size()>1 && datas[0]=="GET" && datas[1]=="myOffers")
    {
        if(datas.size()==2)
            return get_my_offers();
        else
            throw BadRequest();
    }
    if(datas.size()>1 && datas[0]=="POST" && datas[1]=="changeOffer")
    {
        if(datas.size()==9 && datas[2]=="?" && datas[3]=="offerId" && datas[5]=="offerUnitPrice" && datas[7]=="offerAmount")
            return change_offer(stoi(datas[4]),stod(datas[6]),stoi(datas[8]));
        else
            throw BadRequest();
    }
    if(datas.size()>1 && datas[0]=="GET" && datas[1]=="wallet")
    {
        if(datas.size()==5 && datas[2]=="?" && datas[3]=="count")
            return get_wallet(stoi(datas[4]));
        else
            throw BadRequest();
    }
    if(datas.size()>1 && datas[0]=="POST" && datas[1]=="generateDiscountCode")
    {
        if(datas.size()==9 && datas[2]=="?" && datas[3]=="offerId" && datas[5]=="discountPercent" && datas[7]=="discountNumber")
            return generate_discount(stoi(datas[4]),stod(datas[6]),stoi(datas[8]));
        else
            throw BadRequest();
    }
    if(datas.size()>1 && datas[0]=="GET" && datas[1]=="offerBuyers")
    {
        if(datas.size()==2)
            return get_offer_buyers();
        else
            throw BadRequest();
    }



    if(datas.size()>1 && datas[0]=="GET" && datas[1]=="offersOnProduct")
    {
        if(datas.size()==5 && datas[2]=="?" && datas[3]=="productId")
            return get_offers_on_product(stoi(datas[4]));
        else
            throw BadRequest();
    }
    if(datas.size()>1 && datas[0]=="GET" && datas[1]=="productDetail")
    {
        if(datas.size()==5 && datas[2]=="?" && datas[3]=="productId")
            return get_product_detail(stoi(datas[4]));
        else
            throw BadRequest();
    }
    if(datas.size()>1 && datas[0]=="GET" && datas[1]=="comments")
    {
        if(datas.size()==5 && datas[2]=="?" && datas[3]=="productId")
            return get_product_comments(stoi(datas[4]));
        else
            throw BadRequest();
    }
    if(datas.size()>1 && datas[0]=="POST" && datas[1]=="addToCart")
        if( datas.size()>6 && datas[2]=="?" && datas[3]=="offerId" && datas[5]=="amount")
        {
            if(datas.size()==7)
                return add_to_cart(stoi(datas[4]),stoi(datas[6]));
            else if(datas.size()==9 && datas[7]=="discountCode")
                return add_to_cart(stoi(datas[4]),stoi(datas[6]),datas[8]);
            else
                throw BadRequest();
        }
    if(datas.size()>1 && datas[0]=="GET" && datas[1]=="cart")
    {
        if(datas.size()==2)
            return get_cart();
        else
            throw BadRequest();
    }
    if(datas.size()>1 && datas[0]=="POST" && datas[1]=="submitCart")
    {
        if(datas.size()==2)
            return submit_cart();
        else
            throw BadRequest();
    }
    if(datas.size()>1 && datas[0]=="GET" && datas[1]=="orders")
    {
        if(datas.size()==5 && datas[2]=="?" && datas[3]=="count")
            return get_orders(stoi(datas[4]));
        else
            throw BadRequest();
    }
    if(datas.size()>1 && datas[0]=="POST" && datas[1]=="chargeWallet")
    {
        if(datas.size()==5 && datas[2]=="?" && datas[3]=="amount")
            return charge_wallet(stod(datas[4]));
        else
            throw BadRequest();
    }
    if(datas.size()>1 && datas[0]=="POST" && datas[1]=="comment")
    {
        if(datas.size()==7 && datas[2]=="?" && datas[3]=="productId" && datas[5]=="comment")
            return add_comment(stoi(datas[4]),datas[6]);
        else
            throw BadRequest();
    }
    if(datas.size()>1 && datas[0]=="GET" && datas[1]=="compare")
    {
        if(datas.size()==7 && datas[2]=="?" && datas[3]=="productId1" && datas[5]=="productId2")
            return compare(stoi(datas[4]),stoi(datas[6]));
        else
            throw BadRequest();
        }
    if(datas.size()>1 && datas[0]=="GET" && datas[1]=="offers")
    {
        if(datas.size()==2)
            return print_offers();
        else
            throw BadRequest();
    }

    throw NotFound();
}
