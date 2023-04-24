#ifndef __PAIR__
#define __PAIR__

class Pair {
private:
	double value1;
	double value2;

public:
	Pair();
	void addValueBack(double value);
	void addValueFront(double value);
	double getFirstValue();
	double getSecondValue();
	int getSize();
  void resetPair();
  
};

#endif
