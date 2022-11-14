#include <ctime>
#include"Header.h"

int main() {
	setlocale(LC_ALL, "RUS");

	int N = 0;//количество предметов
	T capacity = 0;//вместимость рюкзака
	std::vector<Item> items;//массив предметов

	std::list<int> taken_items;//вывод

	if (input("D:\\50_0.txt", N, capacity, items)) {
		if (isCorrectData(N, capacity, items)) {
			std::cout << "Файл успешно прочитан!\n\n\n";
			std::cout <<"		Входные данные:\n";
			std::cout << "Вместимость рюкзака: " << capacity<<'\n';
			for (int i = 0; i < N; i++) {
				std::cout << items[i] << '\n';
			}

			//сортировка по удельной ценности
			sort_by_specific_price(items);

			std::cout << "\n		Метод ветвей и границ:\n";
			unsigned int start_time = clock();
			taken_items = branch_and_bound(N, capacity, items);
			unsigned int end_time = clock();
			unsigned int time = end_time - start_time;
			std::cout << "Время работы: " << time / 1000. << "\n";
			taken_items.sort();//сортировка взятых вещей
			sort_by_num(items);//сортировка исходного массива (в начальное состояние)
			T price_opt = 0;//для лучшего решения
			T weight_opt = 0;
			std::cout << "Ответ:\n";
			for (auto item_num: taken_items) {
				std::cout << item_num + 1 << '\t';
				price_opt += items[item_num].price;
				weight_opt += items[item_num].weight;
			}
			std::cout << "\nОбщая ценность взятых предметов: " << price_opt << '\n';
			std::cout << "Общий вес взятых предметов: " << weight_opt << '\n';
			std::cout << "\n\n\n";


			std::cout << "\n	Приближенная схема полностью полиномиального времени:\n";
			sort_by_specific_price(items);
			//указать eps
			double eps = 0.1;
			std::cout << "Для точности: eps = " << eps*100 << "%\n";
			start_time = clock();
			taken_items = polynomial_time_approximation_scheme(N, capacity, items, eps);		
			end_time = clock();
			time = end_time - start_time;
			std::cout << "Время работы: " << time / 1000. << '\n';
			taken_items.sort();
			sort_by_num(items);
			T price_eps = 0;//для приближенного решения
			T weight_eps = 0;
			std::cout << "Ответ:\n";
			for (auto item_num : taken_items) {
				std::cout << item_num + 1 << '\t';
				price_eps += items[item_num].price;
				weight_eps += items[item_num].weight;
			}
			std::cout << "\n";
			std::cout << "\nОбщая ценность взятых предметов: " << price_eps << '\n';
			std::cout << "Общий вес взятых предметов: " << weight_eps << '\n';

			std::cout << "\n\n\nПроверка приближенного решения: Расхождение решений составило " << 100*(price_opt - price_eps) / price_opt << "%\n";
		}
		else { std::cout << "Данные введены неверно!\n"; }
	}
	else { std::cout << "Файл не открылся."; }

	system("pause");
	return 0;

}