#include "Police.h"
#include "Jewel.h"
#include "City.h"
#include <iostream>
#include <cstdlib>
using namespace std;

#ifndef ROBBER_H
#define ROBBER_H

/********************ROBBER TEMPLATE CLASS DEFINITION********************/
template <typename R>
class Robber {
public:
	/*GETTER AND SETTERS*/
	int getTotalLootValue(const Robber& robber);
	Robber getRobber(const int xIndex, const int yIndex) const;
	void getIsActive() { return isActive; }
	Robber getLoot(int index) { return loot[index]; }
	int getXCor() const { return xCor; }
	int getYCor() const { return yCor; }

	void setIsActive(bool x) { isActive = x; }

	/*MEMBER FUNCTIONS*/
	void pickUpLoot(Jewel loot);

	void move(City& C);

	/*OVERLOADS*/
	Robber operator --(int);

	bool operator ==(const Robber& rhs);

	bool operator !=(const Robber& rhs);

	/*CONSTRUCTORS*/
	Robber(City& C, const bool isGreedy);

	Robber(City& C, Robber& other);

	Robber() {};

	/*MEMBER VARIABLES*/
	static Robber allRobbers[20];

	/*FORWARD DECLARATIONS*/
	class Police;
private:
	/*MEMBER VARIABLES*/
	static int totalLootValue, numOfRobbers, numOfMoves;

	int xCor = -1, yCor = -1, id = 0, turnsWithoutJewel;

	bool isActive, isOrdinary, spawnedARobber, immobilized;

	Jewel loot[20] = {};
};


/********************ROBBER TEMPLATE CLASS IMPLEMENTATION********************/
template <typename R>
int Robber<R>::totalLootValue = 0;
template <typename R>
int Robber<R>::numOfMoves = 0;
template <typename R>
int Robber<R>::numOfRobbers = 0;
template <typename R>
Robber<R> Robber<R>::allRobbers[] = {};

template <typename R>
int Robber<R>::getTotalLootValue(const Robber& robber) {
	int sum = 0;
	for (int i = 0; i < 20; i++) {
		sum += loot[i].value;
	}
	return sum;
}

template <typename R>
Robber<R> Robber<R>::getRobber(const int xIndex, const int yIndex) const {
	for (int i = 0; i < 20; i++) {
		if (allRobbers[i].xCor == xIndex && allRobbers[i].yCor == yIndex && allRobbers[i].isActive == true) {
			return allRobbers[i];
		}
	}
	return Robber;
}

template <typename R>
Robber<R>::Robber(City& C, bool isGreedy) {
	Robber emptyR;

	turnsWithoutJewel = 0;
	immobilized = false;
	numOfRobbers++;
	id = numOfRobbers;
	isActive = true;
	isOrdinary = (isGreedy == true) ? false : true;
	spawnedARobber = false;


	int randX = rand() % 12;
	int randY = rand() % 14;

	while (C.getCityGrid(randX, randY) != '\0') {
		randX = rand() % 12;
		randY = rand() % 14;
	}

	xCor = randX;
	yCor = randY;

	for (int i = 0; i < 20; i++) {
		if (allRobbers[i] == emptyR) {
			allRobbers[i] = (*this);
			break;
		}
	}
}

template <typename R>
Robber<R>::Robber(City& C, Robber& other) : isActive(other.isActive), isOrdinary(other.isOrdinary) {
	R emptyR;

	other.turnsWithoutJewel = 0;
	other.immobilized = false;

	for (int i = 0;i < 20;i++) {
		int rand20 = rand() % 21;

		if (loot[i] == emptyR) {
			continue;
		}

		while (other.loot[rand20] != emptyR) {
			rand20 = rand() % 21;
		}

		other.loot[rand20] = loot[i];

		other.totalLootValue += loot[i].value;
	}

	int randX = rand() % 12;
	int randY = rand() % 14;

	while (C.getCityGrid(randX, randY) != '\0') {
		randX = rand() % 12;
		randY = rand() % 14;
	}

	xCor = randX;
	yCor = randY;

	numOfRobbers++;
	other.id += numOfRobbers;

	for (int i = 0; i < 20; i++) {
		if (allRobbers[i] == emptyR) {
			allRobbers[i] = (*this);
		}
	}

	other.spawnedARobber = false;
}

template <typename R>
void Robber<R>::pickUpLoot(Jewel lootToAdd) {
	R emptyR;

	for (int i = 0; i < loot.size(); i++) {
		if (loot[i] == emptyR) {
			loot[i] = lootToAdd;
			totalLootValue += lootToAdd.value;
			break;
		}
	}
}

template <typename R>
void Robber<R>::move(City& C) {

	if (isActive == false) {
		return;
	}
	else if (immobilized == true) {
		immobilized = false;
		turnsWithoutJewel = 0;
		return;
	}
	else if (turnsWithoutJewel >= 5) {
		turnsWithoutJewel = 0;
		immobilized = true;
		return;
	}

	numOfMoves++;

	Jewel emptyR;

	bool incompatible = true;
	bool tripped = false;

	int oriXCor = xCor;
	int oriYCor = yCor;

	int tripChance = rand() % 101;
	if (tripChance <= 60) {
		(*this)--;
		tripped = true;
	}

	while (incompatible) {
		int randMove = (rand() % 8);

		xCor = oriXCor;
		yCor = oriYCor;

		switch (randMove) {
		case 0:
			xCor -= 1;
			yCor -= 1;
		case 1:
			yCor -= 1;
		case 2:
			xCor += 1;
			yCor -= 1;
		case 3:
			xCor -= 1;
		case 4:
			xCor += 1;
		case 5:
			xCor -= 1;
			yCor += 1;
		case 6:
			yCor += 1;
		case 7:
			xCor += 1;
			yCor += 1;
		}

		incompatible = (xCor > 11 || xCor < 0 || yCor < 0 || yCor > 13) ? true : false;
	}

	if (tripped) {
		incompatible = true;

		int jXCor = xCor;
		int jYCor = yCor;

		while (incompatible) {
			int randMove = (rand() % 8);

			jXCor = xCor;
			jYCor = yCor;

			switch (randMove) {
			case 0:
				jXCor -= 1;
				jYCor -= 1;
			case 1:
				jYCor -= 1;
			case 2:
				jXCor += 1;
				jYCor -= 1;
			case 3:
				jXCor -= 1;
			case 4:
				jXCor += 1;
			case 5:
				jXCor -= 1;
				jYCor += 1;
			case 6:
				jYCor += 1;
			case 7:
				jXCor += 1;
				jYCor += 1;
			}

			incompatible = (jXCor > 11 || jXCor < 0 || jYCor < 0 || jYCor > 13 || C.getCityGrid(jXCor, jYCor) != '\0') ? true : false;
		}
		for (int i = 0; i < 20;i++) {
			if (loot[i] != emptyR) {
				loot[i].setXCor(jXCor);
				loot[i].setYCor(jYCor);
				loot[i].setLooted(false);
			}
			break;
		}
		(*this)--;
	}

	if (C.getCityGrid(xCor, yCor) == 'r') {
		turnsWithoutJewel++;
		for (int i = 0; i < 20; i++) {
			if (allRobbers[i].id != id && allRobbers[i].xCor == xCor && allRobbers[i].yCor == yCor) {
				if (isOrdinary == false && allRobbers[i].isActive == true) {
					int numOfLoot;
					for (int i = 0; i < 20; i++) {
						if (loot[i] != emptyR) {
							numOfLoot++;
						}
					}

					int ct = 0;
					for (int i = 0; i < 20; i++) {
						if (ct >= (numOfLoot / 2)) {
							break;
						}
						else if (loot[i] != emptyR) {
							ct++;
							if (C.getCityGrid(loot[i].getXCor(), loot[i].getYCor()) != '\0') {
								loot[i].setLooted(false);
								int randX = rand() % 12;
								int randY = rand() % 14;
								while (C.getCityGrid(randX, randY) != '\0') {
									randX = rand() % 12;
									randY = rand() % 14;
								}
								loot[i].setXCor(randX);
								loot[i].setYCor(randY);
								loot[i].setValue((randX + randY) * (randX + randY));
								(*this)--;
							}
							else {
								loot[i].setLooted(false);
								(*this)--;
							}
						}
					}

				}

				break;
			}
		}
	}

	else if (C.getCityGrid(xCor, yCor) == 'J') {
		turnsWithoutJewel = 0;
		Jewel foundJewel = foundJewel.getJewel(xCor, yCor);
		pickUpLoot(foundJewel);
		foundJewel.setLooted(true);

		if (foundJewel.getValue() % 2 == 0 && isOrdinary == false) {
			if (numOfMoves < 3) {
				move(C);
			}
		}
	}

	else if (C.getCityGrid(xCor, yCor) == 'p') {
		Police foundP = foundP.getPolice(xCor, yCor);
		foundP.arrest((*this));
	}
	else {
		turnsWithoutJewel++;
	}

	if (totalLootValue > 1600 && spawnedARobber == false && numOfRobbers < 20 && isActive == true && immobilized == false) {
		spawnedARobber = true;
		Robber newRobber(C, (*this));
	}

	numOfMoves = 0;
}

template <typename R>
Robber<R> Robber<R>::operator --(int) {
	R emptyR;

	for (int i = 0; i < 20; i++) {
		while (loot[i] == emptyR) {
			continue;

		}
		loot[i] = emptyR;
		return (*this);
	}

	return (*this);
}

template <typename R>
bool Robber<R>::operator ==(const Robber& rhs) {
	return (id == rhs.id);
}

template <typename R>
bool Robber<R>::operator !=(const Robber& rhs) {
	return (id != rhs.id);
}

#endif


