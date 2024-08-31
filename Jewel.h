#include <iostream>
using namespace std;

#ifndef JEWEL_H
#define JEWEL_H

/********************JEWEL CLASS********************/
class Jewel {
public:
	/*GETTER AND SETTER*/
	Jewel getJewel(const int xIndex, const int yIndex);
	int getValue() const { return value; }
	int getXCor() const { return xCor; }
	int getYCor() const { return yCor; }
	bool getIsLooted() const { return looted; }

	void setXCor(int x) { xCor = x; }
	void setYCor(int y) { yCor = y; }
	void setLooted(bool l) { looted = l; }
	void setValue(int v) { value = v; }

	/*MEMBER FUNCTIONS*/
	void remove(Jewel& jew);

	/*OVERLOADS*/
	Jewel operator *(const int mult);

	Jewel operator *=(const int mult);

	bool operator ==(const Jewel& rhs);

	bool operator !=(const Jewel& rhs);

	/*CONSTRUCTORS*/
	Jewel() {};

	Jewel(const int values, const int xPos, const int yPos);

	/*MEMBER VARIABLES*/
	static Jewel allJewels[60];
private:
	/*MEMBER VARIABLES*/
	int value = 0, xCor = -1, yCor = -1;

	bool looted = false;
};

#endif