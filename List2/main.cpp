#include <iostream>

class DoublyList;
class Element
{
	int Data;
	Element* pNext;
	Element* pPrev;

public:
	Element(int Data, Element* pPrev = nullptr, Element* pNext = nullptr): Data(Data), pPrev(pPrev), pNext(pNext)
	{
		std::cout << "EConstructor:\t" << this << std::endl;
	}

	~Element()
	{
		std::cout << "EDistructor:\t" << this << std::endl;
	}
	friend class DoublyList;
};

class DoublyList
{
	Element* Head;
	Element* Tail;

public:
	DoublyList()
	{
		Head = nullptr; //Если список пуст то его голова указывает на 0
		Tail = nullptr; //Если список пуст то его хвост указывает на 0
		std:: cout << "DConstructor:\t" << this << std::endl;
	}
	~DoublyList()
	{
		std::cout << "DDistructor:\t" << this << std::endl;
	}
	//								Method's
	void print() const
	{
		std::cout << "Head:\t" << Head << std::endl;
		std::cout << "Tail:\t" << Tail << std::endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext) std::cout << Temp->Data << " " << std::endl;
		std::cout << std::endl;
	}
};

#define START_DOUBLY_LIST
void main()
{
	setlocale(LC_ALL, "");
#ifdef START_DOUBLY_LIST


#endif // START_DOUBLY_LIST


}