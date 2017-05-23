#include <sstream>
#include <string.h>
#include <iostream>

using namespace std;

typedef char const* chars;

chars concat_chars(chars a, chars b){
    char * result = (char*)malloc(strlen(a) + strlen(b) + 1);
    strcpy(result, a); // copy string a into the result.
    strcat(result, b);

    return result;
}

chars fill_zeros(int number, int how_many){
    stringstream strs;
    for (int i = 0; i < how_many; ++i)
        strs<<"0";
    strs<<number;
    string temp_str = strs.str();
    chars resp = temp_str.c_str();

    return resp;
}

int number_digits(int number){
    int digits = 0;
    while (number != 0) { number /= 10; digits++; }

    return digits;
}

chars char_to_chars(char a){
    stringstream strs;
    strs<<a;
    string temp_str = strs.str();
    chars chars_a = temp_str.c_str();

    return chars_a;
}

int chars_to_int(chars a){
    stringstream ss(a);
    long num;
    ss>>num;
    return num;
}

chars sub_chars(chars c, int pos, int range){
    cout<<"c: "<<c<<endl;
    cout<<"pos: "<<pos<<endl;
    cout<<"range: "<<range<<endl;
    stringstream strs;
    strs<<c;
    string temp_str = strs.str();
    chars sub_charss = temp_str.substr(pos, range).c_str();
    cout<<"sub_charss: "<<temp_str.substr(pos, range).c_str()<<endl;

    return sub_charss;
}

int sub_chars_int(chars c, int pos, int range){
    stringstream strs;
    strs<<c;
    string temp_str = strs.str();
    chars sub_charss = temp_str.substr(pos, range).c_str();

    return chars_to_int(sub_charss);
}

chars simple_message_env(chars m){
    int type_message = 1; // this is the type of this message func
    int size_header_2 = 6; // characters

    //(S) first part composed by header-2 and text-data
    int size_m = strlen(m);    
    int n_digits = number_digits(size_m);
    chars header2 = fill_zeros(size_m, size_header_2- n_digits);
    chars first_part = concat_chars(header2, m);
    //(E) first part composed by header-2 and text-data

    //(S) second part composed by header-1 and first part(header-2 | text-data)
    char char_size_header_2 = (char)size_header_2;
    chars chars_size_header_2 = char_to_chars(char_size_header_2);
    chars second_part = concat_chars(chars_size_header_2, first_part);
    //(E) second part composed by header-1 and first part(header-2 | text-data)

    //(S) total message composed by type and second_part(header-1 | header-2 | text-data)
    char char_type_message = (char)type_message;
    chars chars_type_message = char_to_chars(char_type_message);
    chars envelop_messa = concat_chars(chars_type_message, second_part);
    //(E) total message composed by type and second_part(header-1 | header-2 | text-data)

    return envelop_messa;
}

chars simple_message_unwr(chars m){
    int type_message = 1; // this is the type of this message func

    int size_header_2 = (int)m[1];

    int value_header2 = sub_chars_int(m, 2, size_header_2);
    cout<<"value_header2: "<<value_header2<<endl;

    chars unwrap_messa = sub_chars(m, 2 + size_header_2 , value_header2);
    cout<<"text_data: "<<unwrap_messa<<endl;

    return unwrap_messa;
}