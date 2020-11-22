#include "handlers.hpp"

using namespace std;

std::map<std::string, std::string> ShowFirstPage::handle(Request *req) {
    map<string, string> context;
    context["alert0"]=req->getQueryParam("alert0");
    context["alert1"]=req->getQueryParam("alert1");
    return context;
}

std::map<std::string, std::string> ShowLoginPage::handle(Request *req) {
    map<string, string> context;
    context["alert0"]=req->getQueryParam("alert0");
    context["alert1"]=req->getQueryParam("alert1");
    return context;
}

std::map<std::string, std::string> ShowSignupPage::handle(Request *req) {
    map<string, string> context;
    context["alert0"]=req->getQueryParam("alert0");
    context["alert1"]=req->getQueryParam("alert1");
    return context;
}

User* find_user_in_bazar(Bazar* bazar, string sessionId)
{
    User* commander=0;
    vector<User*> logined_users=bazar->get_logined_users();
    for(int i=0;i<logined_users.size();i++)
        if(logined_users[i]->get_username()==sessionId)
            commander=logined_users[i];
    return commander;
}

Response *SignupHandler::callback(Request *req) {
    string name = req->getBodyParam("username");
    string password1 = req->getBodyParam("password1");
    string password2 = req->getBodyParam("password2");
    string mail = req->getBodyParam("mail");
    string usertype = req->getBodyParam("usertype");
    cout<<"session id:"<<req->getSessionId()<<endl;
    cout<<name<<" "<<password1<<" "<<password2<<" "<<mail<<" "<<usertype<<endl;
    Response* res=Response::redirect("/signup");
    try {
        if( password1!=password2 || name=="" || password1=="" || mail=="")
            throw PasswordsAreNotSame();
    //        res = Response::redirect("/signup");
        else
        {
            string request="POST signup ? email "+mail+" username "+name+" password "+password1+" type "+usertype;
            bazar->handle_request(request);
            res = Response::redirect("/"+usertype+"home?alert1=Welcome "+name+"!");
            vector<User*> logined_users=bazar->get_logined_users();
            res->setSessionId( logined_users[logined_users.size()-1]->get_username() );
        }
    } catch(exception &e) {
        string error(e.what());

        return Response::redirect("/signup?alert0="+error);
    }
    return res;
}

Response *LogoutHandler::callback(Request *req) {
    try {
        User* commander=find_user_in_bazar(bazar,req->getSessionId());
        if(commander==0)
            throw PermissionDenied();
        bazar->set_commander_user(commander);
        bazar->handle_request("POST logout");
        Response* res=Response::redirect("/");
        return res;
    } catch(exception& e) {
        string error(e.what());
        return Response::redirect("/?alert0="+error);    }
}

Response *LoginHandler::callback(Request *req) {
    string mail = req->getBodyParam("mail");
    string password = req->getBodyParam("password");
    cout << "mail: " << mail << ",\tpassword: " << password << endl;
    Response *res = Response::redirect("/login");
    string request="POST login ? email "+mail+" password "+password;
    if(mail!="" && password!="")
    {
        try {
            bazar->handle_request(request);
            res = Response::redirect("/");
            vector<User*> logined_users=bazar->get_logined_users();
            res = Response::redirect("/"+logined_users[logined_users.size()-1]->get_type()+"home?alert1=Welcome "+logined_users[logined_users.size()-1]->get_username()+"!");
            res->setSessionId( logined_users[logined_users.size()-1]->get_username() );
        } catch(exception &e) {
            string error(e.what());

            return Response::redirect("/login?alert0="+error);
        }
    }
    return res;
}

std::map<std::string, std::string> ShowManagerHome::handle(Request *req) {
    try{
        User* commander=find_user_in_bazar(bazar,req->getSessionId());
        map<string, string> context;
        context["alert0"]=req->getQueryParam("alert0");
        context["alert1"]=req->getQueryParam("alert1");
        return context;
    } catch(exception& e)
    {
        string error(e.what());
        throw Server::Exception(error);
    }
}

std::map<std::string, std::string> PrintAllOffers::handle(Request *req) {

    try {
        User* commander=find_user_in_bazar(bazar,req->getSessionId());
        if(commander==0)// || commander->get_type()!="manager)
            throw PermissionDenied();
        bazar->set_commander_user(commander);
        cout<<req->getBodyParam("order")<<endl<<req->getBodyParam("field");
        string alloffers=bazar->handle_request("GET offers ? order "+req->getBodyParam("order")+" field "
                                             +req->getBodyParam("field"));
        map<string, string> context;
        istringstream splitoffers(alloffers);
        string line;
        int linecount=0;
        while( getline(splitoffers,line) )
        {
            if(!linecount)
                context["allofferstitle"]=line;
            else
            {
                vector<string> tmp=split(line,"|",false);
                context["alloffers"+to_string(linecount)+"-productid"]=tmp[0];
                context["alloffers"+to_string(linecount)+"-offerid"]=tmp[1];
                context["alloffers"+to_string(linecount)+"-unitprice"]=tmp[2];
                context["alloffers"+to_string(linecount)+"-amount"]=tmp[3];
            }
            linecount++;
        }
        return context;
    } catch(exception& e) {
        throw Server::Exception(e.what());
    }
}


Response* ImportProducts::callback(Request *req) {
    try{
        ofstream productsfile;
        productsfile.open("productsData/"+req->getBodyParam("file_name"));
        productsfile<<req->getBodyParam("file");
        productsfile.close();
        User* commander=find_user_in_bazar(bazar,req->getSessionId());
        if(commander==0)
            throw NotFound();
        bazar->set_commander_user(commander);
        string request="POST importProducts ? type "+req->getBodyParam("producttype")+" filePath "
                        +"productsData/"+req->getBodyParam("file_name");
        bazar->handle_request(request);
        Response* res = Response::redirect("/managerhome?alert1=New Products Added Successfully!");
        return res;
    } catch(exception& e) {
        string error(e.what());
        return Response::redirect("/managerhome?alert0="+error);
    }
}

std::map<std::string, std::string> ShowSellerHome::handle(Request *req) {
    User* commander=find_user_in_bazar(bazar,req->getSessionId());
    if(commander==0 || commander->get_type()!="seller")
        throw Server::Exception("Permission Denied");
    try {
        bazar->set_commander_user(commander);
        string myoffers=bazar->handle_request("GET myOffers");
        map<string, string> context;
        context.clear();
        istringstream spliter(myoffers);
        string line;
        int linecount=0;
        while( getline(spliter,line) )
        {
            if(!linecount)
            {
                linecount++;
                continue;
            }
            else
            {
                vector<string> tmp=split(line,"|",true);
                context["myoffers"+to_string(linecount)+"-productid"]=tmp[0];
                context["myoffers"+to_string(linecount)+"-offerid"]=tmp[1];
                context["myoffers"+to_string(linecount)+"-offerunitprice"]=tmp[2];
                context["myoffers"+to_string(linecount)+"-offeramount"]=tmp[3];
                linecount++;
            }
        }
        context["alert0"]=req->getQueryParam("alert0");
        context["alert1"]=req->getQueryParam("alert1");
        return context;
    } catch(exception& e) {
        string error(e.what());
        throw Server::Exception(error);
    }
}

std::map<std::string, std::string> ShowSetOfferPage::handle(Request *req) {
    User* commander=find_user_in_bazar(bazar,req->getSessionId());
    if(commander==0)// || commander->get_type()!="seller")
        throw Server::Exception("Permission Denied");
    try {
        bazar->set_commander_user(commander);
        string allproducts=bazar->handle_request("GET getProducts");
        map<string, string> context;
        istringstream spliter(allproducts);
        string line;
        int linecount=0;
        while( getline(spliter,line) )
        {
            if(!linecount)
            {
                linecount++;
                continue;
            }
            else
            {
                vector<string> tmp=split(line,"|",true);
                cout<<"test:"<<tmp[1]<<endl;
                context["allproducts"+to_string(linecount)+"-id"]=tmp[0];
                context["allproducts"+to_string(linecount)+"-name"]=tmp[1];
            }
            linecount++;
        }
        return context;
    } catch(exception& e) {
        string error(e.what());
        throw Server::Exception(error);
    }
}

Response* SetOffer::callback(Request *req) {
    User* commander=find_user_in_bazar(bazar,req->getSessionId());
    if(commander==0)
        throw PermissionDenied();
    try {
        bazar->set_commander_user(commander);
        string productid=req->getBodyParam("productid");
        string offerunitprice=req->getBodyParam("offerunitprice");
        string offeramount=req->getBodyParam("offeramount");
        Response* res=Response::redirect("/offer");
        if(stod(offerunitprice)>0.0 && stoi(offeramount)>0)
        {
            string request="POST offer ? productId "+productid+" offerUnitPrice "
                            +offerunitprice+" offerAmount "+offeramount;
            bazar->handle_request(request);
            res=Response::redirect("/sellerhome?alert1=Offer Added Successfully!");
        }
        else
            throw BadRequest();
        return res;
    } catch(exception& e) {
        string error(e.what());
        return Response::redirect("/sellerhome?alert0="+error);
    }
}

std::map<std::string, std::string> ShowBuyerHome::handle(Request *req) {
    User* commander=find_user_in_bazar(bazar,req->getSessionId());
    if(commander==0 || commander->get_type()!="buyer")
        throw Server::Exception("Permission Denied");
    try {
        bazar->set_commander_user(commander);
        string allproducts=bazar->handle_request("GET getProducts");
        map<string, string> context;
        istringstream split(allproducts);
        string line;
        int linecount=0;
        while( getline(split,line) )
        {
            if(!linecount)
                context["allproductsdetail"]=line;
            else
                context["product"+to_string(linecount)]=line;
            linecount++;
        }
        context["alert0"]=req->getQueryParam("alert0");
        context["alert1"]=req->getQueryParam("alert1");
        return context;
    } catch(exception& e) {
        string error(e.what());
        throw Server::Exception(error);
    }
}

std::map<std::string, std::string> ShowProductDetail::handle(Request *req) {
    User* commander=find_user_in_bazar(bazar,req->getSessionId());
    if(commander==0)// || commander->get_type()!="seller")
        throw Server::Exception("Permission Denied");
    try {
        productid=req->getQueryParam("productid");
        bazar->set_commander_user(commander);
        string productdetail=bazar->handle_request("GET productDetail ? productId "+productid);
        map<string, string> context;
        context["alert0"]=req->getQueryParam("alert0");
        context["alert1"]=req->getQueryParam("alert1");
        context["productid"]=productid;
        istringstream splitdetail(productdetail);
        string line;
        int linecount=0;
        vector<Product*> products=bazar->get_products();
        vector< pair<string,string> > comparevector;
        bool comparable=true;
        if(req->getQueryParam("comparewith")!="")
        {
            string path="GET compare ? productId1 "+productid+" productId2 "+req->getQueryParam("comparewith");
            try{
                string check=bazar->handle_request(path);
            } catch(exception& e) {
                comparable=false;
            }
            for(int i=0;i<products.size();i++)
                if(comparable && to_string(products[i]->get_id())==req->getQueryParam("comparewith"))
                {
                    comparevector=products[i]->get_detail_vector();
                    context["comparewith"]=products[i]->get_name();
                }
        }
        while( getline(splitdetail,line) )
        {
            if(!linecount)
                context["productname"]=line;
            else
            {
                vector<string> tmp=split(line,":",true);
                context["feature"+to_string(linecount)+"-name"]=tmp[0];
                context["feature"+to_string(linecount)+"-value"]=tmp[1];
                if(req->getQueryParam("comparewith")!="" && comparable)
                {
                    context["feature"+to_string(linecount)+"-compare"]=comparevector[linecount].second;
                    if(tmp[1][0]-'0'>=0 && tmp[1][0]-'0'<10) {
                        int feature1=stod(tmp[1]);
                        int feature2=stod(comparevector[linecount].second);
                        if(feature1<feature2)
                            context["feature"+to_string(linecount)+"-comparecolor"]="green";
                        if(feature1==feature2)
                            context["feature"+to_string(linecount)+"-comparecolor"]="black";
                        if(feature1>feature2)
                            context["feature"+to_string(linecount)+"-comparecolor"]="red";
                    }
                }
            }
            linecount++;
        }
        string productoffers=bazar->handle_request("GET offersOnProduct ? productId "+productid);
        istringstream splitoffers(productoffers);
        linecount=0;
        while( getline(splitoffers,line) )
        {
            int firstpart=line.find("|");
            int secondpart=line.find("|",firstpart+1);
            line=line.substr(secondpart+2);
            if(!linecount)
                context["offersheader"]=line;
            else
            {
                vector<string> tmp=split(line,"|",true);
                context["offer"+to_string(linecount)+"-offerid"]=tmp[0];
                context["offer"+to_string(linecount)+"-unitprice"]=tmp[1];
                context["offer"+to_string(linecount)+"-amount"]=tmp[2];
            }
            linecount++;
        }
        string allcomments=bazar->handle_request("GET comments ? productId "+productid);
        istringstream splitcomments(allcomments);
        linecount=0;
        while( getline(splitcomments,line) )
        {
            if(!linecount)
                context["commentsheader"]=line+"'s Reviews";
            else
            {
                vector<string> tmp=split(line,"|",false);
                context["comment"+to_string(linecount)+"-user"]=tmp[0];
                context["comment"+to_string(linecount)+"-comment"]=tmp[1];
            }
            linecount++;
        }
        return context;
    } catch(exception& e) {
        string error(e.what());
        throw Server::Exception(error);
    }
}

Response* AddToCart::callback(Request *req) {
    User* commander=find_user_in_bazar(bazar,req->getSessionId());
    if(commander==0)
        throw Server::Exception("Permission Denied");
    try {
        Response* res;
        bazar->set_commander_user(commander);
        bazar->handle_request("POST addToCart ? offerId "+req->getBodyParam("offerid")+" amount "+req->getBodyParam("amount"));
//        res=Response::redirect("/product-"+productid+"-detail");
        res=Response::redirect("/buyerhome?alert1=Product Added To You Cart");
        return res;
    } catch(exception& e) {
        string error(e.what());
        return Response::redirect("/buyerhome?alert0="+error);
    }
}

std::map<std::string, std::string> GetCart::handle(Request *req) {
    User* commander=find_user_in_bazar(bazar,req->getSessionId());
    if(commander==0 || commander->get_type()!="buyer")
        throw Server::Exception("Permission Denied");
    try {
        bazar->set_commander_user(commander);
        string cart=bazar->handle_request("GET cart");
        map<string, string> context;
        istringstream spliter(cart);
        string line;
        int linecount=0;
        while( getline(spliter,line) )
        {
            if(!linecount)
                context["carttitle"]=line;
            else
            {
                vector<string> tmp=split(line,"|",true);
                context["order"+to_string(linecount)+"-productid"]=tmp[0];
                context["order"+to_string(linecount)+"-productname"]=tmp[1];
                context["order"+to_string(linecount)+"-offerid"]=tmp[2];
                context["order"+to_string(linecount)+"-sellerid"]=tmp[3];
                context["order"+to_string(linecount)+"-totalprice"]=tmp[4];
                context["order"+to_string(linecount)+"-amount"]=tmp[5];
            }
            linecount++;
        }
        context["cartcost"]=to_string(commander->calculate_cart_cost());
        return context;
    } catch(exception& e) {
        throw Server::Exception(e.what());
    }
}

Response* SubmitCart::callback(Request *req) {
    User* commander=find_user_in_bazar(bazar,req->getSessionId());
    if(commander==0)
        throw Server::Exception("Permission Denied");
    try {
        Response* res;
        bazar->set_commander_user(commander);
        bazar->handle_request("POST submitCart");
        res=Response::redirect("/buyerhome?alert1=Your Cart Submited Successfully!");
        return res;
    } catch(exception& e) {
        string error(e.what());
        return Response::redirect("/buyerhome?alert0=Credit Isnt Enough,Charge Your Wallet");
    }
}

std::map<std::string, std::string> GetWallet::handle(Request *req) {
    User* commander=find_user_in_bazar(bazar,req->getSessionId());
    if(commander==0 || commander->get_type()!="buyer")
        throw Server::Exception("Permission Denied");
    try {
        bazar->set_commander_user(commander);
        string cart=bazar->handle_request("GET wallet ? count 1");
        map<string, string> context;
        istringstream split(cart);
        string line;
        int linecount=0;
        while( getline(split,line) )
        {
            if(!linecount)
                context["credittitle"]=line;
            else
                context["credit"+to_string(linecount)]=line;
            linecount++;
        }
        return context;
    } catch(exception& e) {
        string error(e.what());
        throw Server::Exception(error);
    }
}

Response* ChargeWallet::callback(Request *req) {
    User* commander=find_user_in_bazar(bazar,req->getSessionId());
    if(commander==0)
        throw Server::Exception("Permission Denied");
    try {
        Response* res;
        bazar->set_commander_user(commander);
        bazar->handle_request("POST chargeWallet ? amount "+req->getBodyParam("amount"));
        res=Response::redirect("/buyerhome?alert1=Account Charged Successfully!");
        return res;
    } catch(exception& e) {
        string error(e.what());
        return Response::redirect("/buyerhome?alert0="+error);
    }
}

Response* AddComment::callback(Request *req) {
    User* commander=find_user_in_bazar(bazar,req->getSessionId());
    if(commander==0)
        throw Server::Exception("Permission Denied");
    try {
        Response* res;
        bazar->set_commander_user(commander);
        bazar->handle_request("POST comment ? productId "+req->getBodyParam("productid")+" comment "+req->getBodyParam("comment"));
        res=Response::redirect("/product-detail?productid="+req->getBodyParam("productid")+"&alert1=Comment Added Successfully");
        return res;
    } catch(exception& e) {
        string error(e.what());
        return Response::redirect("/product-detail?productid="+req->getBodyParam("productid")+"&alert0="+error);
    }
}
