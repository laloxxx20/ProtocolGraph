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
/*#include "protocol.h"*/

using namespace std;

typedef char const* chars;

class Server {

    public:
        struct sockaddr_in stSockAddr, client_addr;
        int SocketFD;
        int port;
        char buffer[255];
        char message[255];
        int n;

        int packet_size;
        int header_size;
        Protocol* protocol;

        int num_clients;
        int *socket_clients;

        Server();
        // port, header_size, packet_size,
        Server(int, int, int);
        void connection();

        void establish_clients();

};

Server::Server(){}

Server::Server(int port, int header_size , int packet_size){
    
    this->num_clients = 3;
    this->socket_clients = new int[num_clients]; //for 3 clients

    this->protocol = new Protocol();

    this->SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    this->port = port;
    this->packet_size = packet_size;
    this->header_size = header_size;

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

        for(;;)
        {
        /*do
        {*/
            bzero(this->buffer, 256);
            n = read(ConnectFD, this->buffer, 255);
            if (n < 0) perror("ERROR reading from socket");
            
            chars unwrapped_messa = this->protocol->unwrap(this->buffer);
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

            n = write(ConnectFD, messa, 255);
            if (n < 0) perror("ERROR writing to socket");
        }
        /*} while(buffer != "chao");*/
        shutdown(ConnectFD, SHUT_RDWR);
        close(ConnectFD);
    }
}

void Server::establish_clients()
{
    socklen_t len;
    int i=0;
    while(i<num_clients){
        
        len = sizeof(client_addr);
        socket_clients[i] = accept(SocketFD, (struct sockaddr *)&client_addr, &len);
   
        if(0 > socket_clients[i])
        {
            perror("error accept failed");
            close(SocketFD);
            exit(EXIT_FAILURE);
        }
        else{
            printf("Client %d ready\n",i);
            i++;
        }
    }



    chars messa = "hola a todos";

    n = write(socket_clients[1], messa, 255); //test
    if (n < 0) perror("ERROR writing to socket");

    n = read(socket_clients[1], this->buffer, 255);
    if (n < 0) perror("ERROR reading from socket");
    printf("Mensaje: [%s]\n",this->buffer);
    

    printf("Clients established, ready to path\n");
    for (int i = 0; i < num_clients; ++i)
    {
        shutdown(socket_clients[i], SHUT_RDWR);
        close(socket_clients[i]);
    }
    
    
}