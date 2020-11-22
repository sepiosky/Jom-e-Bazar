#include "handlers.hpp"
#include "my_server.hpp"
#include "domain/bazar.h"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        Bazar *bazar = new Bazar();
        int port = atoi(argv[1]);
        MyServer server(port);
        server.get("/", new ShowFirstPage("template/index.html"));
        server.setNotFoundErrPage("static/404.html");
        server.get("/login", new ShowLoginPage("template/logincss.html"));
        server.post("/login", new LoginHandler(bazar));
        server.get("/signup", new ShowSignupPage("template/signupcss.html"));
        server.post("/signup", new SignupHandler(bazar));
        server.get("/logout", new LogoutHandler(bazar));
        server.get("/managerhome", new ShowManagerHome(bazar, "template/managerhome.html"));
        server.post("/managerhome", new ImportProducts(bazar));
        server.post("/alloffers", new PrintAllOffers(bazar, "template/alloffers.html"));
        server.get("/sellerhome", new ShowSellerHome(bazar, "template/sellerhome.html"));
        server.get("/offer", new ShowSetOfferPage(bazar, "template/setoffer.html"));
        server.post("/offer", new SetOffer(bazar));
        server.get("/buyerhome", new ShowBuyerHome(bazar, "template/buyerhome.html"));
        /*        for(int i=1;i<=1;i++)
        {
            server.get("/product-"+to_string(i)+"-detail", new ShowProductDetail(bazar,i,"template/productdetail.html"));
            server.post("/add-product-"+to_string(i)+"-to-cart", new AddToCart(bazar,i));
        }*/
        server.get("/product-detail", new ShowProductDetail(bazar, "template/productdetail.html"));
        server.post("/add-product-to-cart", new AddToCart(bazar));
        server.get("/getcart", new GetCart(bazar, "template/getcart.html"));
        server.post("/submitcart", new SubmitCart(bazar));
        server.get("/mywallet", new GetWallet(bazar, "template/getwallet.html"));
        server.post("/chargewallet", new ChargeWallet(bazar));
        server.post("/add-comment", new AddComment(bazar));
        server.run();
    }
    catch (Server::Exception e)
    {
        cerr << e.getMessage() << endl;
        return 0;
    }
}
