#ifndef HEXAGON_H
#define HEXAGON_H
#include "Shape.h"

using namespace std;

class THexagon : public TShape {
public:
	THexagon();
	THexagon(double len);
	THexagon(const THexagon &orig);
	double Square() override;
	void Print() override;
	friend istream &operator >> (istream &is, THexagon &hex);
	friend ostream &operator << (ostream &os, const THexagon &hex);
	bool operator > (THexagon &right);
	bool operator < (THexagon &right);
	bool operator >= (THexagon &right);
	bool operator <= (THexagon &right);
	operator double() const;
	bool operator == (THexagon &right);
	THexagon& operator = (THexagon &right);
	virtual ~THexagon() override;
private:
	double length;
};

#endif
