#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <thread>
#include <map>
#include <fstream>
#include <string>
/*#include "protocol.h"*/

using namespace std;

int DEFAUL_SIZE = 255;
typedef char const* chars;

class Server {

    public:
        struct sockaddr_in stSockAddr;
        int SocketFD;
        int port;

        char message[255];
        int n;

        int packet_size;
        int header_size;
        chars path_bigramas;
        chars path_wordnet;
        Protocol* protocol;
        map<int, int> table_clients; // <number_socket, name_number>

        Server();
        // port, header_size, packet_size,
        Server(int, int, int, chars, chars);        
        void print_table_clients();
        void connection();
        void new_client_connection(int);
        void load_data();
};

Server::Server(){}

Server::Server(int port, int header_size , int packet_size, chars p_bi, chars p_wn){
    this->protocol = new Protocol();

    this->SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    this->port = port;
    this->packet_size = packet_size;
    this->header_size = header_size;
    this->path_bigramas = p_bi;
    this->path_wordnet = path_wordnet;

    if(-1 == this->SocketFD)
    {
        perror("can not create socket");
        exit(EXIT_FAILURE);
    }

    memset(&this->stSockAddr, 0, sizeof(struct sockaddr_in));

    this->stSockAddr.sin_family = AF_INET;
    this->stSockAddr.sin_port = htons(this->port);
    this->stSockAddr.sin_addr.s_addr = INADDR_ANY;

    if(-1 == bind(this->SocketFD,(const struct sockaddr *)&this->stSockAddr, sizeof(struct sockaddr_in)))
    {
        perror("error bind failed");
        close(this->SocketFD);
        exit(EXIT_FAILURE);
    }

    if(-1 == listen(this->SocketFD, 10))
    {
        perror("error listen failed");
        close(this->SocketFD);
        exit(EXIT_FAILURE);
    }

    printf("Waiting for a connection ... \n");
}


void Server::print_table_clients(){
    map<int, int>::iterator it;
    printf("Num Socket | Number name of server \n");

    for(it=this->table_clients.begin(); it!=this->table_clients.end(); it++) {
        printf("%10d | %2d \n", it->first, it->second);
    }
}


void Server::new_client_connection(int connect_id){
    for(;;)
    {
    // do
    // {

        /*printf("DIGITS_TO_SIZE_IN_BYTES_ALL: %d\n", DIGITS_TO_SIZE_IN_BYTES_ALL);
        char header_buffer[DIGITS_TO_SIZE_IN_BYTES_ALL]; 
        bzero(header_buffer, DIGITS_TO_SIZE_IN_BYTES_ALL);
        n = read(connect_id, header_buffer, DIGITS_TO_SIZE_IN_BYTES_ALL);
        if (n < 0) perror("ERROR reading from socket");
        int int_header_buffer = 255;
        try{
            int_header_buffer = chars_to_int(header_buffer);
            printf("int_header_buffer: %d\n", int_header_buffer);
        }
        catch (int e)
        {
            printf("An exception occurred. Exception Nr. %d\n", e);            
            printf("header_buffer: %s\n", header_buffer);
        }*/

        int int_header_buffer = DEFAUL_SIZE;
        char buffer[int_header_buffer];
        bzero(buffer, int_header_buffer);
        n = read(connect_id, buffer, int_header_buffer);
        if (n < 0) perror("ERROR reading from socket");
        /*printf("buffer: %s\n", buffer);
        printf("sizeof buffer: %d\n", sizeof(buffer));*/
        
        chars unwrapped_messa = this->protocol->unwrap(buffer);
        printf("Message of client: << %s >>>\n", unwrapped_messa);

        chars messa = "";
        if(strlen(buffer) > 0){
            printf("Enter message to client: ");
            scanf("%s" , this->message);
            messa = this->protocol->envelop("simple-message", this->message);
        }
        else {
            printf("Client desconnected !!! \n");
            break;
        }

        n = write(connect_id, messa, 255);
        if (n < 0) perror("ERROR writing to socket");
    }
    // } while(buffer != "chao");
    shutdown(connect_id, SHUT_RDWR);
    close(connect_id);
}

void Server::connection(){

    for(;;){

        int ConnectFD = accept(this->SocketFD, NULL, NULL);        

        if(0 > ConnectFD)
        {
            perror("error accept failed");
            close(this->SocketFD);
            exit(EXIT_FAILURE);
        }
        printf("Client connected !!! \n");
        int size_table_clients = table_clients.size();
        table_clients[ConnectFD] = size_table_clients + 1;
        this->print_table_clients();

        char answer;
        printf("Did you want load bigramas to servers? (Y/n): ");
        scanf("%c" , &answer);
        printf("\n%c", answer);
        if(answer == 'y' || answer == 'Y'){
            printf("load_data \n");
            this->load_data();
        }

        thread t(&Server::new_client_connection, this, ConnectFD);
        t.detach();


    }
}

void Server::load_data(){
    printf("load_data \n");
    ifstream bigramas(this->path_bigramas);

    string line;
    if(bigramas.is_open())
    {
        for(int i=0; i<100; i++)
        {
            getline(bigramas, line);
            printf("%s\n", line);
        }
        bigramas.close();
    }
}