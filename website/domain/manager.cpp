#include"manager.h"

using namespace std;

Manager* Manager::signup_manager(string username, string mail, unsigned long password)
{
    if(site_manager!=0)
        return site_manager;
    site_manager=new Manager(username,mail,password);
    return site_manager;
}

void Manager::add_car_csv(vector<Product*>& products, string line)
{
    istringstream csv(line);
    string data;
    getline(csv,data,','); string Name=data;
    getline(csv,data,','); int Weight=stoi(data);
    getline(csv,data,','); int Seats=stoi(data);
    getline(csv,data,','); int Cylinders=stoi(data);
    getline(csv,data,','); int EngineCapacity=stoi(data);
    getline(csv,data,','); int ReverseParkingSensors=stoi(data);
    products.push_back( new Car(Name, Weight, Seats, Cylinders, EngineCapacity,
                                ReverseParkingSensors) );
    return;
}
void Manager::add_tv_csv(vector<Product*>& products, string line)
{
    istringstream csv(line);
    string data;
    getline(csv,data,','); string Name=data;
    getline(csv,data,','); int ScreenSize=stoi(data);
    getline(csv,data,','); string ScreenType=data;
    getline(csv,data,','); string Resolution=data;
    getline(csv,data,','); int ThreeD=stoi(data);
    getline(csv,data,','); int HDR=stoi(data);
    products.push_back( new TV(Name, ScreenSize, ScreenType, Resolution, ThreeD, HDR) );
    return;
}
void Manager::add_mobile_csv(vector<Product*>& products, string line)
{
    istringstream csv(line);
    string data;
    getline(csv,data,','); string Name=data;
    getline(csv,data,','); int Weight=stoi(data);
    getline(csv,data,','); double Frequency=stod(data);
    getline(csv,data,','); double BMemory=stod(data);
    getline(csv,data,','); int RAM=stoi(data);
    getline(csv,data,','); double DisplaySize=stod(data);
    getline(csv,data,','); double CameraResolution=stod(data);
    getline(csv,data,','); string OS=data;
    products.push_back( new Mobile(Name, Weight, Frequency, BMemory, RAM,
                                DisplaySize, CameraResolution, OS) );
    return;
}
bool Manager::sort_offer_by_price_ascend(Offer*& offer1, Offer*& offer2)
{
    if(offer1->get_unit_price() == offer2->get_unit_price())
        return offer1->get_offer_id() < offer2->get_offer_id();
    return offer1->get_unit_price() < offer2->get_unit_price();
}

bool Manager::sort_offer_by_price_descend(Offer*& offer1, Offer*& offer2)
{
    if(offer1->get_unit_price() == offer2->get_unit_price())
        return offer1->get_offer_id() < offer2->get_offer_id();
    return offer1->get_unit_price() > offer2->get_unit_price();
}

void Manager::import_products(vector<Product*>& products, string type, string path)
{
    ifstream fread;
    fread.open(path);
    if(!fread.good())
        throw NotFound();
    string line;
    bool is_first_line=1;
    while(getline(fread,line))
    {
        if(is_first_line) {
            is_first_line=false;
            continue;
        }
        if(type=="car")
            add_car_csv(products,line);
        if(type=="tv")
            add_tv_csv(products,line);
        if(type=="mobile")
            add_mobile_csv(products,line);
    }
}

string Manager::print_offers(vector<Offer*> offers, string order, string field)
{
    string result="productId | offerId | offerUnitPrice | offerAmount\n";
    if(field=="offerId" && order=="ASCEND")
        sort(offers.begin(), offers.end(), sort_offer_by_id_ascend);
    if(field=="offerId" && order=="DESCEND")
        sort(offers.begin(), offers.end(), sort_offer_by_id_descend);
    if(field=="offerPrice" && order=="ASCEND")
        sort(offers.begin(), offers.end(), sort_offer_by_price_ascend);
    if(field=="offerPrice" && order=="DESCEND")
        sort(offers.begin(), offers.end(), sort_offer_by_price_descend);
    for(int i=0;i<offers.size();i++)
    {
        string s_unit_price=to_string(offers[i]->get_unit_price());
        s_unit_price.erase ( s_unit_price.find_last_not_of('0') + 1, std::string::npos );
        if(s_unit_price[s_unit_price.size()-1]=='.')
            s_unit_price.resize(s_unit_price.size()-1);
        result+=to_string(offers[i]->get_product_id()) +" | " + to_string(offers[i]->get_offer_id())
                +" | "+s_unit_price+" | "+to_string(offers[i]->get_amount())+'\n';
    }
    return result;
}


Manager* Manager::site_manager=0;
