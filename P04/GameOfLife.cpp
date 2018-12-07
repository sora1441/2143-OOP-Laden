/*
P04
Purpose: Create your own game of life class and game board to play
John Conway's Game of Life.
Brent Laden
10/19/18
github: sora1441
*/

#include <iostream>
#include <fstream>
#include <string> 
#include <SFML/Graphics.hpp> 

using namespace std;

//My game of life cell
struct golCell
{
	bool isAlive; //keep an alive or dead value
	int neighborCount; //counts the alives cell beside an individual cell

//The shape and size for the automation
	sf::RectangleShape rect;
	int width;
	int height;


	// Default constuctor for golCell
	golCell()
	{
		isAlive = 0;
		neighborCount = 0;
		width = 10;
		height = 10;

		//sets color from SFML library
		rect.setSize(sf::Vector2f(width, height));
		rect.setFillColor(sf::Color::Cyan);
		rect.setOutlineColor(sf::Color::Yellow);
		rect.setOutlineThickness(1);
	}

	//Determines the place of the cell on the worls
	void setCellPos(int x, int y)
	{
		rect.setPosition(x*width, y*height);
	}
};

class GameOfLife
{
private:
	int frameRate;
	int frameCount;
	int rows;
	int cols;
	int width;
	int height;
	golCell** gameBoard;

public:

	//SFML window to print the world and game board
	sf::RenderWindow window;

	golCell **world;

	// Parameterized constuctor for GameOfLife
	GameOfLife(int w, int h)
	{

		frameCount = 0;
		frameRate = 5;
		rows = 0;
		cols = 0;
		width = w;
		height = h;

		//Creates window
		window.create(sf::VideoMode(width, height), "Game of Life");

		//Sets the world 
		world = new golCell*[width];

		for (int i = 0; i < width; i++)
		{
			world[i] = new golCell[height];

			for (int j = 0; j < width; j++)
				world[i][j].setCellPos(i, j);
		}

	}

	//Reads the infile and places values into cell
	void initGameBoard(string &input)
	{
		//opens infile
		ifstream infile;
		infile.open(input);

		string line;
		string name;

		infile >> name;
		infile >> rows >> cols;
		gameBoard = new golCell*[rows];

		for (int i = 0; i < rows; i++)
			gameBoard[i] = new golCell[cols];

		//Places alive and death values into game board
		for (int i = 0; i < rows; i++)
		{
			infile >> line;

			for (int j = 0; j < cols; j++)
			{
				gameBoard[i][j].isAlive = line[j] - 48;
				gameBoard[i][j].neighborCount = 0;
			}
		}
		infile.close();
	}

	// Opens SFML window and set colors for cells
	void displayWorld()
	{
		window.clear();

		//Flips height and width for SFML
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
				window.draw(world[i][j].rect);
		}

		//Flips cols and rows for SFML
		for (int i = 0; i < cols; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				//Displays alive cells
				if (gameBoard[j][i].isAlive == true)
				{
					world[i][j].rect.setFillColor(sf::Color::Red);
					world[i][j].rect.setOutlineColor(sf::Color::Black);
				}
				else
				{
					world[i][j].rect.setFillColor(sf::Color::Cyan);
					world[i][j].rect.setOutlineColor(sf::Color::Black);
				}
			}
		}

		window.display();
	}


	// Determines if cell is on game board

	bool onGameBoard(int r, int c)
	{
		return (r >= 0 && r < rows && c >= 0 && c < cols);
	}

	// Counts the alive cells around a cell
	int countNeighbors(int r, int c)
	{
		int count = 0;

		//Counts whenever a nearby cell is alive
		if (onGameBoard(r - 1, c - 1) == true && gameBoard[r - 1][c - 1].isAlive == true)
			count++;
		if (onGameBoard(r, c - 1) == true && gameBoard[r][c - 1].isAlive == true)
			count++;
		if (onGameBoard(r - 1, c) == true && gameBoard[r - 1][c].isAlive == true)
			count++;
		if (onGameBoard(r + 1, c + 1) == true && gameBoard[r + 1][c + 1].isAlive == true)
			count++;
		if (onGameBoard(r + 1, c) == true && gameBoard[r + 1][c].isAlive == true)
			count++;
		if (onGameBoard(r, c + 1) == true && gameBoard[r][c + 1].isAlive == true)
			count++;
		if (onGameBoard(r - 1, c + 1) == true && gameBoard[r - 1][c + 1].isAlive == true)
			count++;
		if (onGameBoard(r + 1, c - 1) == true && gameBoard[r + 1][c - 1].isAlive == true)
			count++;
		return count;
	}


	// Puts number of alive cells into all the cells
	void neighborCells()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
				gameBoard[i][j].neighborCount = countNeighbors(i, j);
		}
	}


	// Applies rules for Game of Life to cell
	void Rules(int r, int c)
	{
		if (gameBoard[r][c].isAlive == true)
		{
			if (gameBoard[r][c].neighborCount < 2 || gameBoard[r][c].neighborCount > 3)
				gameBoard[r][c].isAlive = false;
			else if (gameBoard[r][c].neighborCount == 2 || gameBoard[r][c].neighborCount == 3)
				gameBoard[r][c].isAlive = true;
		}
		else
		{
			if (gameBoard[r][c].neighborCount == 3)
				gameBoard[r][c].isAlive = true;
		}
	}

	// Determines the frame rate
	int theFrameRate()
	{
		frameCount++;
		if (frameCount % frameRate == 0)
			return 0;
		return 1;
	}

	// Makes new generation of cells
	void nextGen()
	{
		neighborCells();

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				Rules(i, j);
				gameBoard[i][j].neighborCount = 0;
			}
		}
	}

	// Prints a header to outfile
	void outfileHeader(ofstream &outfile)
	{
		outfile << "Brent Laden" << endl;
		outfile << "P04 - Game of Life" << endl;
		outfile << "10/20/18" << endl << endl;
	}
	//	Prints game board to the outfile
	void printGameBoard(string &output)
	{
		//Opens outfile
		ofstream outfile;
		outfile.open(output);

		outfileHeader(outfile);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
				outfile << gameBoard[i][j].isAlive;

			outfile << endl;
		}

		//Closes outfile
		outfile.close();
	}

	// Runs the world and game board with SFML
	void run(int gens)
	{
		int runTimes = 0;

		//Runs simulation
		while (window.isOpen())
		{
			sf::Event event;

			frameCount++;

			//Displays world to screen
			displayWorld();
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			nextGen();
			runTimes++;

			if (runTimes == gens)
				break;
		}
	}

};


	//Calls functions to play the Game of Life
	int main(int argc, char** argv)
	{
		string input = argv[1];
		string output = argv[3];
		string gens = argv[2];
		GameOfLife G(600, 600);
		G.initGameBoard(input);
		G.run(340);
		G.printGameBoard(output);

		return 0;
	}