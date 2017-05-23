
#include "client.cpp"
#include "server.cpp"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int port = 1100;
    if(strcmp(argv[1], "s") == 0)
    {
        Server* s = new Server(port, 4 , 1000);
        s->connection();        
    }
    if(strcmp(argv[1], "c") == 0){
        Client* c = new Client("192.168.0.17", port, 4, 10);
        c->read_server();
    }
    else
        cout<<"Please insert a value to execute server(s) or client(c) "<<endl;

    return 0;
}
