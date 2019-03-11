
#include <iostream>
#include <stdlib.h>
using namespace std;

char square[10] = {'o','1','2','3','4','5','6','7','8','9'}; // used to number the board for choosing the squares

int checkWin();
void board();

int main()
{
	int i, choice = 0, mode, player = 1;
	char mark;
	cout<<"0 for player vs player, 1 for player vs ai" << endl;
	cin >> mode;
	if(mode == 0)
 	{
	do
	{
		board(); //shows the board
		player=(player%2)?1:2; // keeps track of the player
		cout << "Player " << player << ", enter a number:  ";
		cin >> choice;
		mark=(player == 1) ? 'X' : 'O'; // this is so turns are being taken, x, o, x, o, etc.
		if (choice == 1 && square[1] == '1') // each of these if statements are to check if the position of the board is occupied or not. if it isn't, it's an invalid move.
			square[1] = mark;
		else if (choice == 2 && square[2] == '2')
			square[2] = mark;
		else if (choice == 3 && square[3] == '3')
			square[3] = mark;
		else if (choice == 4 && square[4] == '4')
			square[4] = mark;
		else if (choice == 5 && square[5] == '5')
			square[5] = mark;
		else if (choice == 6 && square[6] == '6')
			square[6] = mark;
		else if (choice == 7 && square[7] == '7')
			square[7] = mark;
		else if (choice == 8 && square[8] == '8')
			square[8] = mark;
		else if (choice == 9 && square[9] == '9')
			square[9] = mark;
		else
		{
			cout<<"Can't move here.";
			player--; // this is so the turn is still for the same person if he makes an invalid move.
		}
		i=checkWin();
		player++;
	}while(i==-1);


	board(); //shows board again.
	if(i==1)

		cout<<"Player "<<--player<<" win ";
	else
		cout<<"Game draw";
	}

	if(mode == 1)
	{
		do
		{
			board(); //shows the board
			player=(player%2)?1:2; // keeps track of the player
			cout << "Player 1" << ", enter a number:  ";
			if(player = 1)
				{cin >> choice;}

			else if(player = 2)
				{
					choice = rand()%10+1;
				} //number btwn 1 - 10

			mark=(player == 1) ? 'X' : 'O'; // this is so turns are being taken, x, o, x, o, etc.
			if (choice == 1 && square[1] == '1') // each of these if statements are to check if the position of the board is occupied or not. if it isn't, it's an invalid move.
				square[1] = mark;
			else if (choice == 2 && square[2] == '2')
				square[2] = mark;
			else if (choice == 3 && square[3] == '3')
				square[3] = mark;
			else if (choice == 4 && square[4] == '4')
				square[4] = mark;
			else if (choice == 5 && square[5] == '5')
				square[5] = mark;
			else if (choice == 6 && square[6] == '6')
				square[6] = mark;
			else if (choice == 7 && square[7] == '7')
				square[7] = mark;
			else if (choice == 8 && square[8] == '8')
				square[8] = mark;
			else if (choice == 9 && square[9] == '9')
				square[9] = mark;
			else
			{
				cout<<"Can't move here.";
				player--; // this is so the turn is still for the same person if he makes an invalid move.
			}
			i=checkWin();
			player++;
		}while(i==-1);


		board(); //shows board again.
		if(i==1)

			cout<<"Player "<<--player<<" win ";
		else
			cout<<"Game draw";
	}

	return 0;
}

//this function returns an integer depending on the status of the game. 1 is for win, -1 is to keep the loop running, meaning the game is still going on, 0 is for stalemate/tie.
int checkWin()
{
	if (square[1] == square[2] && square[2] == square[3])  //these if statements are to check all possible ways of winning, vertical, horizontal, or diagonal.
		return 1;
	else if (square[4] == square[5] && square[5] == square[6])
		return 1;
	else if (square[7] == square[8] && square[8] == square[9])
		return 1;
	else if (square[1] == square[4] && square[4] == square[7])
		return 1;
	else if (square[2] == square[5] && square[5] == square[8])
		return 1;
	else if (square[3] == square[6] && square[6] == square[9])
		return 1;
	else if (square[1] == square[5] && square[5] == square[9])
		return 1;
	else if (square[3] == square[5] && square[5] == square[7])
		return 1;
	else if (square[1] != '1' && square[2] != '2' && square[3] != '3'&& square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7] != '7' && square[8] != '8' && square[9] != '9')
		return 0;
	else
		return -1;
}


// draws the board using a series of couts.
void board()
{
	cout << "\n\n\tTic Tac Toe\n\n";
	cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;
	cout << endl;
	cout << "     |     |     " << endl;
	cout << "  " << square[1] << "  |  " << square[2] << "  |  " << square[3] << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << square[4] << "  |  " << square[5] << "  |  " << square[6] << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << square[7] << "  |  " << square[8] << "  |  " << square[9] << endl;
	cout << "     |     |     " << endl << endl;
}
