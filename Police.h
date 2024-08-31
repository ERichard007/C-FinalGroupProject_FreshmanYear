#include <iostream>
#include "City.h"
using namespace std;

template <typename R>
class Robber;


#ifndef POLICE_H
#define POLICE_H
/********************POLICE CLASS********************/
class Police {
public:
	/*GETTER AND SETTERS*/
	Police getPolice(const int xIndex, const int yIndex);
	int getXCor() { return xCor; }
	int getYCor() { return yCor; }
	int getID() { return id; }

	/*MEMBER FUNCTIONS*/
	template <typename R>
	void arrest(const Robber<R>& robber);

	template <typename R>
	void move(City& C);

	/*OVERLOADS*/
	bool operator !=(const Police& rhs);

	bool operator ==(const Police& rhs);

	/*CONSTRUCTORS*/
	Police() {};

	Police(City& C);

	/*MEMBER VARIABLES*/
	static Police allPolice[60];

private:
	/*MEMBER VARIABLES*/
	static int totalRobberCaught;

	int xCor = -1, yCor = -1, id = 0, totalLootConfiscatedValue = 0;
};

#endif

