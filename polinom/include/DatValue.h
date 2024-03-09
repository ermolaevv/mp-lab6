#ifndef _POLINOM_LIB_TDATVALUE_
#define _POLINOM_LIB_TDATVALUE_

class TDatValue {
public:
	virtual TDatValue* GetCopy(void) const = 0; // создание копии
	~TDatValue(void) {}
};

#endif
