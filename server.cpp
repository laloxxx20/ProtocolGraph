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


class Server {
    public:
        struct sockaddr_in stSockAddr;
        int SocketFD;
        int port;
        int buffer;
        int message;
        int n;

        int packet_size;
        int header_size;

        Server();
        // port, header_size, packet_size,
        Server(int, int, int);
};

Server::Server(){}

Server::Server(int port, int header_size , int packet_size){
    this->SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    this->port = port;
    this->packet_size = packet_size;
    this->header_size = header_size;

}