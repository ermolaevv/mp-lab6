#ifndef _POLINOM_LIB_TPOLIMOM_
#define _POLINOM_LIB_TPOLINOM_

#include <vector>
#include <map>

#include "HeadRing.h"
#include "Monom.h"
#include "../../postfix/include/MyExpression.h"

class TPolinom : public THeadRing<TMonom> {
protected:
	int countVar;																	  //количество переменных в каждом мономе
public:
	TPolinom(const int countVar = 3, const int** monoms = NULL, const int km = 0); // конструктор
	// полинома из массива «коэффициент-индекс»
	TPolinom(const TPolinom& q); // конструктор копирования

	const TMonom* GetMonom(void) const { return GetDatValue(); }
	const TMonom* GetMonom(int pos) const { return GetDatValue(pos); }
	void AddMonom(const TMonom& nM);

	TPolinom MultMonom(const TMonom monom);
	TPolinom AddPolinom(const TPolinom& other);

	TPolinom operator+(const TPolinom& q);
	TPolinom& operator+=(const TPolinom& q);
	TPolinom operator-(const TPolinom& q);
	TPolinom& operator-=(const TPolinom& q);

	TPolinom operator*(const double coef) const;
	TPolinom operator*(const double coef);
	TPolinom operator*(const TMonom& coef);
	TPolinom operator*(const TPolinom& other);

    TPolinom Integrate() const;

	TPolinom& operator=(const TPolinom& q); // присваивание
	bool operator==(const TPolinom& other) const;

	std::string ToString(void);
	friend std::ostream& operator<<(std::ostream& ostr, TPolinom& q);

    double Calculate(const int countVar, const double* value);
};

TPolinom::TPolinom(const int cVar, const int** monoms, const int len)
{
    countVar = cVar;
    if (monoms != NULL && len != 0) {
        for (size_t i = 0; i < len; i++) {
            InsCurrent(new TMonom(monoms[i][0], countVar, monoms[i] + 1));
        }
    }
}


TPolinom::TPolinom(const TPolinom& q) : THeadRing(q)
{
    countVar = q.countVar;
}


TPolinom TPolinom::operator*(const double coef) const
{
    TPolinom res(countVar);

    TDatLink<TMonom>* tmp1 = pFirst;
    while (tmp1 != pHead)
    {
        TMonom k = *tmp1->GetDatValue();
        k.SetCoeff(k.GetCoeff() * coef);
        res.AddMonom(k);

        tmp1 = tmp1->GetNextDatLink();
    }
    return res;
}

TPolinom TPolinom::operator*(const double coef)
{
    TPolinom res(countVar);

    TDatLink<TMonom>* tmp1 = pFirst;
    while (tmp1 != pHead)
    {
        TMonom k = *tmp1->GetDatValue();
        k.SetCoeff(k.GetCoeff() * coef);
        res.AddMonom(k);

        tmp1 = tmp1->GetNextDatLink();
    }
    return res;
}

TPolinom TPolinom::operator*(const TMonom& coef)
{
    if (this->countVar != coef.CountDeg)
        throw std::exception("Error different polinomial`s count");

    TPolinom res(countVar);

    TDatLink<TMonom>* tmp1 = pFirst;
    while (tmp1 != pHead)
    {
        TMonom k = (*tmp1->GetDatValue()) * coef;
        res.AddMonom(k);

        tmp1 = tmp1->GetNextDatLink();
    }
    return res;
}

inline TPolinom TPolinom::operator*(const TPolinom& other)
{
    if (this->countVar != other.countVar)
        throw std::exception("Error different polinomial`s count");
    TPolinom res(countVar);
    TDatLink<TMonom>* tmp1 = pFirst;
    TDatLink<TMonom>* tmp2 = other.pFirst;
    while (tmp1 != pHead)
    {
        while (tmp2 != other.pHead)
        {
            TMonom k = (*tmp1->GetDatValue()) * (*tmp2->GetDatValue());

            res.AddMonom(k);
            tmp2 = tmp2->GetNextDatLink();
        }
        tmp1 = tmp1->GetNextDatLink();
        tmp2 = other.pFirst;
    }
    return res;
}

TPolinom& TPolinom::operator=(const TPolinom& q)
{
    if (this == &q)
        return *this;
    else
    {
        DelList();
        countVar = q.countVar;
        THeadRing::operator=(q);
        return *this;
    }
}

bool TPolinom::operator==(const TPolinom& other) const
{
    if (this->countVar != other.countVar)
        return false;
    if (this->ListLen != other.ListLen)
        return false;

    TDatLink<TMonom>* tmp1 = pFirst;
    TDatLink<TMonom>* tmp2 = other.pFirst;

    for (size_t i = 0; i < ListLen; i++)
    {
        if (!(*tmp1->GetDatValue() == (*tmp2->GetDatValue())))
            return false;

        tmp1 = tmp1->GetNextDatLink();
        tmp2 = tmp2->GetNextDatLink();
    }
    return true;
}


void TPolinom::AddMonom(const TMonom& nM)
{
    if (this->countVar != nM.GetCountDeg())
        throw std::exception("Error different polinomial`s count");
    if (nM.GetCoeff() == 0)
        return;

    if (pFirst == NULL)
        InsFirst(nM.GetCopy());
    else if (std::equal(nM.Deg, nM.Deg + nM.CountDeg,
        pFirst->GetDatValue()->Deg))
    {
        pFirst->GetDatValue()->operator+=(nM);
        if (pFirst->GetDatValue()->GetCoeff() == 0)
            DelFirst();
    }
    else {
        int i = 0;
        while (ListLen > 0 && i <= ListLen && *GetMonom() > nM &&
            !(std::equal(nM.Deg, nM.Deg + nM.CountDeg, GetMonom()->Deg)))
        {
            i++;
            if (i == ListLen) {
                InsLast(nM.GetCopy());
                return;
            }
            GoNext();
        }

        if (std::equal(nM.Deg, nM.Deg + nM.CountDeg,
            GetMonom()->Deg)) {
            pCurrLink->GetDatValue()->operator+=(nM);
            if (pCurrLink->GetDatValue()->GetCoeff() == 0)
                DelCurrent();
        }
        else {
            if (GetCurrentPos() == 0) {
                InsFirst(nM.GetCopy());
            }
            else if (GetCurrentPos() > 0) {
                SetCurrentPos(GetCurrentPos() - 1);
                InsCurrent(nM.GetCopy());
            }
        }
    }
}

TPolinom TPolinom::MultMonom(const TMonom monom)
{
    return *this * monom;
}

TPolinom TPolinom::AddPolinom(const TPolinom& other)
{
    return *this + other;
}


std::string TPolinom::ToString()
{
    std::string res = "";
    TDatLink<TMonom>* tmp = pFirst;
	if (ListLen == 0) {
		return "0";
	}
    if (tmp != NULL)
    {
        if (tmp->GetDatValue() == NULL) {
            res += "0";
        }
        else {
            res += ((TMonom*)tmp->GetDatValue())->ToString();
        }
        tmp = tmp->GetNextDatLink();
    }
    while (tmp != NULL && tmp != pHead)
    {
        if (((TMonom*)tmp->GetDatValue())->GetCoeff() > 0) {
            res += " + " + ((TMonom*)tmp->GetDatValue())->ToString();
        }
        else if (((TMonom*)tmp->GetDatValue())->GetCoeff() < 0) {
            tmp->GetDatValue()->SetCoeff(-tmp->GetDatValue()->GetCoeff());
            res += " - " + ((TMonom*)tmp->GetDatValue())->ToString();
            tmp->GetDatValue()->SetCoeff(-tmp->GetDatValue()->GetCoeff());
        }
        tmp = tmp->GetNextDatLink();

    }
    return res;
}

double TPolinom::Calculate(const int countVar, const double* value)
{
    if (this->countVar != countVar)
        throw std::runtime_error("The number of variables is different");
    if (value == nullptr)
        throw std::runtime_error("Value's array is nullptr");

    std::string pol = this->ToString();
    TArithmeticExpression expr(pol);
    std::vector<std::string> valNames = expr.GetOperands();

    std::map<std::string, double> op;
    for (int i = 0; i < this->countVar; i++) {
        op.insert(std::pair<std::string, double>(valNames[i], value[i]));
    }

    return expr.Calculate(op);
}

TPolinom TPolinom::operator+(const TPolinom& q)
{
    if (countVar != q.countVar)
        throw std::exception("Error different polinomials`s count");
	if (*this == q * -1.0) {
		return TPolinom(countVar);
	}
    TPolinom res(*this);

    TDatLink<TMonom>* tmp2 = q.pFirst;

    for (size_t i = 0; i < q.ListLen; i++)
    {
        res.AddMonom(*tmp2->GetDatValue());
        tmp2 = tmp2->GetNextDatLink();
    }

    return res;
}

TPolinom& TPolinom::operator+=(const TPolinom& q)
{
    *this = *this + q;

    return *this;
}

TPolinom TPolinom::operator-(const TPolinom& q)
{
    if (countVar != q.countVar)
        throw std::exception("Error different polinomials`s count");

    TPolinom res(*this);

    TDatLink<TMonom>* tmp2 = q.pFirst;

    for (size_t i = 0; i < q.ListLen; i++)
    {
        TMonom tmp = *tmp2->GetDatValue();
        tmp.SetCoeff(-tmp.GetCoeff());
        res.AddMonom(tmp);
        tmp2 = tmp2->GetNextDatLink();
    }

    return res;
}

TPolinom& TPolinom::operator-=(const TPolinom& q)
{
    *this = *this - q;

    return *this;
}

std::ostream& operator<<(std::ostream& ostr, TPolinom& q)
{
    return ostr << q.ToString();
}

TPolinom TPolinom::Integrate() const {
    TPolinom res(countVar);
    TDatLink<TMonom>* tmp = pFirst;
    while (tmp != pHead) {
        const TMonom* monom = tmp->GetDatValue();
        TMonom integrate_monom = monom->Integrate_Monom();
        res.AddMonom(integrate_monom);
        tmp = tmp->GetNextDatLink();
    }
    return res;
}

#endif
