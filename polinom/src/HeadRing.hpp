template<class T>
THeadRing<T>::THeadRing()
{
	pHead = new TDatLink<T>();
}

template<class T>
THeadRing<T>::THeadRing(const THeadRing<T>& q) : TDatList<T>(q)
{
	this->pHead = q.pHead->GetCopy();
	this->pHead->SetNextLink(this->pFirst);
	this->pLast->SetNextLink(this->pHead);
}

template<class T>
THeadRing<T>::~THeadRing()
{
	delete this->pHead;
}

template<class T>
void THeadRing<T>::InsFirst(T* pVal)
{
	TDatList<T>::InsFirst(pVal);
	this->pHead->SetNextLink(this->pFirst);
	this->pLast->SetNextLink(this->pHead);
}

template<class T>
void THeadRing<T>::DelFirst(void)
{
	TDatList<T>::DelFirst();
	this->pHead->SetNextLink(this->pFirst);
	this->pLast->SetNextLink(this->pHead);

}

template<class T>
int THeadRing<T>::GoNext(void)
{
	if (this->pCurrLink->GetNextDatLink() == this->pHead) {
		this->pCurrLink = this->pHead;
	}
	return TDatList<T>::GoNext();
}

template<class T>
void THeadRing<T>::InsCurrent(T* pVal)
{
	if (this->pCurrLink != NULL && this->pCurrLink->GetNextDatLink() == pHead) {
		this->pCurrLink->InsNextLink(new TDatLink<T>(pVal));
		this->ListLen++;
	}
	else
		TDatList<T>::InsCurrent(pVal);
	if (this->ListLen == 1)
		this->pHead->SetNextLink(this->pFirst);
}

template<class T>
void THeadRing<T>::InsLast(T* pVal)
{
	TDatList<T>::InsLast(pVal);
	this->pLast->SetNextLink(this->pHead);
	if (this->ListLen == 1)
		this->pHead->SetNextLink(this->pFirst);
}

template<class T>
void THeadRing<T>::DelList(void)
{
	TDatList<T>::DelList();
	if (pHead != NULL) {
		delete this->pHead;
		this->pHead = NULL;
	}
}

template<class T>
THeadRing<T>& THeadRing<T>::operator=(const THeadRing<T>& q)
{
	DelList();

	TDatList<T>::operator=(q);

	this->pHead = q.pHead->GetCopy();
    if (q.pFirst != NULL) {
	    this->pHead->SetNextLink(this->pFirst);
	    this->pLast->SetNextLink(this->pHead);
    }

	return *this;
}
