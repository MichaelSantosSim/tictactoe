#include <stdio.h>
#include <string.h>
#include <iostream>
#include <windows.h>

#define PLAYER_1 'X'
#define PLAYER_2 'O'
#define EMPTY_SPACE ' '


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

using namespace std;



typedef struct{
	int gameOver;
	char board[3][3];
	char currentPlayer;
} Game;

void prepareGame(Game* game){

	game->gameOver = 0;

	game -> currentPlayer = PLAYER_1;

	for(int i = 0; i < 3;i++){
		for(int j=0; j < 3; j++){
			game->board[i][j] = EMPTY_SPACE;
		}
	}

}

std::string getColoredString(std::string text){
	return "\033[1;31m" + text + "\033[0m";
}

std::string printPlayer(char player){
	if(player == PLAYER_1){
		return "\033[1;32mX\033[0m";
	}else if(player == PLAYER_2){
		return "\033[1;34mO\033[0m";
	}else{
		return " ";
	}
}

void printGame(Game game){
	system("clear");
	if(game.gameOver){
		std::cout << endl << "\tWinner: " << game.currentPlayer << std::endl;
	}else{
		std::cout << endl << getColoredString("\tCurrent Player: ") << game.currentPlayer<< std::endl;
	}
	std::cout << std::endl;
	
	std::cout << getColoredString("\t+---+---+---+---+") << std::endl;
	std::cout << getColoredString("\t|   | 1 | 2 | 3 |") << std::endl;
	std::cout << getColoredString("\t+---+---+---+---+") << std::endl;


	for(int i = 0; i < 3;i++){
		std::cout << getColoredString("\t| " + std::to_string(i+1) + " |");
		for(int j=0; j<3; j++){
			std::cout << " " << printPlayer(game.board[i][j]) << " |";
		}
		std::cout << std::endl;
		std::cout << getColoredString("\t+---+") << "---+---+---+" << std::endl;
	}
	std::cout << std::endl;
}

int validateCoordinates(char board[3][3], int x, int y){
	//validar jogada
	if(x >= 0 && x < 3 && y >= 0 && y < 3){
		if(board[x][y] == EMPTY_SPACE){
			return 1;
		}
	}

	return 0;
}

void calculateWinner(Game* game){
	// calcularvencedor
	int winner[8][3][2] =  {
								// HORIZONTAL
							 	{{0,0},{0,1},{0,2}},
							 	{{1,0},{1,1},{1,2}},
							 	{{2,0},{2,1},{2,2}},
							 	// VERTICAL
							 	{{0,0},{1,0},{2,0}},
							 	{{0,1},{1,1},{2,1}},
							 	{{0,2},{1,2},{2,2}},
							 	// DIAGONAL
							 	{{0,0},{1,1},{2,2}},
							 	{{2,0},{1,1},{0,2}}
							};
	
	for(int i = 0; i < 8; i++){

		for(int j = 0; j < 3; j++){
			int x = winner[i][j][0];
			int y = winner[i][j][1];
			int ok = (game->board[x][y] == game->currentPlayer);

			if(ok && j == 2){
				game->gameOver = 1;
				return;
			}else if(!ok){
				break;
			}

		}
		
	}
}

void runGame(Game* game){
	printGame(*game);
	while(!game->gameOver){
		int x, y;
		std::cout << "\tInput X coordinate: ";
		std::cin >> x;
		std::cout << "\tInput Y coordinate: ";
		std::cin >> y;
		x--; y--;

		int isValid = validateCoordinates((*game).board, x, y);

		if(isValid){
			game->board[x][y] = game->currentPlayer;
			calculateWinner(game);
			if(!game->gameOver){
				game->currentPlayer = game->currentPlayer == PLAYER_1 ? PLAYER_2 : PLAYER_1;
			}
			printGame(*game);
		}else{
			std::cout << "\t" << x << " and " << y << " are invalid coordinates" << std::endl << std::endl;
		}
	}

}

int main (){
   Game game;
   prepareGame(&game);
   runGame(&game);
   
   return 0;
}
