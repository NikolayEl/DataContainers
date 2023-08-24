#include<iostream>
#define tab "\t"
#define delimitr "\n------------------------------------------------\n"
class ReverseIterator;
class List;
List operator+(const List& left, const List& right);
class Iterator;
class Element;
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
		~Element(){std::cout << "EDestructor:\t" << this << std::endl;}
		friend class List;
		friend List operator+(const List& left, const List& right);
	}*Head, *Tail;
public:
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
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		bool operator==(const Iterator& other) const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other) const
		{
			return this->Temp != other.Temp;
		}
		int& operator*()
		{
			return Temp->Data;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}

		explicit operator int()
		{
			return this->Temp->Data;
		}
	};
public:
	class ReverseIterator
	{
		Element* Temp;
	public:
		ReverseIterator(Element* Temp = nullptr) : Temp(Temp)
		{
			std::cout << "RITConstructor:\t" << this << std::endl;
		}
		~ReverseIterator()
		{
			std::cout << "RITDestructor:\t" << this << std::endl;
		}
		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		bool operator==(const ReverseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*() const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	unsigned int size;
public:
	List()
	{
		Head = Tail = nullptr;
		std::cout << "ElConstructor:\t" << this << std::endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it) push_back(*it);
		std::cout << "1ArgConstructor:\t" << this << std::endl;
	}
	~List()
	{
		//while (Head)pop_front(); //Проверяли pop_front
		while (Tail)pop_back(); //Проверяем pop_back
		std::cout << "ElDestructor:\t" << this << std::endl;
	}
	List(const List& other) :List()
	{
		std::cout << "DCopyConstructor:\t" << this << std::endl;
		//for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
		size = other.size;
		*this = other;
	}
	//						Operators
	
	List& operator=(const List& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		Head = nullptr;
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
		std::cout << "LCopyAssignment:\t" << this << std::endl;
		size = other.size;
		return *this;
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


	//						Adding Elements
	void push_front(int Data)
	{
		if (!Head && !Tail) Head = Tail = new Element(Data);
		else Head = Head->pPrev = new Element(Data, Head); //круто!! Справа налево, поэтому все грамотно получается
		size++;
	}
	void push_back(int Data)
	{
		if (!Head && !Tail) Head = Tail = new Element(Data);
		else Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}

	void insert(int Data, int Index)
	{
		if (Index >= size) return push_back(Data);
		if (Index == 0) return push_front(Data);
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

	//						Remove elements
	void pop_front()
	{
		if (!Head && !Tail) return;
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
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index == 0) return pop_front();
		if (Index >= size) return;
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

	//						Method's
	const Iterator begin() const
	{
		return Head;
	}
	const Iterator end() const
	{
		return nullptr;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}
	void print() const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext) 
			std::cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << std::endl;
		std::cout << std::endl;
	}

	void reverse_print() const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			std::cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << std::endl;
		std::cout << std::endl;
	}
	friend List operator+(const List& left, const List& right);
};

List operator+(const List& left, const List& right)
{
	List cat = left;
	for (List::Iterator it = right.begin(); it != right.end(); ++it) cat.push_back(*it);
	return cat;
}

//#define BASE_CHEK
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHEK
	int n;
	std::cout << "Введите размер списка: "; std::cin >> n;
	List list1;
	for (int i = 0; i < n; i++)
	{
		//list1.push_front(rand() % 100);
		list1.push_back(rand() % 100);
	}
	list1.print();
	std::cout << delimitr << std::endl;
	list1.reverse_print();
	int index;
	int value;
	std::cout << "Enter the index of the added element: "; std::cin >> index;
	std::cout << "Enter the value of the added element: "; std::cin >> value;
	list1.insert(value, index);
	list1.print();
	std::cout << delimitr << std::endl;
	list1.reverse_print();
#endif // BASE_CHEK

	List list1 = { 3, 5, 8, 13, 21 };
	list1.print();
	for (int i : list1) std::cout << i << tab; std::cout << std::endl;
	std::cout << typeid(list1.end()).name() << std::endl;
	//for(List::ReverseIterator it = list1.rbegin(); it != list1.rend(); ++it) std::cout << *it << tab; std::cout << std::endl;
	List list2 = { 34, 55, 89 };
	for (int i : list2) std::cout << i << tab; std::cout << std::endl;
	List list3 = list1 + list2;
	for (int i : list3) std::cout << i << tab; std::cout << std::endl;
}