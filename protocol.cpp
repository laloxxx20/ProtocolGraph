#include <iostream>
#include <vector>
#include <math.h>
#include <map>
#include "messages.cpp"

using namespace std;

typedef const char* (*func)(const char*);

class Protocol{

    public:
        char* message;
        int size_header_type_message;
        int type_message; // 8 bits in decimal, so max of 255
        map<const char*, func> type_messages;

        Protocol();

        // (type_message, data) 
        char const* envelop(char const*, char const*);

        // (data)
        char const* unwrap(char const*);

        // transform first character to bits
        vector<int> transform_char_to_bits(unsigned char);

        int transform_bits_to_decimal(vector<int>);
        void print_binary(vector<int>);

};

Protocol::Protocol(){
    this->size_header_type_message = 8;
    this->type_messages["simple-message"] = simple_message;
}

void Protocol::print_binary(vector<int> v){
    for(int i=0; i<v.size(); i++)
        cout<<v[i]<<" ";
}

// Is saving in reverse way
vector<int> Protocol::transform_char_to_bits(unsigned char type){
    vector<int> binary;
    for(int i = 0; i < this->size_header_type_message; i++)
        binary.push_back((type >> i) & 1 );
    this->print_binary(binary);

    return binary;
}

int Protocol::transform_bits_to_decimal(vector<int> v){
    int result = 0;
    int j=0;
    for(int i=0; i<v.size(); i++)
    {
        if(v[i])
            result += pow(2, i);
    }

    return result;
}


char const* Protocol::unwrap(char const* data){
    cout<<"unwrap"<<endl;
}

char const* Protocol::envelop(char const* type_messa, char const* data){

    map<const char*, func>::iterator it;
    // searching a func in map of type of messages to envelop with func found
    it = this->type_messages.find(type_messa);

    return it->second(data);
}
