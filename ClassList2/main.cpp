#include<iostream>

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
			std::cout << "EConstructor:\t" << this << std::endl;
		}
		~Element(){std::cout << "EDistructor:\t" << this << std::endl;}
	};
};

void main()
{
	setlocale(LC_ALL, "");

}