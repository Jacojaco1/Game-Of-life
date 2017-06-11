#include <SFML\Graphics.hpp>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "Cells.h"
#include <windows.h>

/*===================================================================================================
Game of Life simulation
Here are the rules :
1) Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
2) Any live cell with two or three live neighbours lives on to the next generation.
3) Any live cell with more than three live neighbours dies, as if by overpopulation.
4) Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

Press P to pause the simulation, and create new cells with left mouse clicks when game is paused.

Author : Jacobus Algera
=====================================================================================================
*/
const sf::Vector2i screenDimension(800, 800);
const sf::Vector2i cellDimensions(10, 10);
const int nbrCells = screenDimension.y / cellDimensions.y;
const int delay = 100; //To set the speed of each cycle

void initializeGrid(sf::RenderWindow& window, sf::Color color) {
	for (int i = 0; i < nbrCells; i++)
	{
		for (int j = 0; j < nbrCells; j++)
		{
			sf::VertexArray cell(sf::PrimitiveType::Quads, 4);

			cell[0].position = sf::Vector2f(j*cellDimensions.x + j + 1, i*cellDimensions.y + i + 1);
			cell[1].position = sf::Vector2f(j*cellDimensions.x + cellDimensions.x + j + 1, i*cellDimensions.y + i + 1);
			cell[2].position = sf::Vector2f(j*cellDimensions.x + cellDimensions.x + j + 1, i*cellDimensions.y + cellDimensions.y + i + 1);
			cell[3].position = sf::Vector2f(j*cellDimensions.x + j + 1, i*cellDimensions.y + cellDimensions.y  + i + 1);

			cell[0].color = color;
			cell[1].color = color;
			cell[2].color = color;
			cell[3].color = color;

			window.draw(cell);
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(screenDimension.x + screenDimension.x/cellDimensions.x + 1, screenDimension.y + screenDimension.y/cellDimensions.y + 1), "The Game of Life - Paused", sf::Style::Close | sf::Style::Titlebar); // creates the screen we work on
	
	Cells theCells(nbrCells, cellDimensions);
	printf(
		"Game of Life simulation\nHere are the rules :\n1) Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.\n2) Any live cell with two or three live neighbours lives on to the next generation.\n3) Any live cell with more than three live neighbours dies, as if by overpopulation.\n4) Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.\n\nPress P to pause the simulation, and create new cells with left mouse clicks when game is paused.\n\nAuthor : Jacobus Algera");

	int cells[80 * 80] = {
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,1,1,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		1,1,1,1,0,1,1,1,1,0, 1,1,1,1,0,1,0,0,0,1, 0,0,0,0,1,1,1,1,0,1, 1,1,1,0,0,1,1,1,0,1, 0,0,0,1,0,1,1,1,1,0, 0,1,1,1,0,0,1,1,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		1,0,0,1,0,1,0,0,1,0, 1,0,0,0,0,1,1,0,0,1, 0,0,0,0,1,0,0,0,0,1, 0,0,1,0,1,0,0,0,0,1, 1,0,1,1,0,1,0,0,1,0, 1,0,0,0,0,0,1,1,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		1,0,0,1,0,1,1,1,1,0, 1,1,1,1,0,1,0,1,0,1, 0,0,0,0,1,0,0,0,0,1, 0,0,1,0,0,1,1,0,0,1, 0,1,0,1,0,1,0,0,1,0, 0,1,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		1,0,0,1,0,1,0,0,0,0, 1,0,0,0,0,1,0,0,1,1, 0,0,0,0,1,0,0,0,0,1, 0,0,1,0,0,0,0,1,0,1, 0,0,0,1,0,1,0,0,1,0, 0,0,0,1,0,0,1,1,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		1,1,1,1,0,1,0,0,0,0, 1,1,1,1,0,1,0,0,0,1, 0,0,0,0,1,1,1,1,0,1, 1,1,1,0,1,1,1,1,0,1, 0,0,0,1,0,1,1,1,1,0, 1,1,1,1,0,0,1,1,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 
		0,0,0,0,1,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0, 
		0,0,0,1,1,1,0,0,0,0, 0,0,0,1,1,1,0,0,0,0, 0,0,0,1,1,1,0,0,0,0, 0,0,0,1,1,1,0,0,0,0, 0,0,0,1,1,1,0,0,0,0, 0,0,0,1,1,1,0,0,0,0, 0,0,0,1,1,1,0,0,0,0, 0,0,0,1,1,1,0,0,0,0, 
		0,0,0,0,1,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0, };

	theCells.setTheCells(cells);
	bool gamePause = true;

	while (window.isOpen())		//Main loop here
	{
		sf::Event evnt;			//Handles the events given by the user
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))	//Mouse events
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			int nbrJ = mousePos.x / (cellDimensions.x + 1);
			int nbrI = mousePos.y / (cellDimensions.y + 1);
			if (theCells.isAlive(nbrI, nbrJ))
			{
				//theCells.killCell(nbrI, nbrJ);
			}
			else
			{
				theCells.reviveCell(nbrI, nbrJ);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))	//Keyboard events
		{
			
			gamePause = !gamePause;
			if (gamePause)
			{
				window.setTitle("The Game of Life - Paused");
			}
			else
			{
				window.setTitle("The Game of Life");
			}
			Sleep(100);
		}


		if (!gamePause)
		{
			theCells.update();
		}
		theCells.draw(window, nbrCells, cellDimensions);
		window.display();
		window.clear();
		if (!gamePause) {
			Sleep(delay);
		}
	}
}