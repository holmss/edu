#include "Pentagon.h"

TPentagon::TPentagon()
{
	this->length = 0.0;
}
TPentagon::TPentagon(double len)
{
	this->length = len;
}
TPentagon::TPentagon(const TPentagon &orig)
{
	this->length = orig.length;
}
double TPentagon::Square()
{
	return ((this->length * this->length) / 4.0) * sqrt(25.0 + 10.0 * sqrt(5));
}
void TPentagon::Print()
{
	cout << "PENTAGON: " << this->Square() << endl;
}
istream &operator >> (istream &is, TPentagon &pent)
{
	is >> pent.length;
	return is;
}
ostream &operator << (ostream &os, const TPentagon &pent)
{
	os << double(pent) << endl;
	return os;
}
bool TPentagon::operator > (TPentagon &right)
{
	if (this->Square() > double(right)) {
		return true;
	}
	else return false;
}
bool TPentagon::operator < (TPentagon &right)
{
	if (this->Square() < double(right)) {
		return true;
	}
	else return false;
}
bool TPentagon::operator >= (TPentagon &right)
{
	if (this->Square() >= double(right)) {
		return true;
	}
	else return false;
}
bool TPentagon::operator <= (TPentagon &right)
{
	if (this->Square() <= double(right)) {
		return true;
	}
	else return false;
}
TPentagon::operator double() const
{
	return ((this->length * this->length) / 4.0) * sqrt(25.0 + 10.0 * sqrt(5));
}
bool TPentagon::operator == (TPentagon &right)
{
	if (this->Square() == double(right)) {
		return true;
	}
	else return false;
}
TPentagon& TPentagon::operator=(TPentagon &right)
{
	if (this == &right) {
		return *this;
	}
	else {
		this->length = right.length;
		return *this;
	}
}
TPentagon::~TPentagon()
{
	this->length = 0.0;
}