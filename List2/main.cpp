﻿#include <iostream>
#define delimitr "\n-----------------------------------------------------\n"
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
	void push_front(int Data)
	{
		Element* Temp; //Завожу дополнительную переменную Temp для того, чтобы прописывать pPrev
		Temp = new Element(Data, nullptr, Head);
		if (Head) Head->pPrev = Temp;
		//if(Head)std::cout << "pPrev: \t" << Head->pPrev << std::endl; //сделал чтобы смотреть как записываются адреса
		Head = Temp;
		if (!this->Head->pNext) Tail = Head;
		//std::cout << "Head: \t" << Head << std::endl;
		//std::cout << "Tail: \t" << Tail << std::endl;
		//std::cout << "pNext: \t" << Head->pNext << std::endl;
	}
	void push_back(int Data)
	{
		Element* Temp;
		Temp = new Element(Data, Tail, nullptr);
		if (Tail) Tail->pNext = Temp;
		Tail = Temp;
		if (!this->Tail->pPrev) Head = Tail;
	}
	void pop_front()
	{
		Element* Temp = Head->pNext;
		delete Head;
		Head = Temp;
		Head->pPrev = nullptr;
	}
	void pop_back()
	{
		Element* Temp = Tail->pPrev;
		delete Tail;
		Tail = Temp;
		Tail->pNext = nullptr;
	}
	void print() const
	{
		std::cout << "Head:\t" << Head << std::endl;
		std::cout << "Tail:\t" << Tail << std::endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext) if(Temp)std::cout << Temp->Data << " " << std::endl;
		std::cout << std::endl;
		//std::cout << "Begin: \t" << Head << "\t" << Head->Data << std::endl;
		//std::cout << "End: \t" << Tail << "\t" << Tail->Data << std::endl;
	}
	void print_end() const //Сделал для проверки Tail & pPrev
	{
		std::cout << "Head:\t" << Head << std::endl;
		std::cout << "Tail:\t" << Tail << std::endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev) if(Temp)std::cout << Temp->Data << " " << std::endl;
		std::cout << std::endl;
	}
};

//#define CHEK_PUSH_FRONT
#define CHEK_PUSH_BACK
void main()
{
	setlocale(LC_ALL, "");
	int size;
	std::cout << "Enter size you list: "; std::cin >> size;
	DoublyList list;
#ifdef CHEK_PUSH_FRONT
	for (int i = 0; i < size; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	std::cout << delimitr << std::endl;
	list.print_end();

#endif // CHEK_PUSH_FRONT
	for (int i = 0; i < size; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	/*std::cout << delimitr << std::endl;
	list.print_end();*/
	std::cout << delimitr << std::endl;
	std::cout << "Pop front: " << std::endl;
	list.pop_front();
	list.print();
	std::cout << delimitr << std::endl;
	std::cout << "Pop back:" << std::endl;
	list.pop_back();
	list.print();
}