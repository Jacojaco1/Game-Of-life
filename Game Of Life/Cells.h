#pragma once
#include <SFML\Graphics.hpp>

class Cells
{
public:
	Cells(int nbrCells, sf::Vector2i cellDimensions);
	~Cells();

	void draw(sf::RenderWindow& window, int nbrCells, sf::Vector2i cellDimensions);
	void setTheCells(int theCells[80 * 80]);
	bool isAlive(int i, int j);
	void killCell(int i, int j);
	void reviveCell(int i, int j);
	void update();

private:
	int nbrCells;
	int theCells[80 * 80];
	sf::Vector2i cellDimensions;
};

