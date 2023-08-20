#include <iostream>
#define delimitr "\n-----------------------------------------------------\n"
class DoublyList;
DoublyList operator+(const DoublyList& left, const DoublyList& right);
class Iterator;
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
	friend DoublyList operator+(const DoublyList& left, const DoublyList& right);
	friend class Iterator;
};
class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) : Temp(Temp)
	{
		std::cout << "ITConstructor:\t" << this << std::endl;
	}
	~Iterator()
	{
		std::cout << "ITDestructor:\t" << this << std::endl;
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator& operator--()
	{
		Temp = Temp->pPrev;
		return *this;
	}
	bool operator==(const Iterator& other) const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other) const
	{
		return this->Temp != other.Temp;
	}
	int operator*()
	{
		return Temp->Data;
	}
};

class DoublyList
{	
	int count = 0; //Завел счетчик для уменьшения кол-во итераций в методах - вставлять по индексу и удалять по индексу
				   // Я прикинул, что прохождение по всему списку для поиска кол-ва значений не рентабельно - т.к. значений может быть 1000+
	Element* Head;
	Element* Tail;

public:
	//							Constructor's
	DoublyList()
	{
		Head = nullptr; //Если список пуст то его голова указывает на 0
		Tail = nullptr; //Если список пуст то его хвост указывает на 0
		std:: cout << "DConstructor:\t" << this << std::endl;
	}
	DoublyList(const std::initializer_list<int> arr)
	{
		for (int i : arr)push_back(i);
		std::cout << "1ArgConstructor:\t" << this << std::endl;
	}
	DoublyList(const DoublyList& other) :DoublyList()
	{
		std::cout << "DCopyConstructor:\t" << this << std::endl;
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
		count = other.count;
	}
	DoublyList(DoublyList&& other) :DoublyList()
	{
		std::cout << "DMoveConstructor:\t" << this << std::endl;
		Head = other.Head;
		other.Head = nullptr;
		Tail = other.Tail;
		other.Tail = nullptr;
		count = other.count;
	}
	~DoublyList()
	{
		while (Head)pop_front();
			count = 0;
			std::cout << "DDistructor:\t" << this << std::endl;
	}
	//								Operator's
	DoublyList& operator=(const DoublyList& other)
	{
		std::cout << "DCopyAssignment:\t" << this << std::endl;
		while (Head)pop_front();
		Head = nullptr;
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
		return *this;
		count = other.count;
	}
	DoublyList& operator=(DoublyList&& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		Head = other.Head;
		other.Head = nullptr;
		Tail = other.Tail;
		other.Tail = nullptr;
		std::cout << "DMoveConstructor:\t" << this << std::endl;
		count = other.count;
		return *this;
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
		count++;
	}
	void push_back(int Data)
	{
		Element* Temp;
		Temp = new Element(Data, Tail, nullptr);
		if (Tail) Tail->pNext = Temp;
		Tail = Temp;
		if (!this->Tail->pPrev) Head = Tail;
		count++;
	}
	void pop_front()
	{
		Element* Temp = Head->pNext;
		delete Head;
		Head = Temp;
		if(Head)Head->pPrev = nullptr;
		count--;
	}
	void pop_back()
	{
		Element* Temp = Tail->pPrev;
		delete Tail;
		Tail = Temp;
		Tail->pNext = nullptr;
		count--;
	}
	void insert(int index, int Data)
	{
		if (index == 0) return push_front(Data);
		if (index >= count) return push_back(Data);
		if (index <= count / 2)
		{
			Element* Temp = Head;
			for (int i = 0; i < index - 1; i++) Temp = Temp->pNext;
			Temp->pNext = new Element(Data, Temp, Temp->pNext);
			Temp->pNext->pNext->pPrev = Temp->pNext;
		}
		else
		{
			Element* Temp = Tail;
			for (int i = count; i > index + 1; i--) Temp = Temp->pPrev;
			Temp->pPrev = new Element(Data, Temp->pPrev, Temp);
			Temp->pPrev->pPrev->pNext = Temp->pPrev;
		}
		count++;
	}
	void erase(int index)
	{
		if (index == 0) return pop_front();
		if (index >= count - 1) return pop_back();
		if (index <= count / 2)
		{
			Element* Temp = Head;
			for (int i = 0; i < index - 1; i++) Temp = Temp->pNext;
			Temp->pNext->pNext->pPrev = Temp;
			Element* New = Temp->pNext;
			Temp->pNext = Temp->pNext->pNext;
			delete New;
		}
		else
		{
			Element* Temp = Tail;
			for (int i = count; i > index + 2; i--) Temp = Temp->pPrev;
			Temp->pPrev->pPrev->pNext = Temp;
			Element* New = Temp->pPrev;
			Temp->pPrev = Temp->pPrev->pPrev;
			delete New;
		}
		count--;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	void print() const
	{
		std::cout << "Head:\t" << Head << std::endl;
		std::cout << "Tail:\t" << Tail << std::endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext) if(Temp)std::cout << Temp->Data << " " << std::endl;
		std::cout << "size list:\t" << count << std::endl;
		std::cout << std::endl;
		//std::cout << "Begin: \t" << Head << "\t" << Head->Data << std::endl;
		//std::cout << "End: \t" << Tail << "\t" << Tail->Data << std::endl;
	}
	void print_end() const //Сделал для проверки Tail & pPrev
	{
		std::cout << "Head:\t" << Head << std::endl;
		std::cout << "Tail:\t" << Tail << std::endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev) if(Temp)std::cout << Temp->Data << " " << std::endl;
		std::cout << "size list:\t" << count << std::endl;
		std::cout << std::endl;
	}
	friend DoublyList operator+(const DoublyList& left, const DoublyList& right);
	friend class Iterator;
};
DoublyList operator+(const DoublyList& left, const DoublyList& right)
{
	DoublyList cat = left;
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext) cat.push_back(Temp->Data);
	return cat;
}

//#define CHEK_PUSH_FRONT
//#define CHEK_FUNCTIONS
//#define CHEK_COPY_METHODS
//#define CHEK_MOVE_METODS
#define CHEK_INITIALIZER_LIST
void main()
{
	setlocale(LC_ALL, "");
	//int size;
	//std::cout << "Enter size you list: "; std::cin >> size;
	//DoublyList list;
	//for (int i = 0; i < size; i++)list.push_back(rand() % 100);
	//list.print();
	//list.print_end(); //Проверка обратного выведения
#ifdef CHEK_PUSH_FRONT
	for (int i = 0; i < size; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	std::cout << delimitr << std::endl;
	list.print_end();

#endif // CHEK_PUSH_FRONT
#ifdef CHEK_FUNCTIONS
	list.print();
	/*std::cout << delimitr << std::endl;
	list.print_end();*/
	std::cout << delimitr << std::endl;
	std::cout << "Pop front: " << std::endl;
	list.pop_front();
	list.print();
	list.print_end();
	std::cout << delimitr << std::endl;
	std::cout << "Pop back:" << std::endl;
	list.pop_back();
	list.print();
	list.print_end();
	std::cout << delimitr << std::endl;
	std::cout << "Insert:" << std::endl;
	list.insert(4, 321);
	list.print();
	list.print_end();
	std::cout << delimitr << std::endl;
	std::cout << "Erase:" << std::endl;
	list.erase(0);
	list.print();
	list.print_end();
#endif // CHEK_FUNCTIONS
#ifdef CHEK_COPY_METHODS
	std::cout << delimitr << std::endl;
	std::cout << "CopyConstructor:" << std::endl;
	DoublyList list1 = list;
	list1.print();
	list1.print_end();
	std::cout << delimitr << std::endl;
	std::cout << "CopyAssignment:" << std::endl;
	DoublyList list2;
	list2 = list;
	list2.print();
	list2.print_end();

#endif // CHEK_COPY_METHODS
#ifdef CHEK_MOVE_METODS
	DoublyList list2;
	for (int i = 0; i < size + 2; i++)list2.push_back(rand() % 100);
	list2.print();
	std::cout << delimitr << std::endl;
	std::cout << "MoveConstructor:" << std::endl;
	DoublyList list3 = list + list2;
	//std::cout << delimitr << std::endl;
	list3.print();
	std::cout << delimitr << std::endl;
	std::cout << "MoveAssignment:" << std::endl;
	DoublyList list4;
	list4 = list + list2;
	list4.print();

#endif // CHEK_MOVE_METODS
#ifdef CHEK_INITIALIZER_LIST
	DoublyList list = { 3, 5, 8, 13, 21 };
	list.print();
	list.print_end();

	for (int i : list) std::cout << i << "\t"; std::cout << std::endl;
	std::cout << std::endl;
#endif // CHEK_INITIALIZER_LIST

}