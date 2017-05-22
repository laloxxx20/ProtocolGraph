#include <sstream>
#include <string.h>
#include <iostream>

using namespace std;

char const* concat_chars(char const* a, char const* b){
    char * result = (char*)malloc(strlen(a) + strlen(b) + 1);
    strcpy(result, a); // copy string one into the result.
    strcat(result, b);
    return (char const*)result;
}

char const* int_to_chars(int number){
    stringstream strs;
    strs << number;
    string temp_str = strs.str();
    return (char const *)temp_str.c_str();
}

char const* fill_zeros(char const* number, int how_many){
    cout<<"number: "<<number<<endl;

    /*for(int i=0; i<how_many; i++)
        number = concat_chars((char const*)"0", number);*/
    return number;
}

char const* simple_message(char const* m){
    int size_header_2 = 6; // characters    
    int size_m = strlen(m);
    cout<<"size_m: "<<size_m<<endl;
    char const* size_m_char = int_to_chars(size_m);
    cout<<"size_m_char: "<<size_m_char<<"oooooo"<<endl;
    cout<<"concat_chars: "<<concat_chars((char const*)"fffff", size_m_char)<<endl;
    cout<<"fill_zeros: "<<fill_zeros(size_m_char, 6)<<endl;
    return "something";
}