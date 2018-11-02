#ifndef PENTAGON_H
#define PENTAGON_H
#include "Shape.h"

using namespace std;


class TPentagon : public TShape {
public:
	TPentagon();
	TPentagon(double len);
	TPentagon(const TPentagon &orig);
	double Square() override;
	void Print() override;
	friend istream &operator >> (istream &is, TPentagon &pent);
	friend ostream &operator << (ostream &os, const TPentagon &pent);
	bool operator > (TPentagon &right);
	bool operator < (TPentagon &right);
	bool operator >= (TPentagon &right);
	bool operator <= (TPentagon &right);
	operator double() const;
	bool operator == (TPentagon &right);
	TPentagon& operator = (TPentagon &right);
	virtual ~TPentagon() override;
private:
	double length;
};

#endif
