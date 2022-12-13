/*
Carter Theesfeld
C++ Fall 2022
Due December 13,2022
Lab 7: Battleship
Description: use arrays, enums, and structs to simulate battleship.
*/
#include <iostream>
#include <iomanip>
using namespace std;


const int boardSize = 10;
typedef char board[boardSize][boardSize];

struct ship
{
	//to save the starting point of the ship
	int xCord = 0;
	int yCord = 0;
	int cord[2] = {xCord,yCord};
	//initialized before placement
	int size = 0;
	//ship number is for knowing when the ship is destroyed
	int shipNum = 0;
};
struct fleet
{
	ship destroyer;
	ship cruiser;
	ship submarine;
	ship battleship;
	ship carrier;
};

// functions
//These functions are used to create the board and put values into them
void iniBoard(board& uShip, board& uAttack);
void iniBoards(board& Board_);

//creates the fleet and ships
void iniShips(fleet uFleet);
void iniFleet(fleet& fleet_);
//gives the ships a number and size
void iniFleetSize(fleet& fleet_);
void iniFleetNum(fleet& fleet_);

//function that runs to place the users ships
void userPlaceShips(fleet& uFleet, board uShip, board uAttack);

//gets the starting cords for all the ships
void CordsForShip(fleet& uFleet, board uShip, board uAttack);


//outputs the board to the screen
void outputBoard(board Board_);

//checks the point that wants to be placed
bool checkPoint(int& i, board Board_, fleet Fleet_);

//checks the directions the ship can go
void CheckDirections(int i, fleet Fleet_, board Board_);

//Places the rest of the ship in the direction choosen
void chooseDirections(int i, fleet Fleet_, board Board_);

//outputs the screen the user will need
void outputScreen(board uShip, board uAttack);

//asks the user if they want to play again
bool runAgainQuestion();

//outputs the wins and losses after the game
void outputWins_losses(int wins, int losses);

int main()
{
	int wins = 0;
	int losses = 0;
	do
	{
		//board cAttack;
		//board cShip;
		board uShip;
		board uAttack;
		fleet uFleet;
		fleet cFleet;
		iniBoard(uShip, uAttack);
		iniShips(uFleet);
		userPlaceShips(uFleet, uShip, uAttack);
	} while (runAgainQuestion() == true);
	outputWins_losses(wins, losses);
}

void iniBoard(board& uShip, board& uAttack)
{ 
	iniBoards(uAttack);
	iniBoards(uShip);
	//iniBoards(cAttack);
	//iniBoards(cAttack);
}

//fills the board
void iniBoards(board& Board_)
{
	//fills the board with '~'
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			Board_[i][j] = '~';
		}
	}
}

//give the ships sizes and the 1-5 of placing. we will get to it later.
void iniShips(fleet uFleet)
{
	iniFleet(uFleet);
	
}

//gives the ship a size for placement
void iniFleet(fleet& fleet_)
{
	iniFleetSize(fleet_);
	iniFleetNum(fleet_);
}
void iniFleetSize(fleet& fleet_)
{
	fleet_.destroyer.size = 2;
	fleet_.cruiser.size = 3;
	fleet_.submarine.size = 3;
	fleet_.battleship.size = 4;
	fleet_.carrier.size = 5;
}
void iniFleetNum(fleet& fleet_)
{
	fleet_.destroyer.shipNum = '1';
	fleet_.cruiser.shipNum = '2';
	fleet_.submarine.shipNum = '3';
	fleet_.battleship.shipNum = '4';
	fleet_.carrier.shipNum = '5';
}

//places the users ships
void userPlaceShips(fleet& uFleet,board uShip,board uAttack)
{
	CordsForShip(uFleet, uShip, uAttack);
}
void CordsForShip(fleet& uFleet, board uShip, board uAttack)
{
	
	for (int i = 1; i <= 5; i++)// i will be used to know which ship is being placed
	{
		outputScreen(uShip, uAttack);
		int userInput;
		switch (i)
		{
		case 1:
			cout << "The ship we are going to place the destroyer." << endl;
			break;
		case 2:
			cout << "The ship we are going to place the cruiser." << endl;
			break;
		case 3:
			cout << "The ship we are going to place the submarine." << endl;
			break;
		case 4:
			cout << "The ship we are going to place the battleship." << endl;
			break;
		case 5:
			cout << "The ship we are going to place the carrier." << endl;
			break;
		}


		for (int j = 0; j <= 1; j++)
		{
			//gets the x
			if (j == 0)
			{
				cout << "Type in the X Cordinate from 1-10: ";
				cin >> userInput;
				if (userInput < 1 || userInput > 11)
				{

					do
					{
						cout << "\nInput invalid! Please type a number between 1-10" << endl;
						cin >> userInput;

					} while (userInput > 10 || userInput < 1);
				
					switch (i)
					{
					case 1:
						uFleet.destroyer.xCord = userInput - 1;
						break;
					case 2:
						uFleet.cruiser.xCord = userInput - 1;
						break;
					case 3:
						uFleet.submarine.xCord = userInput - 1;
						break;
					case 4:
						uFleet.battleship.xCord = userInput - 1;
						break;
					case 5:
						uFleet.carrier.xCord = userInput - 1;
						break;
					}
				}
				
			}
			//gets the y
			if (j == 1)
			{
				cout << "Type in the Y Cordinate from 1-10: ";
				cin >> userInput;
				if (userInput < 1 || userInput > 10)
				{

					do
					{
						cout << "\nInput invalid! Please type a number between 1-10" << endl;
						cin >> userInput;

					} while (userInput > 10 || userInput < 1);
				}
				switch (i)
				{
				case 1:
					uFleet.destroyer.yCord = userInput-1;
					break;
				case 2:
					uFleet.cruiser.yCord = userInput-1;
					break;
				case 3:
					uFleet.submarine.yCord = userInput-1;
					break;
				case 4:
					uFleet.battleship.yCord = userInput-1;
					break;
				case 5:
					uFleet.carrier.yCord = userInput-1;
					break;
				}
			}
		}
		bool valid = checkPoint(i, uShip, uFleet);
		if (valid == true)
		{
			CheckDirections(i, uFleet, uShip);
		}
	}
}
void outputScreen(board uShip, board uAttack)
{
	outputBoard(uShip);
	cout << endl << endl;
	outputBoard(uAttack);
}
bool runAgainQuestion()
{
	char answer;
	cout << "Would you like to play again? type 1 for yes or anything else for no. ";
	cin >> answer;
	if (answer == '1')
		return true;
	else
		return false;
}
void outputWins_losses(int wins, int losses)
{
	cout << "The total wins are " << wins << " the total losses are " << losses;
	cout << ".\nThank you for playing!";
}
void outputBoard(board Board_)
{
	cout << " X 1 2 3 4 5 6 7 8 9 10" << endl;
	for (int a = 0; a < boardSize; a++)
	{
		cout << setw(2) << a + 1 << " ";
		for (int b = 0; b < boardSize; b++)
		{
			if (Board_[a][b] == !'~')
			{
				cout << '#' << " ";
			}
			else
			{
				cout << Board_[a][b] << " ";
			}
		}
		cout << endl;
	}
}
bool checkPoint(int& i, board Board_, fleet Fleet_)
{
	bool validity=true;
	
	switch (i)
	{
	case 1:
		if (Board_[Fleet_.destroyer.xCord][Fleet_.destroyer.yCord] =!'~')
			validity = false;
		else
			validity = true;
		
		break;
	case 2:
		if (Board_[Fleet_.submarine.xCord][Fleet_.submarine.yCord] =!'~')
			validity = false;
		else
			validity = true;
		
		break;
	case 3:
		if (Board_[Fleet_.cruiser.xCord][Fleet_.cruiser.yCord] =!'~')
			validity = false;
		else
			validity = true;
		
		break;
	case 4:
		if (Board_[Fleet_.battleship.xCord][Fleet_.battleship.yCord] =!'~')
			validity = false;
		else
			validity = true;
		
		break;
	case 5:
		if (Board_[Fleet_.carrier.xCord][Fleet_.carrier.yCord] =!'~')
			validity = false;
		else
			validity = true;
		
		break;

	}
	return validity;
}
void CheckDirections(int i, fleet Fleet_,board Board_)
{
	bool up = true;
	bool down = true;
	bool right = true;
	bool left = true;

	switch (i)
	{
		
		//destroyer directions
	case 1:
		Board_[Fleet_.destroyer.xCord][Fleet_.destroyer.yCord] = Fleet_.destroyer.shipNum;
		
		for (int j = 1; j <= Fleet_.destroyer.size - 1; j++)
		{
			
			if (Board_[Fleet_.destroyer.xCord][Fleet_.destroyer.yCord+j] != '~' || Fleet_.destroyer.yCord - j < 0)
			{ 
				up = false;
			}
			if (Board_[Fleet_.destroyer.xCord][Fleet_.destroyer.yCord - j] != '~' || Fleet_.destroyer.yCord + j > 9)
			{
				down = false;
			}
			if (Board_[Fleet_.destroyer.xCord + j][Fleet_.destroyer.yCord] != '~' || Fleet_.destroyer.xCord + j > 9)
			{
				right = false;
			}
			if (Board_[Fleet_.destroyer.xCord - j][Fleet_.destroyer.yCord] != '~' || Fleet_.destroyer.xCord - j > 0)
			{
				left = false;
			}
		}


		cout << "Please choose a direction from the following. \n";
		if (up == true)
		{
			cout << "type 0 for up; ";
		}

		if (down == true)
		{
			cout << "type 1 for down; ";
		}
		if (right == true)
		{
			cout << "type 2 for right; ";
		}
		if (left == true)
		{
			cout << "type 3 for left; ";
		}
		cout << ": ";
		break;
		//cruiser directions
	case 2:
		Board_[Fleet_.cruiser.xCord][Fleet_.cruiser.yCord] = Fleet_.cruiser.shipNum;

		for (int j = 1; j <= Fleet_.destroyer.size - 1; j++)
		{

			if (Board_[Fleet_.destroyer.xCord][Fleet_.destroyer.yCord + j] == '~')
			{
				up = false;
			}
		}

		for (int j = 1; j <= Fleet_.cruiser.size - 1; j++)
		{

			if (Board_[Fleet_.cruiser.xCord][Fleet_.cruiser.yCord - j] == '~')
			{
				down = false;
			}
		}


		for (int j = 1; j <= Fleet_.cruiser.size - 1; j++)
		{

			if (Board_[Fleet_.cruiser.xCord + j][Fleet_.cruiser.yCord] == '~')
			{
				right = false;
			}
		}


		for (int j = 1; j <= Fleet_.cruiser.size - 1; j++)
		{

			if (Board_[Fleet_.cruiser.xCord - j][Fleet_.cruiser.yCord] == '~')
			{
				left = false;
			}
		}

		cout << "Please choose a direction from the following. \n";
		if (up == true)
		{
			cout << "type 0 for up ";
		}

		if (down == true)
		{
			cout << "type 1 for down ";
		}
		if (right == true)
		{
			cout << "type 2 for right ";
		}
		if (left == true)
		{
			cout << "type 3 for left ";
		}
		cout << ": ";
		break;
		//submarine directions
	case 3:
		Board_[Fleet_.submarine.xCord][Fleet_.submarine.yCord] = Fleet_.submarine.shipNum;

		for (int j = 1; j <= Fleet_.submarine.size - 1; j++)
		{

			if (Board_[Fleet_.submarine.xCord][Fleet_.submarine.yCord + j] == '~')
			{
				up = false;
			}
		}

		for (int j = 1; j <= Fleet_.submarine.size - 1; j++)
		{

			if (Board_[Fleet_.submarine.xCord][Fleet_.submarine.yCord - j] == '~')
			{
				down = false;
			}
		}

		for (int j = 1; j <= Fleet_.submarine.size - 1; j++)
		{

			if (Board_[Fleet_.submarine.xCord + j][Fleet_.submarine.yCord] =='~')
			{
				right = false;
			}
		}

		for (int j = 1; j <= Fleet_.submarine.size - 1; j++)
		{

			if (Board_[Fleet_.submarine.xCord - j][Fleet_.submarine.yCord] == '~')
			{
				left = false;
			}
		}

		cout << "Please choose a direction from the following. \n";
		if (up == true)
		{
			cout << "type 0 for up; ";
		}

		if (down == true)
		{
			cout << "type 1 for down; ";
		}
		if (right == true)
		{
			cout << "type 2 for right; ";
		}
		if (left == true)
		{
			cout << "type 3 for left; ";
		}
		cout << ": ";
		break;
		//battleship directions
	case 4:
		Board_[Fleet_.battleship.xCord][Fleet_.battleship.yCord] = '4';

		for (int j = 1; j <= Fleet_.battleship.size - 1; j++)
		{

			if (Board_[Fleet_.battleship.xCord][Fleet_.battleship.yCord + j] == '~')
			{
				up = false;
			}
		}

		for (int j = 1; j <= Fleet_.battleship.size - 1; j++)
		{

			if (Board_[Fleet_.battleship.xCord][Fleet_.battleship.yCord - j] == '~')
			{
				down = false;
			}
		}

		for (int j = 1; j <= Fleet_.battleship.size - 1; j++)
		{

			if (Board_[Fleet_.battleship.xCord + j][Fleet_.battleship.yCord] == '~')
			{
				right = false;
			}
		}

		for (int j = 1; j <= Fleet_.battleship.size - 1; j++)
		{

			if (Board_[Fleet_.battleship.xCord - j][Fleet_.battleship.yCord] == '~')
			{
				left = false;
			}
		}

		cout << "Please choose a direction from the following. \n";
		if (up == true)
		{
			cout << "type 0 for up; ";
		}

		if (down == true)
		{
			cout << "type 1 for down; ";
		}
		if (right == true)
		{
			cout << "type 2 for right; ";
		}
		if (left == true)
		{
			cout << "type 3 for left; ";
		}
		cout << ": ";
		break;
		//carrier dicrections
	case 5:
		Board_[Fleet_.carrier.xCord][Fleet_.carrier.yCord] = '5';

		for (int j = 1; j <= Fleet_.carrier.size - 1; j++)
		{
			if (Board_[Fleet_.carrier.xCord][Fleet_.carrier.yCord + j] == '~')
			{
				up = false;
			}
		}

		for (int j = 1; j <= Fleet_.carrier.size - 1; j++)
		{

			if (Board_[Fleet_.carrier.xCord][Fleet_.carrier.yCord - j] == '~')
			{
				down = false;
			}
		}

		for (int j = 1; j <= Fleet_.carrier.size - 1; j++)
		{

			if (Board_[Fleet_.carrier.xCord + j][Fleet_.carrier.yCord] == '~')
			{
				right = false;
			}
		}

		for (int j = 1; j <= Fleet_.carrier.size - 1; j++)
		{

			if (Board_[Fleet_.carrier.xCord - j][Fleet_.carrier.yCord] == '~')
			{
				left = false;
			}
		}

		cout << "Please choose a direction from the following. \n";
		if (up == true)
		{
			cout << "type 0 for up; ";
		}

		if (down == true)
		{
			cout << "type 1 for down; ";
		}
		if (right == true)
		{
			cout << "type 2 for right; ";
		}
		if (left == true)
		{
			cout << "type 3 for left; ";
		}
		cout << ": ";
		break;
	}
	chooseDirections(i, Fleet_, Board_);
}
void chooseDirections(int i,fleet Fleet_,board Board_)
{
	int dir;
	cin >> dir;
	switch (i)
	{
		//destroyer
	case 1:
		switch (dir)
		{
		case 0:
			for (int j = 0; j < Fleet_.destroyer.size-1 ; j++)
			{
				Board_[Fleet_.destroyer.xCord][Fleet_.destroyer.yCord+j] = Fleet_.destroyer.shipNum;
			}
			break;
		case 1:
			for (int j = 0; j < Fleet_.destroyer.size-1; j++)
			{
				Board_[Fleet_.destroyer.xCord][Fleet_.destroyer.yCord-j] = Fleet_.destroyer.shipNum;
			}
			break;
		case 2:
			for (int j = 0; j < Fleet_.destroyer.size-1; j++)
			{
				Board_[Fleet_.destroyer.xCord+j][Fleet_.destroyer.yCord] = Fleet_.destroyer.shipNum;
			}
			break;
		case 3:
			for (int j = 0; j < Fleet_.destroyer.size-1; j++)
			{
				Board_[Fleet_.destroyer.xCord-j][Fleet_.destroyer.yCord] = Fleet_.destroyer.shipNum;
			}
			break;
		}
		//cruiser
	case 2:
		switch (dir)
		{
		case 0:
			for (int j = 0; j < Fleet_.cruiser.size - 1; j++)
			{
				Board_[Fleet_.cruiser.xCord][Fleet_.cruiser.yCord + j] = Fleet_.cruiser.shipNum;
			}
			break;
		case 1:
			for (int j = 0; j < Fleet_.cruiser.size - 1; j++)
			{
				Board_[Fleet_.cruiser.xCord][Fleet_.cruiser.yCord - j] = Fleet_.cruiser.shipNum;
			}
			break;
		case 2:
			for (int j = 0; j < Fleet_.cruiser.size - 1; j++)
			{
				Board_[Fleet_.cruiser.xCord + j][Fleet_.cruiser.yCord] = Fleet_.cruiser.shipNum;
			}
			break;
		case 3:
			for (int j = 0; j < Fleet_.cruiser.size - 1; j++)
			{
				Board_[Fleet_.cruiser.xCord - j][Fleet_.cruiser.yCord] = Fleet_.cruiser.shipNum;
			}
			break;
		}
		break;
		//submarine
	case 3:
		switch (dir)
		{
		case 0:
			for (int j = 0; j < Fleet_.submarine.size - 1; j++)
			{
				Board_[Fleet_.submarine.xCord][Fleet_.submarine.yCord + j] = Fleet_.submarine.shipNum;
			}
			break;
		case 1:
			for (int j = 0; j < Fleet_.submarine.size - 1; j++)
			{
				Board_[Fleet_.submarine.xCord][Fleet_.submarine.yCord - j] = Fleet_.submarine.shipNum;
			}
			break;
		case 2:
			for (int j = 0; j < Fleet_.submarine.size - 1; j++)
			{
				Board_[Fleet_.submarine.xCord + j][Fleet_.submarine.yCord] = Fleet_.submarine.shipNum;
			}
			break;
		case 3:
			for (int j = 0; j < Fleet_.submarine.size - 1; j++)
			{
				Board_[Fleet_.submarine.xCord - j][Fleet_.submarine.yCord] = Fleet_.submarine.shipNum;
			}
			break;
		}
		break;
		//battleship
	case 4:
		switch (dir)
		{
		case 0:
			for (int j = 0; j < Fleet_.battleship.size - 1; j++)
			{
				Board_[Fleet_.battleship.xCord][Fleet_.battleship.yCord + j] = Fleet_.battleship.shipNum;
			}
			break;
		case 1:
			for (int j = 0; j < Fleet_.battleship.size - 1; j++)
			{
				Board_[Fleet_.battleship.xCord][Fleet_.battleship.yCord - j] = Fleet_.battleship.shipNum;
			}
			break;
		case 2:
			for (int j = 0; j < Fleet_.battleship.size - 1; j++)
			{
				Board_[Fleet_.battleship.xCord + j][Fleet_.battleship.yCord] = Fleet_.battleship.shipNum;
			}
			break;
		case 3:
			for (int j = 0; j < Fleet_.battleship.size - 1; j++)
			{
				Board_[Fleet_.battleship.xCord - j][Fleet_.battleship.yCord] = Fleet_.battleship.shipNum;
			}
			break;
		}
		break;
		//carrier
	case 5:
		switch (dir)
		{
		case 0:
			for (int j = 0; j < Fleet_.carrier.size - 1; j++)
			{
				Board_[Fleet_.carrier.xCord][Fleet_.carrier.yCord + j] = Fleet_.carrier.shipNum;
			}
			break;
		case 1:
			for (int j = 0; j < Fleet_.carrier.size - 1; j++)
			{
				Board_[Fleet_.carrier.xCord][Fleet_.carrier.yCord - j] = Fleet_.carrier.shipNum;
			}
			break;
		case 2:
			for (int j = 0; j < Fleet_.carrier.size - 1; j++)
			{
				Board_[Fleet_.carrier.xCord + j][Fleet_.carrier.yCord] = Fleet_.carrier.shipNum;
			}
			break;
		case 3:
			for (int j = 0; j < Fleet_.carrier.size - 1; j++)
			{
				Board_[Fleet_.carrier.xCord - j][Fleet_.carrier.yCord] = Fleet_.carrier.shipNum;
			}
			break;
		}
		break;
	}
	
}
