#include "ListOfOA.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												Element methods																//

template<typename T> ListSeparation::List<T>::Element::Element(T Data, Element* pNext, Element* pPrev) :Data(Data), pNext(pNext), pPrev(pPrev)
{
#ifdef DEBUG
	cout << "ECostructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T> ListSeparation::List<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

}

//												Element methods																//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------------------------------------//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//										ConstBaseIterator methods																//

template<typename T> ListSeparation::List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) :Temp(Temp)
{
#ifdef DEBUG
	cout << "BItConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T> ListSeparation::List<T>::ConstBaseIterator::~ConstBaseIterator()
{
#ifdef DEBUG
	cout << "BItDestructor:\t" << this << endl;
#endif // DEBUG

}

template<typename T> bool ListSeparation::List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T> bool ListSeparation::List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T> const T& ListSeparation::List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}

//										ConstBaseIterator methods																//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------------------------------------//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												ConstIterator methods																//

template<typename T> ListSeparation::List<T>::ConstIterator::ConstIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T> ListSeparation::List<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
}

template<typename T> typename ListSeparation::List<T>::ConstIterator& ListSeparation::List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T> typename ListSeparation::List<T>::ConstIterator ListSeparation::List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T> typename ListSeparation::List<T>::ConstIterator& ListSeparation::List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename ListSeparation::List<T>::ConstIterator ListSeparation::List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}

template <typename T>typename ListSeparation::List<T>::ConstIterator ListSeparation::List<T>::cbegin()const
{
	return Head;
}
template<typename T> typename ListSeparation::List<T>::ConstIterator ListSeparation::List<T>::cend()const
{
	return nullptr;
}

//												ConstIterator methods																//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------------------------------------//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//									      ConstReverseIterator methods														//

template<typename T> ListSeparation::List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T> ListSeparation::List<T>::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
	cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T> typename ListSeparation::List<T>::ConstReverseIterator& ListSeparation::List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename ListSeparation::List<T>::ConstReverseIterator ListSeparation::List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T> typename ListSeparation::List<T>::ConstReverseIterator& ListSeparation::List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T> typename ListSeparation::List<T>::ConstReverseIterator& ListSeparation::List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T> typename ListSeparation::List<T>::ConstReverseIterator ListSeparation::List<T>::crbegin()const
{
	return Tail;
}
template<typename T> typename ListSeparation::List<T>::ConstReverseIterator ListSeparation::List<T>::crend()const
{
	return nullptr;
}

//									      ConstReverseIterator methods														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------------------------------------//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												Iterator methods															//

template<typename T> ListSeparation::List<T>::Iterator::Iterator(Element* Temp) :ConstIterator(Temp) {}
template<typename T> T& ListSeparation::List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

template<typename T> typename ListSeparation::List<T>::Iterator ListSeparation::List<T>::begin()
{
	return Head;
}
template<typename T> typename ListSeparation::List<T>::Iterator ListSeparation::List<T>::end()
{
	return nullptr;
}

//												Iterator methods															//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------------------------------------//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												ReverseIterator methods														//

template<typename T> ListSeparation::List<T>::ReverseIterator::ReverseIterator(Element* Temp) :ConstReverseIterator(Temp) {}
template<typename T> T& ListSeparation::List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

template<typename T> typename ListSeparation::List<T>::ReverseIterator ListSeparation::List<T>::rbegin()
{
	return Tail;
}
template<typename T> typename ListSeparation::List<T>::ReverseIterator ListSeparation::List<T>::rend()
{
	return nullptr;
}

//												ReverseIterator methods														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------------------------------------//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												List methods																//

template<typename T> ListSeparation::List<T>::List()
{
	Head = Tail = nullptr;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T> ListSeparation::List<T>::List(const  std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
	{
		push_back(*it);
	}
}
template <typename T> ListSeparation::List<T>::List(const ListSeparation::List<T>& other) :List()
{
	*this = other;
}
template <typename T> ListSeparation::List<T>::~List()
{
	//while (Head)pop_front();
	while (Tail)pop_back();
	cout << "LDestructor:\t" << this << endl;
}
template<typename T> ListSeparation::List<T>& ListSeparation::List<T>::operator=(const ListSeparation::List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	cout << "LCopyAssignment:\t" << this << endl;
	return *this;
}
template<typename T> void ListSeparation::List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)	Head = Tail = new Element(Data);
	else Head = Head->pPrev = new Element(Data, Head);
	size++;
}
template<typename T> void ListSeparation::List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)Head = Tail = new Element(Data);
	else Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}
template<typename T> void ListSeparation::List<T>::insert(T Data, int Index)
{
	if (Index == 0)return push_front(Data);
	if (Index >= size)return push_back(Data);
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
	}
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	size++;
}
template<typename T> void ListSeparation::List<T>::pop_front()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		return;
	}
	Head = Head->pNext;
	delete Head->pPrev;
	Head->pPrev = nullptr;
	size--;
}
template<typename T> void ListSeparation::List<T>::pop_back()
{
	if (Head == Tail)return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
template<typename T> void ListSeparation::List<T>::erase(int Index)
{
	if (Index == 0)return pop_front();
	if (Index >= size)return;
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
	}
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	delete Temp;
}
template<typename T> void ListSeparation::List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
}
template<typename T> void ListSeparation::List<T>::reverse_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
}
template <typename T>ListSeparation::List<T> operator+(const ListSeparation::List<T>& left, const ListSeparation::List<T>& right)
{
	ListSeparation::List<T> cat = left;
	for (typename ListSeparation::List<T>::ConstIterator it = right.cbegin(); it != right.cend(); ++it)
	{
		//(*it) *= 10;
		cat.push_back(*it);
	}
	return cat;
}
//												List methods																//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
