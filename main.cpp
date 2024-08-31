// Programmer: Evan Richard & Christopher Elam
// Date: 4/22/2024
// File: main.cpp
// Assignment: Final Project
// Purpose: Use all of the skill learned so far to make a final project about a robbery escape!

#include <iostream>
#include <cstdlib>
#include <time.h> // delete when done
#include "City.h"
#include "Jewel.h"
#include "Police.h"
#include "Robber.h"
using namespace std;

int ROBBERLIMIT = 20;

int main() { //implement police and robber move functions
	srand(time(0)); //100

	City myCity;

	Police police1(myCity);
	Police police2(myCity);
	Police police3(myCity);

	Robber<int> robber1(myCity, false);
	Robber<int> robber2(myCity, false);

	Robber<int> gRobber1(myCity, true);
	Robber<int> gRobber2(myCity, true);

	myCity.printCityGrid();

	robber1.move(myCity);

	myCity.printCityGrid();

	return 0;
}