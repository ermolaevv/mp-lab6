#ifndef _POLINOM_LIB_TMONOM_
#define _POLINOM_LIB_TMONOM_

#include <iostream>
#include <string>
#include "DatValue.h"


class TMonom : public TDatValue {
protected:
	double Coeff; // коэффициент монома
	int CountDeg; // индекс (свертка степеней)
	int* Deg;
public:
	TMonom(const double cval = 1, const int ival = 0, const int* deg = NULL);
	TMonom(const TMonom& m);
	~TMonom(void);
	virtual TMonom* GetCopy(void) const
	{
		return new TMonom(*this);
	} // изготовить копию
	void SetCoeff(const double cval) { Coeff = cval; }
	double GetCoeff(void) const { return Coeff; }

	void SetCountDeg(const int ival);
	int GetCountDeg(void) const { return CountDeg; }

	void SetDeg(const int* deg);
	int* GetDeg(void) { return Deg;	}

	std::string ToString(void);

	TMonom operator+(const TMonom& mon);
	TMonom& operator+=(const TMonom& mon);

	TMonom operator-(const TMonom& mon);
	TMonom& operator-=(const TMonom& mon);

	TMonom operator*(const TMonom& mon);
	TMonom& operator*=(const TMonom& mon);
	
	TMonom& operator=(const TMonom& tm);

	bool operator==(const TMonom& tm) const;
	int operator<(const TMonom& mon);
	int operator<(const TMonom& mon) const;
	int operator>(const TMonom& mon);
	int operator>(const TMonom& mon) const;

	friend class TPolinom;
	friend std::istream& operator>>(std::istream& istr, TMonom& mon);
	friend std::ostream& operator<<(std::ostream& ostr, const TMonom& mon);
};


TMonom::TMonom(const double cval, const int ival, const int* deg)
{
    Coeff = cval; CountDeg = ival;
    if (deg != NULL) {
        Deg = new int[ival];
        std::copy(deg, deg + ival, Deg);
    }
    else {
        Deg = NULL;
    }
}

TMonom::TMonom(const TMonom& m)
{
    this->Coeff = m.Coeff;
    this->CountDeg = m.CountDeg;
    this->Deg = new int[this->CountDeg];
    std::copy(m.Deg, m.Deg + m.CountDeg, this->Deg);
}


TMonom::~TMonom()
{
    if (Deg != nullptr)
        delete[] Deg;
    CountDeg = 0;
    Coeff = 0;
}


void TMonom::SetCountDeg(int _count)
{
    if (_count < 0)
        throw std::exception("Error monom`s count");
    else if (_count == 0)
    {
        if (Deg != 0)
            delete[] Deg;
        Deg = 0;
        CountDeg = 0;
    }
    else if (_count == CountDeg) {
        return;
    }
    else
    {
        int* tmp = new int[CountDeg];
        std::copy(Deg, Deg + CountDeg, tmp);

        if (Deg != NULL)
            delete[] Deg;

        Deg = new int[_count] {};
        int i = 0;
        if (CountDeg >= _count)
            std::copy(tmp, tmp + _count, Deg);
        else
            std::copy(tmp, tmp + CountDeg, Deg);
        CountDeg = _count;

        if (tmp != NULL)
            delete[] tmp;
    }
}


void TMonom::SetDeg(const int* _deg)
{
    for (int i = 0; i < CountDeg; i++)
    {
        if (_deg[i] >= 0)
            Deg[i] = _deg[i];
        else
            throw std::exception("Error degree");
    }
}


TMonom TMonom::operator+(const TMonom& mon)
{
    TMonom tmp(mon);
    if (CountDeg != mon.CountDeg)
        throw std::exception("Error different monoms`s count");

    for (int i = 0; i < mon.CountDeg; i++)
        if (Deg[i] != mon.Deg[i])
            throw std::exception("Error different degree");

    tmp.Coeff = Coeff + mon.Coeff;
    return tmp;
}


TMonom& TMonom::operator+=(const TMonom& mon)
{
    if (CountDeg != mon.CountDeg)
        throw std::exception("Error different monoms`s count");

    for (int i = 0; i < mon.CountDeg; i++)
        if (Deg[i] != mon.Deg[i])
            throw std::exception("Error different degree");

    Coeff += mon.Coeff;
    return *this;
}


TMonom TMonom::operator-(const TMonom& mon)
{
    TMonom tmp(mon);
    if (CountDeg != mon.CountDeg)
        throw std::exception("Error different monoms`s count");

    for (int i = 0; i < mon.CountDeg; i++)
        if (Deg[i] != mon.Deg[i])
            throw std::exception("Error different degree");

    tmp.Coeff = Coeff - mon.Coeff;
    return tmp;
}


TMonom& TMonom::operator-=(const TMonom& mon)
{
    if (CountDeg != mon.CountDeg)
        throw std::exception("Error different monoms`s count");

    for (int i = 0; i < mon.CountDeg; i++)
        if (Deg[i] != mon.Deg[i])
            throw std::exception("Error different degree");

    Coeff -= mon.Coeff;
    return *this;
}


TMonom TMonom::operator*(const TMonom& mon)
{
    if (CountDeg != mon.CountDeg)
        throw std::exception("Error different monoms`s count");

    TMonom tmp(mon);
    tmp.Coeff = Coeff * mon.Coeff;
    for (int i = 0; i < CountDeg; i++)
        tmp.Deg[i] = Deg[i] + mon.Deg[i];
    return tmp;
}


TMonom& TMonom::operator*=(const TMonom& mon)
{
    if (CountDeg != mon.CountDeg)
        throw std::exception("Error different monoms`s count");

    Coeff = Coeff * mon.Coeff;
    for (int i = 0; i < CountDeg; i++)
        Deg[i] += mon.Deg[i];
    return *this;
}


std::istream& operator>>(std::istream& istr, TMonom& mon)
{
    istr >> mon.Coeff;
    istr >> mon.CountDeg;
    for (int i = 0; i < mon.CountDeg; i++)
        istr >> mon.Deg[i];
    return istr;
}


std::ostream& operator<<(std::ostream& ostr, const TMonom& mon)
{
    double coef = mon.GetCoeff();
    if (coef == (int)coef)
        ostr << std::to_string((int)coef);
    else
        ostr << std::to_string(round(coef * 100) / 100);
    if (coef != 0)
    {
        for (int i = 0; i < mon.CountDeg; i++)
            if (mon.Deg[i] != 0)
            {
                ostr << "*x" + std::to_string(i);
                if (mon.Deg[i] != 1)
                    ostr << "^" + std::to_string(mon.Deg[i]);
            }
    }
    return ostr;
}


TMonom& TMonom::operator=(const TMonom& mon)
{
    if (CountDeg != mon.CountDeg)
        throw std::exception("Error leng not equal");

    Coeff = mon.Coeff;
    if (CountDeg != mon.CountDeg) {
        CountDeg = mon.CountDeg;
        if (Deg == NULL)
            delete[] Deg;
        Deg = new int[CountDeg];
    }
    std::copy(mon.Deg, mon.Deg + mon.CountDeg, Deg);
    return *this;
}


int TMonom::operator<(const TMonom& mon)
{
    if (CountDeg != mon.CountDeg)
        throw false;
    if (*this == mon)
        return false;

    for (int i = 0; i < CountDeg; i++)
    {
        if (Deg[i] == mon.Deg[i])
            continue;
        else if (Deg[i] < mon.Deg[i])
            return true;
        else
            return false;
    }
    if (Coeff >= mon.Coeff)
        return false;
    return true;
}

int TMonom::operator<(const TMonom& mon) const
{
    if (*this == NULL)
        return true;
    if (mon == NULL)
        return false;
    if (CountDeg != mon.CountDeg)
        throw false;
    if (*this == mon)
        return false;

    for (int i = 0; i < CountDeg; i++)
    {
        if (Deg[i] == mon.Deg[i])
            continue;
        else if (Deg[i] < mon.Deg[i])
            return true;
        else
            return false;
    }
    if (Coeff > mon.Coeff)
        return false;
    return true;
}



std::string TMonom::ToString()
{
    std::string res;
    double coef = GetCoeff();
    if (coef == (int)coef)
        res += std::to_string((int)coef);
    else
        res += std::to_string(round(coef * 100000) / 100000);
    if (coef != 0)
    {
        for (int i = 0; i < CountDeg; i++)
            if (Deg[i] != 0)
            {
                res += "*x" + std::to_string(i);
                if (Deg[i] != 1)
                    res += "^" + std::to_string(Deg[i]);
            }
    }
    return res;
}


int TMonom::operator>(const TMonom& mon) {
    return !(*this < mon);
}

int TMonom::operator>(const TMonom& mon) const {
    return !(*this < mon);
}

bool TMonom::operator==(const TMonom& mon) const
{
    if (Coeff != mon.Coeff)
        return false;
    if (CountDeg != mon.CountDeg)
        return false;
    if (!std::equal(Deg, Deg + CountDeg, mon.Deg))
        return false;
    return true;
}


#endif
