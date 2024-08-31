#include <iostream>
using namespace std;

#ifndef CITY_H
#define CITY_H

/********************CITY CLASS********************/
class City {
public:
	/*GETTER AND SETTERS*/
	char getCityGrid(int indexX, int indexY) const { return cityGrid[indexX][indexY]; }

	void setCityGrid(int indexX, int indexY, char value) { cityGrid[indexX][indexY] = value; }

	/*MEMBER FUNCTIONS*/
	void printCityGrid();

	/*CONSTRUCTORS*/
	City();

private:
	/*MEMBER VARIABLES*/
	char cityGrid[11][13] = {};
	int numOfJewels = 60;
};

#endif
