#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class book {
private:
	string name,title;
	int year, count;
public:
	friend istream& operator>>(istream & in, book & book)
	{	
		in >> book.name;
		in >> book.year;
		in >> book.count;
		getline(in, book.title);
		return in;
	}
	friend ostream& operator<<(ostream& out, const book& book)
	{
		//Оператор вывода
		out <<book.name << ' ' << book.year << ' ' << book.count << book.title;
		return out;
	}
	friend bool operator>(book& first, book& second)
	{
		if (first.year > second.year) return true;
		return false;
	}
};

template<class T1, class T2>
class collection {
private:
	class elem {
	public:
		T1 key; T2 item;
		elem& operator= (const elem &elem) {
			key = elem.key;
			item = elem.item;
			return *this;
		}
	};
	unsigned int top, count;
	elem *array;
	void extendarray();
public:
	collection();
	~collection();

	void sort_key();
	void sort_item();

	void add_elem(T1 key, T2 item);
	void delete_elem(unsigned int i);

	collection& operator[](unsigned int i);
	
	template <class T1, class T2>
	friend ostream& operator<<(ostream& out, const collection<T1,T2>& collection);
	
	template <class T1, class T2>
	friend istream& operator>>(istream & in, collection<T1, T2> & collection);

};

template<class T1, class T2>
collection<T1, T2>::collection() {
	top = 4;
	count = 0;
	array = new elem[top];
}

template<class T1, class T2>
collection<T1, T2>::~collection() {
	delete[] array;
}

template<class T1, class T2>
void collection<T1, T2>::add_elem(T1 key, T2 item) {
	//Добавление нашего элемента, увеличиваем массив если требуется
	if (!(top > count))  extendarray();
	array[count].key = key;
	array[count].item = item;
	count++;
}

template<class T1, class T2>
void collection<T1, T2>::delete_elem(unsigned int i) {
	//Удаление элемента по индексу
	for (; i < count; i++) {
		array[i].key = array[i + 1].key;
		array[i].item = array[i + 1].item;
	}
	count--;
}

template<class T1, class T2>
void collection<T1, T2>::extendarray() {
	//Расширение существующуего массива
	elem *x = new elem[top * 2];
	for (unsigned int i = 0; i < top; i++) {
		x[i] = array[i];
	}
	delete[]array;
	array = x;
	top = top * 2;
}

template<class T1, class T2>
void collection<T1, T2>::sort_key() {
	//Сортировка по ключу, в нашем случае с книгами, по Фамилии
	unsigned int c = count-1;
	for (unsigned int i = 0; i < c; i = 0) {
		for (unsigned int j = 0; j < c; j++) {
			if (array[j].key > array[j + 1].key) {
				elem x = array[j];
				array[j] = array[j + 1];
				array[j + 1] = x;
			}
		}
		c--;
	}
}

template<class T1, class T2>
void collection<T1, T2>::sort_item() {
	//Сортировка по содержимому, в нашем случае с книгами, по Году издания
	unsigned int c = count - 1;
	for (unsigned int i = 0; i < c; i = 0) {
		for (unsigned int j = 0; j < c; j++) {
			if (array[j].item > array[j + 1].item) {
				elem x = array[j];
				array[j] = array[j + 1];
				array[j + 1] = x;
			}
		}
		c--;
	}
}

template<class T1, class T2>
collection<T1,T2> & collection<T1,T2>::operator[](unsigned int i) {
	//Оператор квадратных скобок, можно работать как с массивом
	return array[i];
}

template<class T1, class T2>
std::ostream& operator<<(ostream& out, const collection<T1, T2>& collection)
{
	//Оператор вывода
	for (unsigned int i = 0; i < collection.count; i++) {
		out << collection.array[i].key << ' ' << collection.array[i].item << '\n';
	}
	return out;
}

template<class T1, class T2>
std::istream& operator>>(istream & in, collection<T1,T2> & collection)
{
	//Оператор ввода
	T1 key; T2 item;
	while (in >> key) {
		if (in.peek() == '\n') break;
		in >> item;
		collection.add_elem(key, item);
	}
	return in;
}

int main() {

	setlocale(0, "Russian");

	collection<string, book> arr;
	
	ifstream fin;
	fin.open("Library.txt");
	fin >> arr;
	fin.close();

	for (int decide = 1; decide != 0; ) {
		cout << "Выберите действие" << endl
			<< "1 - Вывод всех данных" << endl
			<< "2 - Добавить книгу" << endl
			<< "3 - Удалить книгу" << endl
			<< "0 - Сохранить и Выйти" << endl;
		string key; 
		book item;
		unsigned int i;
		cin >> decide;
		switch (decide) {
		case 1:
			cout << "1 - Отсортировать по Фамилии" << endl
				<<	"2 - Отсортировать по Году Издания" <<endl;
			cin >> decide;
			switch (decide) {
			case 1:
				arr.sort_key();
				cout << "Фамилия Инициалы. Год выпуска. Количество. Название." << endl;
				cout << arr << endl;
				break;
			case 2:
				arr.sort_item();
				cout << "Фамилия Инициалы. Год выпуска. Количество. Название." << endl;
				cout << arr << endl;
				break;
			default:
				cout << "Wrong Number" << endl;
			}
			break;
		case 2:
			cout << "Введите Фамилию и Инициалы автора, Год выпуска книги, Количество, и в конце Название" << endl;
			cin >> key; cin >> item;
			arr.add_elem(key, item);
			break;
		case 3:
			cout << "Введите номер элемента" << endl;
			cin >> i;
			arr.delete_elem(i);
			break;
		case 0:
			break;
		default:
			cout << "Wrong Number" << endl;
		}
	}
	
	fstream fout;
	remove("Library.txt");
	fout.open("Library.txt", fstream::app);
	fout << arr << endl;

	return 0;
}