#ifndef IREMOVECRITERIABYVALUE_H
#define IREMOVECRITERIABYVALUE_H
#include "IRemoveCriteria.h"

template <class T> class IRemoveCriteriaByValue : public IremoveCriteria<T>{
public:
	IRemoveCriteriaByValue(T value) : _value(value) {};
	bool IsIt(T *value) override {
		return _value == *value;
	};
private:
	T _value;

}

#endif
