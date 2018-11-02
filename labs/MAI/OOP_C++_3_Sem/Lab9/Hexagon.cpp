#include "Hexagon.h"

THexagon::THexagon()
{
	this->length = 0.0;

}
THexagon::THexagon(double len)
{
	this->length = len;
}
THexagon::THexagon(const THexagon &orig)
{
	this->length = orig.length;
}
double THexagon::Square()
{
	return ((3.0 * sqrt(3.0)) * (this->length * this->length)) / 2.0;
}
void THexagon::Print()
{
	cout << "HEXAGON: " << this->Square() << endl;
}
istream &operator >> (istream &is, THexagon &hex)
{
	is >> hex.length;
	return is;
}
ostream &operator << (ostream &os, const THexagon &hex)
{
	os << double(hex) << endl;
	return os;
}
bool THexagon::operator > (THexagon &right)
{
	if (this->Square() > double(right)) {
		return true;
	}
	else return false;
}
bool THexagon::operator < (THexagon &right)
{
	if (this->Square() < double(right)) {
		return true;
	}
	else return false;
}
bool THexagon::operator >= (THexagon &right)
{
	if (this->Square() >= double(right)) {
		return true;
	}
	else return false;
}
bool THexagon::operator <= (THexagon &right)
{
	if (this->Square() <= double(right)) {
		return true;
	}
	else return false;
}
THexagon::operator double() const
{
	return ((3.0 * sqrt(3.0)) * (this->length * this->length)) / 2.0;
}
bool THexagon::operator == (THexagon &right)
{
	if (this->Square() == double(right)) {
		return true;
	}
	else return false;
}
THexagon& THexagon::operator=(THexagon &right)
{
	if (this == &right) {
		return *this;
	}
	else {
		this->length = right.length;
		return *this;
	}
}
THexagon::~THexagon()
{
	this->length = 0.0;
}