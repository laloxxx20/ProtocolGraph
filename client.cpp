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
/*#include "game.cpp"*/

using namespace std;


class Client
{
    public:
        struct sockaddr_in stSockAddr;

        int Res;
        int SocketFD;
        int n;
        int message_server;
        int port;
        char* ip_address;

        /*char buffer[256];*/
        /*char message[256];*/
        int buffer;
        int message;
        string name;
        int packet_size;
        int header_size;
        /*x*/
        char chip;


        Client();
        // ip, port, header_size, packet_size, 
        Client(char*, int, int, int);
        string adding_header(string);

        bool login(char*);
        void read_server();
        void write_server();
        void get_list_online();
        void start_client();
};


Client::Client(){}

Client::Client(char* ip, int port, int header, int packet)
{
    this->ip_address = ip;
    this->port = port;
    this->header_size = header;
    this->packet_size = packet;
    //game = new Game(board);
    SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    // error while we try create the token
    if (-1 == SocketFD)
    {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(this->port);
    this->Res = inet_pton(AF_INET, ip_address, &stSockAddr.sin_addr);

    if (0 > Res)
    {
        perror("error: first parameter is not a valid address family");
        close(SocketFD);
        exit(EXIT_FAILURE);
    }
    else if (0 == Res)
    {
        perror("char string (second parameter does not contain valid ipaddress");
        close(SocketFD);
        exit(EXIT_FAILURE);
    }

    if (-1 == connect(SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
    {
        perror("connect failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
    }
  
}

void Client::read_server()
{
    for(;;)
    {
        //game->draw_board();
        printf("\n Your sign to play is : %c \n", this->chip);
        printf("Introduce a position to start (ex: 22 <- to fill pos [2][2]): ");
        scanf("%d" , &message);

        /*char * error_message = (char*)"";
        if(!game->set_position(message, error_message, 'O'))
            printf("ERROR:  %s \n", error_message);*/

        n = write(SocketFD, &message, sizeof(message));
        if (n < 0) perror("ERROR writing to socket");
        
        message_server = read(SocketFD, &buffer, sizeof(buffer));
        if (message_server < 0) perror("ERROR reading from socket");

        /*char * error_messagee = (char*)"";
        if(!game->set_position(buffer, error_messagee, 'X'))
            printf("ERROR:  %s \n", error_messagee);*/

        printf("Message of server: << %d >>\n", buffer);
    }
}