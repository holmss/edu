#ifndef IREMOVECRITERIA_H
#define IREMOVECRITERIA_H

template <class T> class IRemoveCriteria {
public:
	virtual bool IsIt(T *value) = 0;
private:
};

#endif