#ifndef _POLINOM_LIB_TDATLINK_
#define _POLINOM_LIB_TDATLINK_

#include <cstddef>
#include "RootLink.h"
#include "DatValue.h"

template<class T>
class TDatLink : public TRootLink<T>{
protected:
	T* pValue; // указатель на объект значения
public:
	TDatLink(T* pVal = NULL, TRootLink<T>* pN = NULL) :
		TRootLink<T>(pN) {
		pValue = pVal;
	}
	void SetDatValue(T* pVal) override { this->pValue = pVal; }
	T* GetDatValue(void) override { return this->pValue; }
	TDatLink<T>* GetNextDatLink(void) { return (TDatLink<T>*)this->pNext; }
	TDatLink<T>* GetCopy(TRootLink<T>* next = NULL) override {
		if (this->pValue != NULL)
			return new TDatLink<T>(new T(*this->pValue), next);
		return new TDatLink<T>(NULL, next);
	}
	template<class U>
	friend class TDatList;
};

#endif
