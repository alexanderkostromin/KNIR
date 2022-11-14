#include"Header.h"
#define MIN(a,b) (a < b ? a : b)

struct Pseudo_solution {
	std::list<int> item_numbers;//номера вещей в отсортированном массиве
	T weight=0;//минимальный объем, необходимый для того чтобы уложить предметы с номерами,
					//не превосходящими k от 1 до N, общей стоимостью не менее p<=S
};

//суммарная стоимость при жадном алгоритме
T greedy_price_opt(int N, T capacity, std::vector<Item>& items) {
	T total_price = 0;
	T total_weight = 0;
	int i = 0;
	while (i != N) {
		while (total_weight + items[i].weight <= capacity) {
			total_weight += items[i].weight;
			total_price += items[i].price;
			i++;
			if (i == N) break;
		}
		if (total_price == 0 && i != N) {
			i++;
		}
		else break;
	}


		
	return total_price;
}

std::list<int> polynomial_time_approximation_scheme(int N, T capacity, std::vector<Item>& items, double eps) {

	T p_max = 0;
	p_max = greedy_price_opt(N, capacity,items);//оценка такова, что стоимость оптимального решения не меньше чем стоимость при жадном заполнении
												



	double coeff = p_max /( (1 + (1. / eps)) * N);
	std::vector<long long> items_rounded_price;
	for (auto item : items) {
		items_rounded_price.push_back(long long(round(item.price * 1.0 / coeff)));
	}
	
	long long S = 0;
	for (auto item_price : items_rounded_price) {
		S += item_price;
	}

	Pseudo_solution** w = new Pseudo_solution*[N+1];
	for (int i = 0; i <= N; i++) {
		w[i] = new Pseudo_solution[S+1];
	}
	//w(k,p)
	//w(N,S)

	for (long long p = 1; p <= S; p++) {
		for (int k = 1; k <= N; k++) {
			w[k][p].weight = capacity+1;
		}
	}

	w[0][0].weight = 0;
	w[0][0].item_numbers = {};
	for (int p = 1; p <= S; p++) {
		w[0][p].weight = -1;
	}
	for (int k = 1; k <= N; k++) {
		w[k][0].weight = 0;
		w[k][0].item_numbers = {};
	}

	std::list<int> best_solution;//будет хранить номера элементов в векторе items, которым соотвествует лучшее решение данным методом
	for (long long p = 1; p <= S;p++) {
		for(int k = 0; k < N; k++) {
			T w_take;
			T w_leave;
			std::list<int> take_numbers;
			if (p - items_rounded_price[k] <= 0) {
				w_take = w[k][0].weight;
				take_numbers = w[k][0].item_numbers;
			}
			else {
				w_take = w[k][p - items_rounded_price[k]].weight;
				take_numbers = w[k][p - items_rounded_price[k]].item_numbers;
			}

			w_leave = w[k][p].weight;

			if (w_take== -1) {
				if (w_leave == -1) {
					w[k + 1][p].weight = -1;
				}
				else {
					w[k + 1][p].weight = w_leave;	
					w[k + 1][p].item_numbers = w[k][p].item_numbers;
				}
			}
			else {
				if (w_leave == -1 || w_take + items[k].weight <= w_leave) {//суть в том что первая строка в этой таблице ~ноль предметов поэтому item на один индекс меньше
					w[k + 1][p].weight = w_take + items[k].weight;
					w[k + 1][p].item_numbers = take_numbers;
					w[k + 1][p].item_numbers.push_back(k);
				}
				else {
					w[k + 1][p].weight = w_leave;
					w[k + 1][p].item_numbers = w[k][p].item_numbers;
				}
			}
		}

		if (w[N][p].weight <= capacity) {//можем искать дальше
			best_solution = w[N][p].item_numbers;
		}
		else {//иначе нашли максимальное p(предыдущее)
			break;	
		}
	}


	std::list<int> taken_items;
	for (auto i : best_solution) {
		taken_items.push_back(items[i].num);
	}

	for (int i = 0; i <= N; i++) {
		delete[] w[i];
	}

	return taken_items;
}