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
// #include "protocol.h"

using namespace std;

typedef char const* chars;
/*const int DIGITS_TO_SIZE_IN_BYTES_ALL = 6; // this variable is for all type of message, because is the number of digits where the size of ALL message is */

class Client{

    public:
        struct sockaddr_in stSockAddr;

        int Res;
        int SocketFD;
        int n;
        int message_server;
        int port;
        chars ip_address;

        /*char buffer[256];*/
        /*char message[256];*/
        char message[256];
        char buffer[256];
        int packet_size;
        int header_size;

        Protocol* protocol;


        Client();
        // ip, port, header_size, packet_size, 
        Client(chars, int, int, int);
        string adding_header(string);

        bool login(char*);
        void read_server();
        void write_server();
        void get_list_online();
        void start_client();
};


Client::Client(){}

Client::Client(chars ip, int port, int header, int packet)
{

    this->protocol = new Protocol();
    /*chars message = this->protocol->envelop("simple-message", "test text lalito");
    cout<<"envelop message: "<<message<<endl;
    chars unwrapped_messa = this->protocol->unwrap(message);
    cout<<"unwrapped message: "<<unwrapped_messa<<endl;*/

    this->ip_address = ip;
    this->port = port;
    this->header_size = header;
    this->packet_size = packet;
    this->SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    // error while we try create the token
    if (-1 == this->SocketFD)
    {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    memset(&this->stSockAddr, 0, sizeof(struct sockaddr_in));

    this->stSockAddr.sin_family = AF_INET;
    this->stSockAddr.sin_port = htons(this->port);
    this->Res = inet_pton(AF_INET, ip_address, &this->stSockAddr.sin_addr);

    if (0 > this->Res)
    {
        perror("error: first parameter is not a valid address family");
        close(this->SocketFD);
        exit(EXIT_FAILURE);
    }
    else if (0 == this->Res)
    {
        perror("char string (second parameter does not contain valid ipaddress");
        close(this->SocketFD);
        exit(EXIT_FAILURE);
    }

    if (-1 == connect(this->SocketFD, (const struct sockaddr *)&this->stSockAddr, sizeof(struct sockaddr_in)))
    {
        perror("connect failed");
        close(this->SocketFD);
        exit(EXIT_FAILURE);
    }
  
}


void Client::read_server()
{
    for(;;)
    {
        /*printf("message: %s\n", messa);
        chars ALL_MSG_SIZE = this->protocol->all_message_size(messa);
        printf("ALL_MSG_SIZE: %s\n", ALL_MSG_SIZE);

        n = write(this->SocketFD, ALL_MSG_SIZE, chars_to_int(ALL_MSG_SIZE));
        if (n < 0) perror("ERROR writing to socket");*/

        printf("Enter a message to server: ");
        scanf("%s" , this->message);
        chars messa = this->protocol->envelop("simple-message", this->message);

        n = write(this->SocketFD, messa, 255);
        if (n < 0) perror("ERROR writing to socket");
        
        bzero(this->buffer, 255);
        this->message_server = read(this->SocketFD, this->buffer, 255);
        if (this->message_server < 0) perror("ERROR reading from socket");

        chars unwrapped_messa = this->protocol->unwrap(this->buffer);
        printf("Message of server: << %s >>\n", unwrapped_messa);
    }

    shutdown(this->SocketFD, SHUT_RDWR);
    close(this->SocketFD);
}