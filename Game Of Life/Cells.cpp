#include "Cells.h"
/*==============================
Class used to manage the cells
A cell is dead when = 0, and alive when = 1
I am working with a 80x80 grid.
================================*/

void vertexCell(sf::RenderWindow& window, int i, int j, sf::Color color, sf::Vector2i cellDimensions);
void copyArray(int array1[], int array2[]);
bool isAlive(int i, int j, int theCells[]);

//Every cell can't be tested to see how many of it's neighbors are alive in the same way (e.g top-left cell only has 3 potential neighbors, while the cell situated at i=j=1 has 8 potential neighbors), thus I created different tests for each case
void testMid(int i, int j, int theCells[], int tempCells[]); // (i < 79 && j < 79 && i > 0 && j > 0)
void testLeft(int i, int j, int theCells[], int tempCells[]); // (i < 79  && i > 0 && j == 0)
void testTop(int i, int j, int theCells[], int tempCells[]); // (j < 79 && j > 0  && i == 0)
void testRight(int i, int j, int theCells[], int tempCells[]); // (i < 79 && i > 0  && j == 79)
void testBot(int i, int j, int theCells[], int tempCells[]); // (j < 79 && j > 0  && i == 79)
void testTopLeft(int i, int j, int theCells[], int tempCells[]); // (i == 0 && j == 0)
void testTopRight(int i, int j, int theCells[], int tempCells[]); // (i == 0 && j == 79)
void testBotRight(int i, int j, int theCells[], int tempCells[]); // (i == 79 && j == 79)
void testBotLeft(int i, int j, int theCells[], int tempCells[]); // (i == 79 && j == 0)

Cells::Cells(int nbrCells, sf::Vector2i cellDimensions)
{
	for (int i = 0; i < nbrCells; i++)
	{
		for (int j = 0; j < nbrCells; j++)
		{
			theCells[j + i * nbrCells] = 0;
		}
	}
	this->cellDimensions = cellDimensions;
	this->nbrCells = nbrCells;
}


Cells::~Cells()
{
}

void Cells::draw(sf::RenderWindow& window, int nbrCells, sf::Vector2i cellDimensions)
{
	for (int i = 0; i < nbrCells; i++)
	{
		for (int j = 0; j < nbrCells; j++)
		{
			if (theCells[j + i*nbrCells] > 0)
			{
				vertexCell(window, i, j, sf::Color::Blue, cellDimensions);
			}
			else
			{
				vertexCell(window, i, j, sf::Color::White, cellDimensions);
			}
		}
	}
}

void Cells::setTheCells(int theCells[80 * 80])  //Funcion to initialize the cells with a specified array as an input
{
	for (int i = 0; i < nbrCells; i++)
	{
		for (int j = 0; j < nbrCells; j++)
		{
			this->theCells[j + i*nbrCells] = theCells[j + i*nbrCells];
		}
	}
}

bool Cells::isAlive(int i, int j)
{
	if (theCells[j + nbrCells*i] > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Cells::killCell(int i, int j)
{	
	theCells[j + nbrCells*i] = 0;
}

void Cells::reviveCell(int i, int j)
{
	theCells[j + nbrCells*i] = 1;
}

void Cells::update() //Checks every cell to see if it should be killed or revived
{
	int tempCells[80 * 80];
	copyArray(tempCells, theCells);
	for (int i = 0; i < 80; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			if (i < 79 && j < 79 && i > 0 && j > 0)
				testMid(i, j, theCells, tempCells);
			else if (i < 79 && i > 0 && j == 0)
				testLeft(i, j, theCells, tempCells);
			else if (j < 79 && j > 0 && i == 0)
				testTop(i, j, theCells, tempCells);
			else if (i < 79 && i > 0 && j == 79)
				testRight(i, j, theCells, tempCells);
			else if (j < 79 && j > 0 && i == 79)
				testBot(i, j, theCells, tempCells);
			else if (i == 0 && j == 0)
				testTopLeft(i, j, theCells, tempCells);
			else if (i == 0 && j == 79)
				testTopRight(i, j, theCells, tempCells);
			else if (i == 79 && j == 79)
				testBotRight(i, j, theCells, tempCells);
			else if (i == 79 && j == 0)
				testBotLeft(i, j, theCells, tempCells);
		}
	}
	copyArray(theCells, tempCells);
}

void vertexCell(sf::RenderWindow& window, int i, int j, sf::Color color, sf::Vector2i cellDimensions) //Draws each cell, which is created by using vertexes, as it isn't as heavy as creating squares for each cell complexity-wise
{

	sf::VertexArray cell(sf::PrimitiveType::Quads, 4);

	cell[0].position = sf::Vector2f(j*cellDimensions.x + j + 1, i*cellDimensions.y + i + 1);	//Specifying the 4 corners of the cell
	cell[1].position = sf::Vector2f(j*cellDimensions.x + cellDimensions.x + j + 1, i*cellDimensions.y + i + 1);
	cell[2].position = sf::Vector2f(j*cellDimensions.x + cellDimensions.x + j + 1, i*cellDimensions.y + cellDimensions.y + i + 1);
	cell[3].position = sf::Vector2f(j*cellDimensions.x + j + 1, i*cellDimensions.y + cellDimensions.y + i + 1);

	cell[0].color = color;
	cell[1].color = color;
	cell[2].color = color;
	cell[3].color = color;

	window.draw(cell);
}

void copyArray(int array1[], int array2[])
{
	for (int i = 0; i < 80; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			array1[j + i * 80] = (int)array2[j + i * 80];
		}
	}
}
bool isAlive(int i, int j, int theCells[])
{
	if (theCells[j + i * 80] > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void testMid(int i, int j, int theCells[], int tempCells[]) // (i < 79 && j < 79 && i > 0 && j > 0)
{
	int nbrNeighbors = 0;
	if (isAlive(i, j-1, theCells))
		nbrNeighbors ++;
	if (isAlive(i - 1, j - 1, theCells))
		nbrNeighbors++;
	if (isAlive(i-1, j, theCells))
		nbrNeighbors++;
	if (isAlive(i-1, j + 1, theCells))
		nbrNeighbors++;
	if (isAlive(i, j + 1, theCells))
		nbrNeighbors++;
	if (isAlive(i + 1, j + 1, theCells))
		nbrNeighbors++;
	if (isAlive(i+1, j, theCells))
		nbrNeighbors++;
	if (isAlive(i+1, j - 1, theCells))
		nbrNeighbors++;
	if (nbrNeighbors < 2)
		tempCells[j + i * 80] = 0;
	else if (nbrNeighbors > 3)
		tempCells[j + i * 80] = 0;
	else if (nbrNeighbors == 3)
		tempCells[j + i * 80] = 1;
}
void testLeft(int i, int j, int theCells[], int tempCells[]) // (i < 79 && j < 79 && i > 0 && j > 0)
{
	int nbrNeighbors = 0;
	if (isAlive(i - 1, j, theCells))
		nbrNeighbors++;
	if (isAlive(i - 1, j + 1, theCells))
		nbrNeighbors++;
	if (isAlive(i, j + 1, theCells))
		nbrNeighbors++;
	if (isAlive(i + 1, j + 1, theCells))
		nbrNeighbors++;
	if (isAlive(i + 1, j, theCells))
		nbrNeighbors++;
	if (nbrNeighbors < 2)
		tempCells[j + i * 80] = 0;
	else if (nbrNeighbors > 3)
		tempCells[j + i * 80] = 0;
	else if (nbrNeighbors == 3)
		tempCells[j + i * 80] = 1;
}
void testTop(int i, int j, int theCells[], int tempCells[]) // (i < 79 && j < 79 && i > 0 && j > 0)
{
	int nbrNeighbors = 0;
	if (isAlive(i, j - 1, theCells))
		nbrNeighbors++;
	if (isAlive(i + 1, j - 1, theCells))
		nbrNeighbors++;
	if (isAlive(i + 1, j, theCells))
		nbrNeighbors++;
	if (isAlive(i + 1, j + 1, theCells))
		nbrNeighbors++;
	if (isAlive(i, j + 1, theCells))
		nbrNeighbors++;
	if (nbrNeighbors < 2)
		tempCells[j + i * 80] = 0;
	else if (nbrNeighbors > 3)
		tempCells[j + i * 80] = 0;
	else if (nbrNeighbors == 3)
		tempCells[j + i * 80] = 1;
}
void testRight(int i, int j, int theCells[], int tempCells[]) // (i < 79 && j < 79 && i > 0 && j > 0)
{
	int nbrNeighbors = 0;
	if (isAlive(i - 1, j, theCells))
		nbrNeighbors++;
	if (isAlive(i - 1, j - 1, theCells))
		nbrNeighbors++;
	if (isAlive(i, j - 1, theCells))
		nbrNeighbors++;
	if (isAlive(i + 1, j - 1, theCells))
		nbrNeighbors++;
	if (isAlive(i + 1, j, theCells))
		nbrNeighbors++;
	if (nbrNeighbors < 2)
		tempCells[j + i * 80] = 0;
	else if (nbrNeighbors > 3)
		tempCells[j + i * 80] = 0;
	else if (nbrNeighbors == 3)
		tempCells[j + i * 80] = 1;
}
void testBot(int i, int j, int theCells[], int tempCells[]) // (i < 79 && j < 79 && i > 0 && j > 0)
{
	int nbrNeighbors = 0;
	if (isAlive(i, j - 1, theCells))
		nbrNeighbors++;
	if (isAlive(i - 1, j - 1, theCells))
		nbrNeighbors++;
	if (isAlive(i - 1, j, theCells))
		nbrNeighbors++;
	if (isAlive(i - 1, j + 1, theCells))
		nbrNeighbors++;
	if (isAlive(i, j + 1, theCells))
		nbrNeighbors++;
	if (nbrNeighbors < 2)
		tempCells[j + i * 80] = 0;
	else if (nbrNeighbors > 3)
		tempCells[j + i * 80] = 0;
	else if (nbrNeighbors == 3)
		tempCells[j + i * 80] = 1;
}

void testTopLeft(int i, int j, int theCells[], int tempCells[]) // (i == 0 && j == 0)
{
	int nbrNeighbors = 0;
	if (isAlive(i, j + 1, theCells))
		nbrNeighbors++;
	if (isAlive(i + 1, j + 1, theCells))
		nbrNeighbors++;
	if (isAlive(i + 1, j, theCells))
		nbrNeighbors++;
	if (nbrNeighbors < 2)
		tempCells[j + i * 80] = 0;
	else if (nbrNeighbors > 3)
		tempCells[j + i * 80] = 0;
	else if (nbrNeighbors == 3)
		tempCells[j + i * 80] = 1;
}
void testTopRight(int i, int j, int theCells[], int tempCells[]) // (i == 0 && j == 79)
{
	int nbrNeighbors = 0;
	if (isAlive(i, j - 1, theCells))
		nbrNeighbors++;
	if (isAlive(i + 1, j - 1, theCells))
		nbrNeighbors++;
	if (isAlive(i + 1, j, theCells))
		nbrNeighbors++;
	if (nbrNeighbors < 2)
		tempCells[j + i * 80] = 0;
	else if (nbrNeighbors > 3)
		tempCells[j + i * 80] = 0;
	else if (nbrNeighbors == 3)
		tempCells[j + i * 80] = 1;
}
void testBotRight(int i, int j, int theCells[], int tempCells[]) // (i == 79 && j == 79)
{
	int nbrNeighbors = 0;
	if (isAlive(i - 1, j , theCells))
		nbrNeighbors++;
	if (isAlive(i - 1, j - 1, theCells))
		nbrNeighbors++;
	if (isAlive(i, j - 1, theCells))
		nbrNeighbors++;
	if (nbrNeighbors < 2)
		tempCells[j + i * 80] = 0;
	else if (nbrNeighbors > 3)
		tempCells[j + i * 80] = 0;
	else if (nbrNeighbors == 3)
		tempCells[j + i * 80] = 1;
}
void testBotLeft(int i, int j, int theCells[], int tempCells[]) // (i == 79 && j == 0)
{
	int nbrNeighbors = 0;
	if (isAlive(i - 1, j, theCells))
		nbrNeighbors++;
	if (isAlive(i - 1, j + 1, theCells))
		nbrNeighbors++;
	if (isAlive(i, j + 1, theCells))
		nbrNeighbors++;
	if (nbrNeighbors < 2)
		tempCells[j + i * 80] = 0;
	else if (nbrNeighbors > 3)
		tempCells[j + i * 80] = 0;
	else if (nbrNeighbors == 3)
		tempCells[j + i * 80] = 1;
}


