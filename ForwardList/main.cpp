#include <iostream>
using namespace std;
#define tab "\t"
#define delimitr "\n---------------------------------------------------------------\n"
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
	ForwardList(const ForwardList& other)
	{
		Element* Temp = other.Head;
		Head = new Element(Temp->Data, Head);
		int count = 0;
		while (Temp)
		{
			count++;
			if (count == 1)
			{
				Temp = Temp->pNext;
				continue;
			}
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "LCopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other)
	{
		this->Head = nullptr;
		this->Head = other.Head;
		cout << "LMoveConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		Element* Temp;
		while (Head)
		{
			Temp = Head->pNext;
			Head = nullptr;
			Head = Temp;
		}
		cout << "LDestructor:\t" << this << endl;
		print(); //Проверка на выполенение удаления
	}

	//					Adding elemetns;
	void push_front(int Data)
	{
		Head = new Element(Data, Head);
	}
	void push_back(int Data)
	{
		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
	}
	void pop_front()
	{
		Head = Head->pNext;
	}
	void pop_back()
	{
		int count = 0;
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
			count++;
		}
		Temp = Head;
		for (int i = 0; i < count - 1; i++) Temp = Temp->pNext;
		Temp->pNext = nullptr;
		
	}

	void insert(const int index, const int number)
	{
		int count = 0;
		Element* Temp = Head;
		if (index == 0)
		{
			Head = new Element(number, Head);
		}
		else 
		{
			while (count + 1 != index)
			{
				Temp = Temp->pNext;
				count++;
			}
			Temp->pNext = new Element(number, Temp->pNext);
		}
	}


	//					Methods:
	ForwardList& operator=(const ForwardList& other)
	{
		Element* Temp = other.Head;
		Head = new Element(Temp->Data);
		int count = 0;
		while (Temp)
		{
			count++;
			if (count == 1)
			{
				Temp = Temp->pNext;
				continue;
			}
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other) return *this;
		Element* Temp;
		while (Head)
		{
			Temp = Head->pNext;
			Head = nullptr;
			Head = Temp;
		}
		Head = other.Head;
		cout << "LMoveAssignment:\t" << this << endl;
		return *this;
	}
	void print() const
	{
		Element* Temp = Head; //Temp - это итератор
		// Итератор – это указатель, при помощи которого можно получить доступ к элементам структуры данных
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;//Переход на следующий элемент
		}
		cout << endl;
	}
};


void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	cout << delimitr << endl;
	list.push_back(123);
	list.print();
	cout << delimitr << endl;
	list.push_front(123);
	list.print();
	cout << delimitr << endl;
	list.pop_front();
	list.print();
	cout << delimitr << endl;
	list.pop_back();
	list.print();
	cout << delimitr << endl;
	list.insert(5, 321);
	list.print();
	cout << delimitr << endl;
	ForwardList A(list);
	A.print();
	cout << delimitr << endl;
	ForwardList B;
	B = list;
	B.print();
}