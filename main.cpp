#include "protocol.h"
#include "client.h"
#include "server.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int port = 1100;
    char const* IP_SERVER = "192.168.9.104";
    chars path_bigramas = "../en.wiki.big";
    chars path_wordnet = "../CCR.WN";

    if(strcmp(argv[1], "s") == 0)
    {
        Server* s = new Server(port, 4 , 1000, path_bigramas, path_wordnet);
        /*s->load_data();*/
        s->connection();        
    }

    if(strcmp(argv[1], "c") == 0){
        Client* c = new Client(IP_SERVER, port, 4, 10);
        c->read_server();
    }
    else
        cout<<"Please insert a value to execute server(s) or client(c) "<<endl;

    return 0;
}
