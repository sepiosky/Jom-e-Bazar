#include"mobile.h"

using namespace std;

string Mobile::get_product_detail()
{
    string result=name_+'\n';
    result+="Weight: "+to_string(weight_)+'\n';
    result+="CPU Frequency: "+to_string(cpu_frequency_)+'\n';
    result+="Built-int Memory: "+to_string(built_in_memory_)+'\n';
    result+="RAM: "+to_string(ram_)+'\n';
    result+="Display Size: "+to_string(display_size_)+'\n';
    result+="Camera Resolution: "+to_string(camera_resolution_)+'\n';
    result+="Operating System: "+operating_system_+'\n';
    return result;
}

vector< pair<string,string> > Mobile::get_detail_vector()
{
    vector< pair<string,string> > result;
    result.push_back( make_pair("Name",this->name_) );
    result.push_back( make_pair("Weight",to_string(this->weight_)) );
    result.push_back( make_pair("CPU Frequency",to_string(this->cpu_frequency_)) );
    result.push_back( make_pair("Built-in Memory",to_string(this->built_in_memory_)) );
    result.push_back( make_pair("RAM",to_string(this->ram_)) );
    result.push_back( make_pair("Display Size",to_string(this->display_size_)) );
    result.push_back( make_pair("Camera Resolution",to_string(this->camera_resolution_)) );
    result.push_back( make_pair("Operating System",this->operating_system_) );
    return result;
}
