#include"ListOfOA.h"
#include"ListOfOA.cpp"

//#define BASE_CHECK
//#define INT_CHEK
#define DOUBLE_CHEK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	cout << delimiter << endl;
	list.reverse_print();
	int index;
	int value;
	cout << "Ввкдите индекс добавляемого элемента: "; cin >> index;
	cout << "Ввкдите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	cout << delimiter << endl;
	list.reverse_print();
#endif // BASE_CHECK

#ifdef INT_CHEK
	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	List<int> list3 = list1 + list2;

	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
#endif // INT_CHEK
#ifdef DOUBLE_CHEK
	ListSeparation::List<double> list1 = { 2.7, 3.14, 5.1 };
	ListSeparation::List<double> list2 = { 4.4, 8.3 };
	ListSeparation::List<double> list3 = list1 + list2;

	for (double i : list1)cout << i << tab; cout << endl;
	for (double i : list2)cout << i << tab; cout << endl;
	for (double i : list3)cout << i << tab; cout << endl;
#endif // DOUBLE_CHEK

}