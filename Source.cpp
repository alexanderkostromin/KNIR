#include"Header.h"

std::ostream& operator<<(std::ostream& os, const Item item) {

	os << "Предмет №(" << item.num + 1 << "):\t вес = " << item.weight <<"\t стоимость = "  << item.price;
	return os;
}

bool input(std::string inFileName, int& N, T& capacity, std::vector<Item>& items) {
	std::cout << "Считываем файл...\n";
	std::ifstream in(inFileName); // окрываем файл для чтения
	if (in.is_open()) {

		in >> N;
		items.reserve(N);

		//считываем вещи
		for (int i = 0; i < N; i++) {
			Item item;
			in >> item.weight >> item.price;
			item.num = i;
			items.push_back(item);
		}

		in >> capacity;

		return true;
	}
	else return false;
}

bool isCorrectData(int& N, T& capacity, std::vector<Item>& items) {
	if (N <= 0 || capacity < 0) return false;
	for (auto& item : items) {
		if (item.price <= 0 || item.weight <= 0) return false;
	}
	//проверка корректности данных

	return true;
}


void sort_by_num(std::vector<Item>& items) {

	int size = items.size();
	for (int i = 0; i < size; i++) {
		int min_ind = i;
		double min_y = items[i].num;
		for (int j = i + 1; j < size; j++) {
			if (min_y > items[j].num) {
				min_ind = j;
				min_y = items[j].num;
			}
		}
		Item copy_item;
		copy_item = items[i];
		items[i] = items[min_ind];
		items[min_ind] = copy_item;
	}
}

//сортировка предметов по удельной цене O(N^2) времени
void sort_by_specific_price(std::vector<Item>& items) {//сортировка выбором

	//поменять обозначения
	//оптимизация

	int size = items.size();
	for (int i = 0; i < size; i++) {
		int max_ind = i;
		double max_y = items[i].price / items[i].weight;
		for (int j = i + 1; j < size; j++) {
			if (max_y < items[j].price / items[j].weight) {
				max_ind = j;
				max_y = items[j].price / items[j].weight;
			}
		}
		Item copy_item;
		copy_item = items[i];
		items[i] = items[max_ind];
		items[max_ind] = copy_item;
	}
}