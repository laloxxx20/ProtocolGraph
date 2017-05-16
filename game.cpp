#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


class Game
{
    public:
        char** board;
        char** options_to_win;
        int* current_x;
        int* current_y;
        char chip;
        char chip_m;
        int board_dimention;

        Game();
        Game(int);
        void draw_board();
        void transform_num_to_coord(int);
        void message_to_start();
        bool get_posision(int, char const *);
        bool set_position(int, char*, char);
};

Game::Game(){}

Game::Game(int board_dimention){
    this->board_dimention = board_dimention;
    board =  new char*[this->board_dimention];
    for(int i=0; i<this->board_dimention; i++)
        board[i] = new char[this->board_dimention];

    for(int i=0; i<this->board_dimention; i++)
    {
        for(int j=0; j<this->board_dimention; j++)
            board[i][j]='_';
    }

    chip_m = '*';
}

/*char board[3][3] = {{'_', '_', '_'},
                    {'_', '_', '_'},
                    {'_', '_', '_'}};

int options_to_win[8][3] = {{00, 01, 02},
                            {10, 11, 12},
                            {20, 21, 22},
                            {00, 10, 20},
                            {01, 11, 21},
                            {02, 12, 22},
                            {00, 11, 22},
                            {20, 11, 02}};*/


void Game::draw_board()
{
    printf("   ");
    for(int i=0; i<this->board_dimention; i++)
        printf("%d ", i);
    printf("\n");

    for(int i=0; i<this->board_dimention; i++){
        printf("%d| ", i);
        for(int j=0; j<this->board_dimention; j++){
            printf("%c ", this->board[i][j]);
        }
        printf("\n");
    }
}

void Game::transform_num_to_coord(int num){
    *this->current_x = num / 10;
    *this->current_y = num % 10;
}

void Game::message_to_start(){
    printf("\n Your sign to play is : %c \n", chip);
    printf("Introduce a position to start (ex: 22 <- to fill pos [2][2]): ");
}

bool Game::get_posision(int pos, char const * message){
    if(pos>22)
    {
        message = "You need a position beetween 0-0 and 2-2(00 - 22)";
        return 0;
    }
    transform_num_to_coord(pos);
    printf("transform_num_to_coord: %i - %i\n", *this->current_x, *this->current_y);
    chip_m = board[*this->current_x][*this->current_y];
    printf("element: %c\n", chip_m);
    return true;
}

bool Game::set_position(int pos, char* message, char chip_contrary){
    if(get_posision(pos, message))
    {
        printf("set_position: %i - %i\n", *this->current_x, *this->current_y);
        printf("element: %c \n", chip_m);
        if(chip_m == '_'){
            board[*this->current_x][*this->current_x] = chip_contrary;
            printf("%c\n", board[*this->current_x][*this->current_x]);
            printf("printing board \n");
            draw_board();
            return true;
        }
        return false;
    }
}