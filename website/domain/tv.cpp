#include"tv.h"

using namespace std;

string TV::get_product_detail()
{
    string result=name_+'\n';
    result+="Screen Size: "+to_string(screen_size_)+'\n';
    result+="Screen Type: "+screen_type_+'\n';
    result+="Resolution: "+resolution_+'\n';
    result+="3D: "+to_string(three_d_)+'\n';
    result+="HDR: "+to_string(hdr_)+'\n';
    return result;
}

vector< pair<string,string> > TV::get_detail_vector()
{
    vector< pair<string,string> > result;
    result.push_back( make_pair("Name",this->name_) );
    result.push_back( make_pair("Screen Size",to_string(this->screen_size_)) );
    result.push_back( make_pair("Screen Type",this->screen_type_) );
    result.push_back( make_pair("Resolution",this->resolution_) );
    result.push_back( make_pair("3D",to_string(this->three_d_)) );
    result.push_back( make_pair("HDR",to_string(this->hdr_)) );
    return result;
}
