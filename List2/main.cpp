#include <iostream>
#define delimiter "\n-----------------------------------------------------\n"
class List;
List operator+(const List& left, const List& right);
//std::ostream& operator<<(std::ostream& out, const Iterator& obj);
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
	friend class List;
	friend List operator+(const List& left, const List& right);
	//friend std::ostream& operator<<(std::ostream& out, const Iterator& obj);
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
	explicit operator int()
	{
		return Temp->Data;
	}
	//friend std::ostream& operator<<(std::ostream& out, const Iterator& obj);
};

class List
{	
	int size = 0; //Завел счетчик для уменьшения кол-во итераций в методах - вставлять по индексу и удалять по индексу
				   // Я прикинул, что прохождение по всему списку для поиска кол-ва значений не рентабельно - т.к. значений может быть 1000+
	Element* Head;
	Element* Tail;

public:
	//							Constructor's
	List()
	{
		Head = nullptr; //Если список пуст то его голова указывает на 0
		Tail = nullptr; //Если список пуст то его хвост указывает на 0
		std:: cout << "DConstructor:\t" << this << std::endl;
	}
	List(const std::initializer_list<int> arr)
	{
		for (int i : arr)push_back(i);
		std::cout << "1ArgConstructor:\t" << this << std::endl;
	}
	List(const List& other) :List()
	{
		std::cout << "DCopyConstructor:\t" << this << std::endl;
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
		size = other.size;
	}
	List(List&& other) :List()
	{
		std::cout << "DMoveConstructor:\t" << this << std::endl;
		Head = other.Head;
		other.Head = nullptr;
		Tail = other.Tail;
		other.Tail = nullptr;
		size = other.size;
	}
	~List()
	{
		while (Head)pop_front();
			size = 0;
			std::cout << "DDistructor:\t" << this << std::endl;
	}
	//								Operator's
	List& operator=(const List& other)
	{
		std::cout << "DCopyAssignment:\t" << this << std::endl;
		while (Head)pop_front();
		Head = nullptr;
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
		return *this;
		size = other.size;
	}
	List& operator=(List&& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		Head = other.Head;
		other.Head = nullptr;
		Tail = other.Tail;
		other.Tail = nullptr;
		std::cout << "DMoveConstructor:\t" << this << std::endl;
		size = other.size;
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
		size++;
	}
	void push_back(int Data)
	{
		Element* Temp;
		Temp = new Element(Data, Tail, nullptr);
		if (Tail) Tail->pNext = Temp;
		Tail = Temp;
		if (!this->Tail->pPrev) Head = Tail;
		size++;
	}
	void pop_front()
	{
		Element* Temp = Head->pNext;
		delete Head;
		Head = Temp;
		if(Head)Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		Element* Temp = Tail->pPrev;
		delete Tail;
		Tail = Temp;
		Tail->pNext = nullptr;
		size--;
	}
	void insert(int index, int Data)
	{
		if (index == 0) return push_front(Data);
		if (index >= size) return push_back(Data);
		if (index <= size / 2)
		{
			Element* Temp = Head;
			for (int i = 0; i < index - 1; i++) Temp = Temp->pNext;
			Temp->pNext = new Element(Data, Temp, Temp->pNext);
			Temp->pNext->pNext->pPrev = Temp->pNext;
		}
		else
		{
			Element* Temp = Tail;
			for (int i = size; i > index + 1; i--) Temp = Temp->pPrev;
			Temp->pPrev = new Element(Data, Temp->pPrev, Temp);
			Temp->pPrev->pPrev->pNext = Temp->pPrev;
		}
		size++;
	}
	void erase(int index)
	{
		if (index == 0) return pop_front();
		if (index >= size - 1) return pop_back();
		if (index <= size / 2)
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
			for (int i = size; i > index + 2; i--) Temp = Temp->pPrev;
			Temp->pPrev->pPrev->pNext = Temp;
			Element* New = Temp->pPrev;
			Temp->pPrev = Temp->pPrev->pPrev;
			delete New;
		}
		size--;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	Iterator ended()
	{
		return Tail;
	}
	void print() const
	{
		std::cout << "Head:\t" << Head << std::endl;
		std::cout << "Tail:\t" << Tail << std::endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext) if(Temp)std::cout << Temp->Data << " " << std::endl;
		std::cout << "size list:\t" << size << std::endl;
		std::cout << std::endl;
		//std::cout << "Begin: \t" << Head << "\t" << Head->Data << std::endl;
		//std::cout << "End: \t" << Tail << "\t" << Tail->Data << std::endl;
	}
	void reverse_print() const //Сделал для проверки Tail & pPrev
	{
		std::cout << "Head:\t" << Head << std::endl;
		std::cout << "Tail:\t" << Tail << std::endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev) if(Temp)std::cout << Temp->Data << " " << std::endl;
		std::cout << "size list:\t" << size << std::endl;
		std::cout << std::endl;
	}
	friend List operator+(const List& left, const List& right);
	friend class Iterator;
};
List operator+(const List& left, const List& right)
{
	List cat = left;
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext) cat.push_back(Temp->Data);
	return cat;
}
//std::ostream& operator<<(std::ostream& out, const Iterator& obj)
//{
//	return out << obj->Temp->Data;
//}

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
	//List list;
	//for (int i = 0; i < size; i++)list.push_back(rand() % 100);
	//list.print();
	//list.print_end(); //Проверка обратного выведения
#ifdef CHEK_PUSH_FRONT
	for (int i = 0; i < size; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	std::cout << delimiter << std::endl;
	list.reverse();

#endif // CHEK_PUSH_FRONT
#ifdef CHEK_FUNCTIONS
	list.print();
	/*std::cout << delimiter << std::endl;
	list.print_end();*/
	std::cout << delimiter << std::endl;
	std::cout << "Pop front: " << std::endl;
	list.pop_front();
	list.print();
	list.reverse();
	std::cout << delimiter << std::endl;
	std::cout << "Pop back:" << std::endl;
	list.pop_back();
	list.print();
	list.reverse();
	std::cout << delimiter << std::endl;
	std::cout << "Insert:" << std::endl;
	list.insert(4, 321);
	list.print();
	list.reverse();
	std::cout << delimiter << std::endl;
	std::cout << "Erase:" << std::endl;
	list.erase(0);
	list.print();
	list.reverse();
#endif // CHEK_FUNCTIONS
#ifdef CHEK_COPY_METHODS
	std::cout << delimiter << std::endl;
	std::cout << "CopyConstructor:" << std::endl;
	List list1 = list;
	list1.print();
	list1.reverse();
	std::cout << delimiter << std::endl;
	std::cout << "CopyAssignment:" << std::endl;
	List list2;
	list2 = list;
	list2.print();
	list2.reverse();

#endif // CHEK_COPY_METHODS
#ifdef CHEK_MOVE_METODS
	List list2;
	for (int i = 0; i < size + 2; i++)list2.push_back(rand() % 100);
	list2.print();
	std::cout << delimiter << std::endl;
	std::cout << "MoveConstructor:" << std::endl;
	List list3 = list + list2;
	//std::cout << delimiter << std::endl;
	list3.print();
	std::cout << delimiter << std::endl;
	std::cout << "MoveAssignment:" << std::endl;
	List list4;
	list4 = list + list2;
	list4.print();

#endif // CHEK_MOVE_METODS
#ifdef CHEK_INITIALIZER_LIST
	List list = { 3, 5, 8, 13, 21 };
	//list.print();
	//list.reverse_print();

	for (int i : list) std::cout << i << "\t"; std::cout << std::endl;
	std::cout << std::endl;
	std::cout << delimiter << std::endl;
	for (Iterator it = list.ended(); it != 0; --it) std::cout << (int)it << "\t"; std::cout << std::endl;
#endif // CHEK_INITIALIZER_LIST

}