#ifndef OCTAGON_H
#define OCTAGON_H
#include "Shape.h"


using namespace std;

class TOctagon : public TShape {
public:
	TOctagon();
	TOctagon(double len);
	TOctagon(const TOctagon &orig);
	double Square() override;
	void Print() override;
	friend istream &operator >> (istream &is, TOctagon &oct);
	friend ostream &operator << (ostream &os, const TOctagon &oct);
	bool operator > (TOctagon &right);
	bool operator < (TOctagon &right);
	bool operator >= (TOctagon &right);
	bool operator <= (TOctagon &right);
	operator double() const;
	bool operator == (TOctagon &right);
	TOctagon& operator = (TOctagon &right);
	virtual ~TOctagon() override;
private:
	double length;
};

#endif
