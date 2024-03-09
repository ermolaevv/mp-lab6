//TDatLink* TDatList::GetLink(T* pVal, TDatLink* pLink)
//{
//	return TDatLink*();
//}
template<class T>
void TDatList<T>::DelLink(const TDatLink<T>* pLink)
{
	TDatLink<T>* ptr = pFirst;
	TDatLink<T>* pre_ptr = NULL;
	
	while (ptr->pNext != pStop && ptr != pLink)
		pre_ptr = ptr;
		ptr = ptr->GetNextDatLink();

	if (ptr->pNext == pStop && ptr != pLink) {
		throw std::exception("Element not found");
	}

	if (pre_ptr != NULL) {
		pre_ptr->pNext = ptr->GetNextLink();
	}

	delete ptr;
	ListLen--;
}

template<class T>
TDatList<T>::TDatList()
{
	pFirst = NULL;
	pLast = NULL;
	pPrevLink = NULL;
	pCurrLink = NULL;
	pStop = new TDatLink<T>();
	CurrPos = NULL;
	ListLen = 0;
}

template<class T>
TDatList<T>::TDatList(const TDatList& q)
{
	ListLen = q.ListLen;

	pFirst = q.pFirst->GetCopy(q.pFirst->GetNextDatLink());
	pStop = q.pStop->GetCopy();
	pCurrLink = pFirst;

	for (size_t i = 0; i < ListLen - 1; i++) {
		pPrevLink = pCurrLink;
		pCurrLink = pCurrLink->GetNextDatLink();
		pCurrLink = pCurrLink->GetCopy(pCurrLink->GetNextDatLink());
		pPrevLink->SetNextLink(pCurrLink);
	}

	pLast = pCurrLink;
	pLast->SetNextLink(pStop);
	SetCurrentPos(q.CurrPos);
}

template<class T>
T* TDatList<T>::GetDatValue(int pos) const
{
	if (pos >= ListLen)
		return NULL;
	if (pos == CurrPos)
		return pCurrLink->GetDatValue();
	
	TDatLink<T>* ptr = pFirst;
	for (int i = 0; i < pos; i++)
		ptr = ptr->GetNextDatLink();
	return ptr->GetDatValue();
}

template<class T>
int TDatList<T>::SetCurrentPos(int pos)
{
	if (pos < 0 || pos >= ListLen)
		throw std::exception("Wrong index");
	pCurrLink = pFirst;
	pPrevLink = NULL;
	CurrPos = 0;

	while (CurrPos < pos) {
		pPrevLink = pCurrLink;
		pCurrLink = pCurrLink->GetNextDatLink();
		CurrPos++;
	}
	
	return CurrPos;
}

template<class T>
int TDatList<T>::Reset(void)
{
	pCurrLink = pFirst;
	pPrevLink = NULL;
	CurrPos = 0;
	return CurrPos;
}

template<class T>
int TDatList<T>::IsListEnded(void) const
{
	return pCurrLink->pNext == pStop;
}

template<class T>
int TDatList<T>::GoNext(void)
{
	if (IsListEnded()) {
		throw std::exception("List is ended");
	}

	pPrevLink = pCurrLink;
	pCurrLink = pCurrLink->GetNextDatLink();
	CurrPos = ++CurrPos % ListLen;
	return CurrPos;
}

template<class T>
void TDatList<T>::InsFirst(T* pVal)
{
	if (pFirst == NULL && ListLen == 0) {
		pFirst = new TDatLink<T>(pVal, pStop);
		pLast = pCurrLink = pFirst;
	}
	else {
		TDatLink<T>* tmp = pFirst;
		pFirst = new TDatLink<T>(pVal);
		pFirst->pNext = tmp;
		SetCurrentPos(CurrPos);
	}
	ListLen++;
}

template<class T>
void TDatList<T>::InsLast(T* pVal)
{
	TDatLink<T>* tmp = new TDatLink<T>(pVal, pStop);
	if (pFirst == NULL && ListLen == 0) {
		pFirst = tmp;
		pLast = pCurrLink = pFirst;
	}
	else {
		pLast->InsNextLink(tmp);
		pLast = tmp;
	}
	ListLen++;
}

template<class T>
void TDatList<T>::InsCurrent(T* pVal)
{
	TDatLink<T>* tmp = new TDatLink<T>(pVal);
	if (pFirst == NULL && ListLen == 0) {
		pFirst = new TDatLink<T>(pVal, pStop);
		pLast = pCurrLink = pFirst;
	}
	else {
		if (pCurrLink->pNext == pStop) {
			pLast = tmp;
		}
		pCurrLink->InsNextLink(tmp);
	}
	ListLen++;
}

template<class T>
void TDatList<T>::DelFirst(void)
{
	if (pFirst != NULL) {
		TDatLink<T>* prev = pFirst;
		pFirst = (TDatLink<T>*)pFirst->GetNextLink();
		if (pCurrLink == prev)
			pCurrLink = pFirst;
		delete prev;
		prev = NULL;
		ListLen--;
	}
}

template<class T>
void TDatList<T>::DelCurrent(void)
{
	if (pCurrLink != NULL) {
		TDatLink<T>* prev = pCurrLink;
		pFirst = (TDatLink<T>*)pCurrLink->GetNextLink();
		delete prev;
		ListLen--;
	}
}

template<class T>
void TDatList<T>::DelList(void)
{
	TDatLink<T>* prev = pFirst;
	while (ListLen > 0) {
		DelFirst();
	}
	if (pStop != NULL)
	{
		delete pStop;
		pStop = NULL;
	}
	ListLen = 0;
}

template<class T>
TDatList<T>& TDatList<T>::operator=(const TDatList& q)
{
	if (this == &q) {
		return *this;
	}
	if (pFirst != NULL)
		DelList();
    if (q.pFirst == NULL)
        return *this;
	ListLen = q.ListLen;

	pFirst = q.pFirst->GetCopy(q.pFirst->GetNextDatLink());
	pStop = q.pStop->GetCopy();
	pCurrLink = pFirst;

	for (size_t i = 0; i < ListLen - 1; i++) {
		pPrevLink = pCurrLink;
		pCurrLink = pCurrLink->GetNextDatLink();
		pCurrLink = pCurrLink->GetCopy(pCurrLink->GetNextDatLink());
		pPrevLink->SetNextLink(pCurrLink);
	}

	pLast = pCurrLink;
	pLast->SetNextLink(pStop);
	SetCurrentPos(q.CurrPos);

	return *this;
}
