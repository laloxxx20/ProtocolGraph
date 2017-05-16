/*#include "game.cpp"*/
#include "client.cpp"
#include "server.cpp"

int main(int argc, char const *argv[])
{
    /*Game* a = new Game(10);
    a->draw_board();*/
    //Client* c = new Client("192.168.162.131", 1100, 4, 1000, 10);
    Server* s = new Server(1100, 4 , 1000);

    return 0;
}