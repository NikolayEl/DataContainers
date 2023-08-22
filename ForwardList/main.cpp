#include <iostream>
#include <initializer_list>
//using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
#define delimiter "\n---------------------------------------------------------------\n"
class ForwardList;
ForwardList operator+(const ForwardList& left, const ForwardList& right);
class Element
{
	int Data; // значение элемента
	Element* pNext; // адрес следующего элемента
public:
	/*Element* get_pNext() const
	{
		return pNext;
	}
	int get_Data() const
	{
		return Data;
	}*/
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend class Iterator;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};
class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}	
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	int operator*()
	{
		return Temp->Data;
	}
};
class ForwardList
{
	Element* Head; //Голова списка - содержит адрес начального элемента списка
public:
	ForwardList()
	{
		Head = nullptr; // Если список пуст, то его голова указывает на 0
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int> &arr):ForwardList()
	{
		
		//for (int const* it = arr.begin(); it != arr.end(); it++)
		//{
		//	push_back(*it);
		//}
		for (int i: arr)
		{
			push_back(i);
		}
		cout << "ArrConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other):ForwardList()
	{
		//Element* Temp = other.Head;
		//while (Temp)
		//{
		//	push_back(Temp->Data);
		//	Temp = Temp->pNext;
		//}
		cout << "LCopyConstructor:\t" << this << endl;
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		//*this = other;
	}
	ForwardList(ForwardList&& other):ForwardList() //&& - r-value reference
	{
		//this->Head = other.Head;
		//other.Head = nullptr;
		*this = std::move(other);
		cout << "LMoveConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//					Operators
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other) return *this;
		while (Head) pop_front();
		this->Head = other.Head;
		other.Head = nullptr; 
		/*Head = nullptr;
		Element* Temp_this = Head;
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
		Element* Temp_other = other.Head;*/
		//while(Temp_other)
		//{
		//	Element* New = Temp_other;
		//	Temp_other = nullptr;
		//	Temp_other = New->pNext;
		//}
		cout << "LMoveAssignment:\t" << this << endl;
		return *this;
	}

	//					Adding elemetns;
	void push_front(int Data)
	{
		Head = new Element(Data, Head);
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
	}

	//					Delete elements
	void pop_front()
	{
		Element* erased = Head;
		Head = Head->pNext;
		delete erased;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext) Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}

	void insert(const int index, const int number)
	{
		if (index == 0) return push_front(number);
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++) if(Temp->pNext)Temp = Temp->pNext;
		// 1) Создаем новый элемент
		Element* New = new Element(number);
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		//Temp->pNext = new Element(number, Temp->pNext); //my code
	}
	void erase(int Index)
	{
		if (Index == 0) return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) if (Temp->pNext) Temp = Temp->pNext;
		Element* erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete erased;
	}


	//					Methods:
	Iterator begin()
	{
		return Head;
	}

	Iterator end()
	{
		return nullptr;
		//Element* Temp;
		//for (Temp = Head; Temp->pNext; Temp = Temp->pNext);
		//return &Temp->Data;
	}

	void print() const
	{
		//Element* Temp = Head; //Temp - это итератор
		//// Итератор – это указатель, при помощи которого можно получить доступ к элементам структуры данных
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;//Переход на следующий элемент
		//}
		//cout << endl;
		cout << "Head: " << Head << endl;
		for(Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << endl;
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)cat.push_back(Temp->Data);
	return cat;
}


//#define BASE_CHEK
//#define OPERATOR_PLUS_CHEK
//#define RANGE_BASE_FOR_ARRAY
#define MOVE_SEMANTIC_CHEK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHEK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	cout << delimiter << endl;
	cout << "Insert push back" << endl;
	list.push_back(123);
	list.print();
	cout << delimiter << endl;
	cout << "Insert push front" << endl;
	list.push_front(123);
	list.print();
	cout << delimiter << endl;
	cout << "Insert pop front" << endl;
	list.pop_front();
	list.print();
	cout << delimiter << endl;
	cout << "Insert pop back" << endl;
	list.pop_back();
	list.print();
	cout << delimiter << endl;
	cout << "Insert element:" << endl;
	list.insert(1, 321);
	list.print();
	cout << delimiter << endl;
	cout << "Delete element:" << endl;
	list.erase(2);
	list.print();
	cout << delimiter << endl;
	cout << "Copy Constructor:" << endl;
	ForwardList A(list);
	A.print();
	cout << delimiter << endl;
	cout << "Copy Assignment:" << endl;
	ForwardList B;
	B = list;
	B.print();
	cout << delimiter << endl;
	ForwardList C = A + B;
	C.print();
#endif // BASE_CHEK
#ifdef OPERATOR_PLUS_CHEK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();
	cout << delimiter << endl;

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();
	cout << delimiter << endl;

	ForwardList list3;
	cout << delimiter << endl;
	list3 = (list1 + list2);
	list3.print();

#endif // OPERATOR_PLUS_CHEK

#ifdef RANGE_BASE_FOR_ARRAY
	int arr[] = {3, 5, 8, 13, 21};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
	for (int i : arr) cout << i << tab;
	cout << endl;

	ForwardList list = {3, 5, 8, 13, 21};
	list.print();

	//cout << "Begin:" << *list.begin() << endl; //Проверка работы функций
	//cout << "End:" << *list.end() << endl;
	for (int i: list) // Это не будет работать т.к. наш ForwardList - это список из данных разных областей памяти, а данный тип цикла работает с функциями
	//	// Begine и End, с помощью которых можно задать начало и конец массива и таким образом перебрать массив, но только из одной области памяти непрерывной
	//	// Я не знаю может быть кроме этих функций можно задать и шаг, тогда эту задачу можно выполнить, а иначе нет.
	{
		cout << i << tab;
	}
	cout << endl;
	//cout << endl;
#endif // RANGE_BASE_FOR_ARRAY

#ifdef MOVE_SEMANTIC_CHEK
	ForwardList list1 = { 3, 5, 8 , 13, 21 };
	for (int i : list1) cout << i << tab; cout << endl;
	cout << delimiter << endl;

	ForwardList list2 = { 34, 55, 89 };
	for (int i : list2) cout << i << tab; cout << endl;
	cout << delimiter << endl;
	
	ForwardList list3;
	list3 = list1 + list2;
	cout << delimiter << endl;
	for (int i : list3) cout << i << tab; cout << endl; //Move constructor
#endif // MOVE_SEMANTIC_CHEK

}