#ifndef _POLINOM_LIB_TDATLIST_
#define _POLINOM_LIB_TDATLIST_

#include <exception>
#include "DatLink.h"
#include "RootLink.h"

template<class T>
class TDatList {
protected:
    TDatLink<T>* pFirst; // первое звено
    TDatLink<T>* pLast; // последнее звено
    TDatLink<T>* pCurrLink; // текущее звено
    TDatLink<T>* pPrevLink; // звено перед текущим
    TDatLink<T>* pStop; // значение указателя, означающего конец списка
    int CurrPos; // номер текущего звена (нумерация от 0)
    int ListLen; // количество звеньев в списке
protected: // методы
    //TDatLink* GetLink(T* pVal = NULL, TDatLink* pLink = NULL);
    void DelLink(const TDatLink<T>* pLink); // удаление звена
public:
    TDatList();
    TDatList(const TDatList<T>& q);
    ~TDatList(void) { DelList(); }
    // доступ
    T* GetDatValue(const int pos) const; // значение
    T* GetDatValue(void) const { return GetDatValue(CurrPos); } // значение
    virtual int IsEmpty(void) const { return pFirst == pStop; } // список пуст ?
    int GetLength(void) const { return ListLen; } // к-во звеньев
    TDatLink<T>* GetFirst(void) const { return pFirst; }
    TDatLink<T>* GetLast(void) const { return pLast; }
    // навигация
    int SetCurrentPos(const int pos); // установить текущее звено
    int GetCurrentPos(void) const { return CurrPos; } // получить номер тек. звена
    virtual int Reset(void); // установить на начало списка
    virtual int IsListEnded(void) const; // список завершен ?
    virtual int GoNext(void); // сдвиг вправо текущего звена
    // (=1 после применения GoNext для последнего звена списка)
    // вставка звеньев
    virtual void InsFirst(T* pVal = NULL); // перед первым
    virtual void InsLast(T* pVal = NULL); // вставить последним
    virtual void InsCurrent(T* pVal = NULL); // перед текущим
    // удаление звеньев
    virtual void DelFirst(void); // удалить первое звено
    virtual void DelCurrent(void); // удалить текущее звено
    virtual void DelList(void); // удалить весь список
    TDatList<T>& operator=(const TDatList<T>& q);
};

#include "../src/DatList.hpp"

#endif
