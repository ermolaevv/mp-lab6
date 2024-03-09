#ifndef _POLINOM_LIB_THEADRING_
#define _POLINOM_LIB_THEADRING_

#include "DatList.h"

template<class T>
class THeadRing : public TDatList<T> {
protected:
	TDatLink<T>* pHead; // заголовок, pFirst - звено за pHead
public:
	THeadRing(void);
	THeadRing(const THeadRing& q);
	~THeadRing(void);
	// вставка звеньев
	virtual void InsFirst(T* pVal = NULL); // после заголовка
	// удаление звеньев
	virtual void DelFirst(void); // удалить первое звено
	int GoNext(void) override;
	void InsCurrent(T* pVal) override;
	void InsLast(T* pVal) override;
	void DelList(void) override; 
	THeadRing& operator=(const THeadRing& q);
};

#include "../src/HeadRing.hpp"

#endif
