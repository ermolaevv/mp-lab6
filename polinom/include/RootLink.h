#ifndef _POLINOM_LIB_TROOTLINK_
#define _POLINOM_LIB_TROOTLINK_

#include "DatValue.h"
#include "DatList.h"

template<class T>
class TRootLink {
protected:
	TRootLink<T>* pNext; // указатель на следующее звено
public:
	TRootLink(TRootLink<T>* pN = NULL) { pNext = pN; }
	TRootLink<T>* GetNextLink(void) { return pNext; }
	void SetNextLink(TRootLink<T>* pLink) { pNext = pLink; }
	void InsNextLink(TRootLink<T>* pLink) {
		TRootLink* p = pNext; pNext = pLink;
		if (pLink != NULL) pLink->pNext = p;
	}
	virtual void SetDatValue(T* pVal) = 0;
	virtual T* GetDatValue(void) = 0;
	virtual TRootLink<T>* GetCopy(TRootLink<T>* next = NULL) = 0;
	template<class U>
	friend class TDatList;
};

#endif#
