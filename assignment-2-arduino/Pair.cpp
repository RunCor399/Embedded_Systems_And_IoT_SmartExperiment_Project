#include "Pair.h"

/* Class that contains Pair of two objects */
Pair::Pair() {
	this->value1 = -1;
	this->value2 = -1;
}

double Pair::getFirstValue() {
	return this->value1;
}

double Pair::getSecondValue() {
	return this->value2;
}

void Pair::addValueFront(double position) {
	this->value1 = position;
}

void Pair::addValueBack(double position) {
	this->value2 = position;
}

int Pair::getSize() {
	if (this->value1 == -1 && this->value2 == -1) {
		return 0;
	}
	else if (this->value1 == -1 && this->value2 != -1) {
		return 1;
	}
	else {
		return 2;
	}
}

void Pair::resetPair() {
  this->value1 = -1;
  this->value2 = -1;
}
