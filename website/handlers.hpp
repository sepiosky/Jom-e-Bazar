#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../APHTTP/server/server.hpp"
#include "domain/bazar.h"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

class ShowFirstPage : public TemplateHandler {
public:
    ShowFirstPage(std::string path_) : TemplateHandler(path_) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class ShowLoginPage : public TemplateHandler {
public:
    ShowLoginPage(std::string path_) : TemplateHandler(path_) {} ;
    std::map<std::string, std::string> handle(Request *req);
};


class ShowSignupPage : public TemplateHandler {
public:
    ShowSignupPage(std::string path_) : TemplateHandler(path_) {} ;
    std::map<std::string, std::string> handle(Request *req);
};



class LoginHandler : public RequestHandler {
    Bazar* bazar;
public:
    LoginHandler(Bazar* bazar_) : bazar(bazar_) {} ;
    Response *callback(Request *);
};

class SignupHandler : public RequestHandler {
    Bazar* bazar;
public:
    SignupHandler(Bazar* bazar_) : bazar(bazar_) {} ;
    Response *callback(Request *);
};

class LogoutHandler : public RequestHandler {
    Bazar* bazar;
public:
    LogoutHandler(Bazar* bazar_) : bazar(bazar_) {} ;
    Response *callback(Request *);
};

class ShowManagerHome : public TemplateHandler {
    Bazar* bazar;
public:
    ShowManagerHome(Bazar* bazar_,std::string path_) : TemplateHandler(path_), bazar(bazar_) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class ImportProducts : public RequestHandler {
    Bazar* bazar;
public:
    ImportProducts(Bazar* bazar_) : bazar(bazar_) {};
    Response* callback(Request *);
};

class PrintAllOffers : public TemplateHandler {
    Bazar* bazar;
public:
    PrintAllOffers(Bazar* bazar_,std::string path_) : TemplateHandler(path_), bazar(bazar_) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class ShowSellerHome : public TemplateHandler {
    Bazar* bazar;
public:
    ShowSellerHome(Bazar* bazar_,std::string path_) : TemplateHandler(path_), bazar(bazar_) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class ShowSetOfferPage : public TemplateHandler {
    Bazar* bazar;
public:
    ShowSetOfferPage(Bazar* bazar_,std::string path_) : TemplateHandler(path_), bazar(bazar_) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class SetOffer : public RequestHandler {
    Bazar* bazar;
public:
    SetOffer(Bazar* bazar_) : bazar(bazar_) {};
    Response* callback(Request *);
};

class ShowBuyerHome : public TemplateHandler {
    Bazar* bazar;
public:
    ShowBuyerHome(Bazar* bazar_,std::string path_) : TemplateHandler(path_), bazar(bazar_) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class ShowProductDetail : public TemplateHandler {
    Bazar* bazar;
    std::string productid;
public:
    ShowProductDetail(Bazar* bazar_, std::string path_) : TemplateHandler(path_), bazar(bazar_) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class AddToCart : public RequestHandler {
    Bazar* bazar;
    std::string productid;
public:
    AddToCart(Bazar* bazar_) : bazar(bazar_) {};
    Response* callback(Request *);
};

class GetCart : public TemplateHandler {
    Bazar* bazar;
public:
    GetCart(Bazar* bazar_, std::string path_) : TemplateHandler(path_), bazar(bazar_) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class SubmitCart : public RequestHandler {
    Bazar* bazar;
public:
    SubmitCart(Bazar* bazar_) : bazar(bazar_) {};
    Response* callback(Request *);
};

class GetWallet : public TemplateHandler {
    Bazar* bazar;
public:
    GetWallet(Bazar* bazar_, std::string path_) : TemplateHandler(path_), bazar(bazar_) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class ChargeWallet : public RequestHandler {
    Bazar* bazar;
public:
    ChargeWallet(Bazar* bazar_) : bazar(bazar_) {};
    Response* callback(Request *);
};

class AddComment : public RequestHandler {
    Bazar* bazar;
public:
    AddComment(Bazar* bazar_) : bazar(bazar_) {};
    Response* callback(Request *);
};



#endif
