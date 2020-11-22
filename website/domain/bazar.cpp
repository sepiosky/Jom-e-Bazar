#include "bazar.h"

using namespace std;

Bazar::Bazar()
{
    users_.clear();
    products_.clear();
    offers_.clear();
    commander_ = 0;
    comment_classifier_ = new CommentClassifier(CC_TRAIN_DATA_PATH, CC_CLASS_PROB_PATH);
    users_.push_back(Manager::signup_manager("admin", "admin@gmail.com", hash_password("admin")));
    //    login("admin@gmail.com","admin");
}

Bazar::~Bazar()
{
    commander_ = 0;
    for (int i = 0; i < products_.size(); i++)
        delete (products_[i]);
    products_.clear();
    for (int i = 0; i < users_.size(); i++)
        delete (users_[i]);
    users_.clear();
    for (int i = 0; i < offers_.size(); i++)
        delete (offers_[i]);
    offers_.clear();
    delete (comment_classifier_);
}

string Bazar::handle_request(string request)
{
    try
    {
        return request_handler(request);
    }
    catch (exception &e)
    {
        throw;
    }
}

unsigned long Bazar::hash_password(string password)
{
    unsigned long hash = 5381;
    for (int i = 0; i < password.size(); i++)
        hash = (hash << 5) + hash + password[i];
    return hash;
}

int Bazar::user_exists(string mail, unsigned long password)
{
    for (int i = 0; i < users_.size(); i++)
    {
        if (users_[i]->get_mail() == mail && users_[i]->get_password() == password)
            return i;
        if (users_[i]->get_mail() == mail && users_[i]->get_password() != password)
            return -2;
    }
    return -1;
}

int Bazar::username_exists(string username)
{
    for (int i = 0; i < users_.size(); i++)
        if (users_[i]->get_username() == username)
            return i;
    return -1;
}

int Bazar::mail_exists(string mail)
{
    for (int i = 0; i < users_.size(); i++)
        if (users_[i]->get_mail() == mail)
            return i;
    return -1;
}

string Bazar::signup(string username, string mail, string password, string type)
{
    try
    {
        if (username_exists(username) != -1)
            throw UsernameExists();
        if (mail_exists(mail) != -1)
            throw MailExists();
        unsigned long hashed_password = hash_password(password);
        if (type == "buyer")
            users_.push_back(new Buyer(username, mail, hashed_password));
        if (type == "seller")
            users_.push_back(new Seller(username, mail, hashed_password));
        return login(mail, password);
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::login(string mail, string password)
{
    try
    {
        unsigned long hashed_password = hash_password(password);
        int user_index = user_exists(mail, hashed_password);
        if (user_index == -1)
            throw UserDoesntExists();
        if (user_index == -2)
            throw WrongPassword();
        if (commander_ != 0)
            throw BadRequest();
        logined_users_.push_back(users_[user_index]);
        return "OK\n";
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::logout()
{
    try
    {
        if (commander_ == 0)
            throw PermissionDenied();
        try
        {
            commander_->empty_cart();
        }
        catch (exception &e)
        {
        }
        bool is_logined = false;
        for (int i = 0; i < logined_users_.size(); i++)
            if (logined_users_[i] == commander_)
            {
                is_logined = true;
                logined_users_.erase(logined_users_.begin() + i);
            }

        if (!is_logined)
            throw PermissionDenied();
        commander_ = 0;
        return "OK\n";
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::import_products(string type, string path)
{
    try
    {
        commander_->import_products(products_, type, path);
        return "OK\n";
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::print_offers(string order, string field)
{
    try
    {
        return commander_->print_offers(offers_, order, field);
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::print_products()
{
    try
    {
        return commander_->print_products(products_);
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::set_offer(int product_id, double unit_price, int amount)
{
    try
    {
        vector<Offer *> seller_offers = commander_->get_offers();
        for (int i = 0; i < seller_offers.size(); i++)
            if (seller_offers[i]->get_product_id() == product_id)
                throw BadRequest();
        int product_index = -1;
        for (int i = 0; i < products_.size(); i++)
            if (products_[i]->get_id() == product_id)
                product_index = i;
        if (product_index == -1)
            throw BadRequest();
        Offer *new_offer = new Offer(product_id, products_[product_index]->get_name(),
                                     unit_price, amount, commander_->get_id());
        offers_.push_back(new_offer);
        products_[product_index]->set_offer(new_offer);
        commander_->set_offer(new_offer);
        return "OK\n";
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::get_my_offers()
{
    try
    {
        return commander_->print_my_offers();
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::change_offer(int offer_id, double unit_price, int amount)
{
    try
    {
        commander_->change_offer(offer_id, unit_price, amount);
        return "OK\n";
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::generate_discount(int offer_id, double percent, int num)
{
    try
    {
        commander_->generate_discount(offer_id, percent, num);
        return "OK\n";
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::get_offer_buyers()
{
    try
    {
        return commander_->get_offer_buyers();
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::get_offers_on_product(int product_id)
{
    try
    {
        int product_index = -1;
        for (int i = 0; i < products_.size(); i++)
            if (products_[i]->get_id() == product_id)
                product_index = i;
        if (product_index == -1)
            throw BadRequest();
        return commander_->get_offers_on_product(products_[product_index]);
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::get_product_detail(int product_id)
{
    try
    {
        int product_index = -1;
        for (int i = 0; i < products_.size(); i++)
            if (products_[i]->get_id() == product_id)
                product_index = i;
        if (product_index == -1)
            throw BadRequest();
        return commander_->get_product_detail(products_[product_index]);
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::get_product_comments(int product_id)
{
    try
    {
        int product_index = -1;
        for (int i = 0; i < products_.size(); i++)
            if (products_[i]->get_id() == product_id)
                product_index = i;
        if (product_index == -1)
            throw BadRequest();
        return commander_->get_product_comments(products_[product_index]);
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::add_to_cart(int offer_id, int amount, string discount_code)
{
    try
    {
        Offer *offer = 0;
        for (int i = 0; i < offers_.size(); i++)
            if (offers_[i]->get_offer_id() == offer_id)
                offer = offers_[i];
        if (offer == 0)
            throw BadRequest();
        commander_->add_to_cart(offer, amount, discount_code);
        return "OK\n";
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::get_cart()
{
    try
    {
        return commander_->get_cart();
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::submit_cart()
{
    try
    {
        vector<pair<int, Order>> sellers_payments = commander_->submit_cart();
        for (int i = 0; i < sellers_payments.size(); i++)
        {
            int seller_index = -1;
            for (int j = 0; j < users_.size(); j++)
                if (users_[j]->get_id() == sellers_payments[i].first)
                    seller_index = j;
            if (seller_index == -1)
                throw BadRequest();
            users_[seller_index]->sell_order(sellers_payments[i].second);
        }
        return "OK\n";
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::get_orders(int count)
{
    try
    {
        return commander_->get_orders(count);
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::get_wallet(int count)
{
    try
    {
        return commander_->get_wallet(count);
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::charge_wallet(double amount)
{
    try
    {
        commander_->charge_wallet(amount);
        return "OK\n";
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::add_comment(int product_id, string comment)
{
    try
    {
        int product_index = -1;
        for (int i = 0; i < products_.size(); i++)
            if (products_[i]->get_id() == product_id)
                product_index = i;
        if (product_index == -1)
            throw NotFound();
        commander_->add_comment(products_[product_index], comment, comment_classifier_);
        return "OK\n";
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::compare(int product_id1, int product_id2)
{
    try
    {
        Product *product1 = 0;
        Product *product2 = 0;
        for (int i = 0; i < products_.size(); i++)
        {
            if (products_[i]->get_id() == product_id1)
                product1 = products_[i];
            if (products_[i]->get_id() == product_id2)
                product2 = products_[i];
        }
        if (product1 == 0 || product2 == 0)
            throw NotFound();
        return commander_->compare(product1, product2);
    }
    catch (exception &e)
    {
        throw;
    }
}

string Bazar::request_handler(string request)
{
    string copy = request;
    vector<string> datas;
    istringstream handler(request);
    string data;
    while (getline(handler, data, ' '))
        datas.push_back(data);
    if (datas[0] != "POST" && datas[0] != "GET")
        throw BadRequest();
    if (datas.size() > 1 && datas[0] == "POST" && datas[1] == "signup")
    {
        if (datas[2] == "?" && datas[3] == "email" && datas[5] == "username" && datas[7] == "password")
        {
            if (datas.size() == 9)
                return signup(datas[6], datas[4], datas[8]);
            else if (datas.size() == 11 && datas[9] == "type")
                return signup(datas[6], datas[4], datas[8], datas[10]);
            else
                throw BadRequest();
        }
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "POST" && datas[1] == "login")
    {
        if (datas.size() == 7 && datas[2] == "?" && datas[3] == "email" && datas[5] == "password")
            return login(datas[4], datas[6]);
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "POST" && datas[1] == "logout")
    {
        if (datas.size() == 2)
            return logout();
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "POST" && datas[1] == "evaluateModel")
    {
        if (datas.size() == 2)
        {
            comment_classifier_->test(CC_TEST_DATA_PATH);
            return "OK";
        }
        else
            throw BadRequest();
    }

    if (datas.size() > 1 && datas[0] == "POST" && datas[1] == "importProducts")
    {
        if (datas.size() == 7 && datas[2] == "?" && datas[3] == "type" && datas[5] == "filePath")
            return import_products(datas[4], datas[6]);
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "GET" && datas[1] == "offers")
    {
        if (datas.size() == 7 && datas[2] == "?" && datas[3] == "order" && datas[5] == "field")
        {
            if ((datas[4] != "ASCEND" && datas[4] != "DESCEND") || (datas[6] != "offerId" && datas[6] != "offerPrice"))
                throw NotFound();
            return print_offers(datas[4], datas[6]);
        }
        //        else
        //            throw BadRequest();
    }

    if (datas.size() > 1 && datas[0] == "GET" && datas[1] == "getProducts")
    {
        if (datas.size() == 2)
            return print_products();
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "POST" && datas[1] == "offer")
    {
        if (datas.size() == 9 && datas[2] == "?" && datas[3] == "productId" && datas[5] == "offerUnitPrice" && datas[7] == "offerAmount")
            return set_offer(stoi(datas[4]), stod(datas[6]), stoi(datas[8]));
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "GET" && datas[1] == "myOffers")
    {
        if (datas.size() == 2)
            return get_my_offers();
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "POST" && datas[1] == "changeOffer")
    {
        if (datas.size() == 9 && datas[2] == "?" && datas[3] == "offerId" && datas[5] == "offerUnitPrice" && datas[7] == "offerAmount")
            return change_offer(stoi(datas[4]), stod(datas[6]), stoi(datas[8]));
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "GET" && datas[1] == "wallet")
    {
        if (datas.size() == 5 && datas[2] == "?" && datas[3] == "count")
            return get_wallet(stoi(datas[4]));
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "POST" && datas[1] == "generateDiscountCode")
    {
        if (datas.size() == 9 && datas[2] == "?" && datas[3] == "offerId" && datas[5] == "discountPercent" && datas[7] == "discountNumber")
            return generate_discount(stoi(datas[4]), stod(datas[6]), stoi(datas[8]));
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "GET" && datas[1] == "offerBuyers")
    {
        if (datas.size() == 2)
            return get_offer_buyers();
        else
            throw BadRequest();
    }

    if (datas.size() > 1 && datas[0] == "GET" && datas[1] == "offersOnProduct")
    {
        if (datas.size() == 5 && datas[2] == "?" && datas[3] == "productId")
            return get_offers_on_product(stoi(datas[4]));
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "GET" && datas[1] == "productDetail")
    {
        if (datas.size() == 5 && datas[2] == "?" && datas[3] == "productId")
            return get_product_detail(stoi(datas[4]));
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "GET" && datas[1] == "comments")
    {
        if (datas.size() == 5 && datas[2] == "?" && datas[3] == "productId")
            return get_product_comments(stoi(datas[4]));
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "POST" && datas[1] == "addToCart")
    {
        if (datas.size() > 6 && datas[2] == "?" && datas[3] == "offerId" && datas[5] == "amount")
        {
            if (datas.size() == 7)
                return add_to_cart(stoi(datas[4]), stoi(datas[6]));
            else if (datas.size() == 9 && datas[7] == "discountCode")
                return add_to_cart(stoi(datas[4]), stoi(datas[6]), datas[8]);
            else
                throw BadRequest();
        }
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "GET" && datas[1] == "cart")
    {
        if (datas.size() == 2)
            return get_cart();
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "POST" && datas[1] == "submitCart")
    {
        if (datas.size() == 2)
            return submit_cart();
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "GET" && datas[1] == "orders")
    {
        if (datas.size() == 5 && datas[2] == "?" && datas[3] == "count")
            return get_orders(stoi(datas[4]));
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "POST" && datas[1] == "chargeWallet")
    {
        if (datas.size() == 5 && datas[2] == "?" && datas[3] == "amount")
            return charge_wallet(stod(datas[4]));
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "POST" && datas[1] == "comment")
    {
        if (datas.size() >= 7 && datas[2] == "?" && datas[3] == "productId" && datas[5] == "comment")
        {
            for (int i = datas[0].size() + datas[1].size(); i < copy.size() - 7; i++)
                if (copy.substr(i, 7) == "comment")
                {
                    datas[6] = copy.substr(i + 8);
                    break;
                }
            return add_comment(stoi(datas[4]), datas[6]);
        }
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "GET" && datas[1] == "compare")
    {
        if (datas.size() == 7 && datas[2] == "?" && datas[3] == "productId1" && datas[5] == "productId2")
            return compare(stoi(datas[4]), stoi(datas[6]));
        else
            throw BadRequest();
    }
    if (datas.size() > 1 && datas[0] == "GET" && datas[1] == "offers")
    {
        if (datas.size() == 2)
            return print_offers();
        else
            throw BadRequest();
    }

    throw NotFound();
}
