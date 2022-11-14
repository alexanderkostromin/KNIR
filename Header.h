#pragma once
#include <fstream>
#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<set>
#include<math.h>

typedef double T;

struct Item {
	T weight = 0;
	T price = 0;
	int num = 0;
};

class Backpack {
private:
	T weight;
	std::vector<Item> remaining_items;
	std::vector<Item>* pItems;
public:
	std::list<int> taken_items;
	Backpack(T WEIGHT, std::list<int> TAKEN_ITEMS, std::vector<Item> REMAINING_ITEMS, std::vector<Item>* PITEMS);
	void add_item( Item item, int i = 0 );
	void leave_item();
	T get_weight();
	T get_price();
	//жадная оценка ветви сверху
	friend T greedy_bound(Backpack backpack, T capacity, int i);
	//номера взятых в рюкзак вещей и вещи, для которых ещё не принято решение брать их или не брать

};

std::ostream& operator<<(std::ostream& os, const Item item);

//ввод данных из файла
bool input(std::string inFileName, int& N, T& capacity, std::vector<Item>& items);

//базовая проверка на корректность данных
bool isCorrectData(int& N, T& capacity, std::vector<Item>& items);

//сортировка предметов по удельной цене
void sort_by_specific_price(std::vector<Item>& items);

//сортировка по номеру предмета
void sort_by_num(std::vector<Item>& items);

//метод ветвей и границ
std::list<int> branch_and_bound(int N, T capacity, std::vector<Item>& items);

//Приближенная схема полностью полиномиального времени
std::list<int> polynomial_time_approximation_scheme(int N, T capacity, std::vector<Item>& items, double eps = 0.5);