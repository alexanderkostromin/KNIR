#include"Header.h"


struct Solution {
	std::list<int> item_numbers;//Номера вещей, реализующие решение
	T total_price = 0; //Итоговая цена предложенного варианта
};


Backpack::Backpack(T WEIGHT, std::list<int> TAKEN_ITEMS, std::vector<Item> REMAINING_ITEMS, std::vector<Item>* PITEMS):
	weight(WEIGHT), taken_items(TAKEN_ITEMS), remaining_items(REMAINING_ITEMS), pItems(PITEMS)
{

}

T Backpack::get_weight() {
	return weight;
};

T Backpack::get_price() {
	T total_price = 0;
	for (auto i : taken_items  ) {
		total_price += (*pItems)[i].price;
	}
	return total_price;
}

//добавление вещи в рюкзак
void Backpack::add_item(Item item, int i) {
	taken_items.push_back(i);
	weight += item.weight;
	remaining_items.erase(remaining_items.begin());
}

//реализация того, что вещь не берут
void Backpack::leave_item() {
	remaining_items.erase(remaining_items.begin());
}

//оценка сверху жадным алгоритмом
T greedy_bound(Backpack backpack, T capacity, int i) {//добавить счетчик i++ для items[i].price и передавать его сюда
	while (backpack.remaining_items.size()) {
		if (backpack.get_weight() + backpack.remaining_items[0].weight <= capacity) {
			backpack.add_item(backpack.remaining_items[0],i);
			i++;
		}
		else 	break;
	}
	T bound = backpack.get_price();

	if (backpack.remaining_items.size()) {
		bound += backpack.remaining_items[0].price / backpack.remaining_items[0].weight * (capacity - backpack.get_weight());
	}
	return bound;
}


//рекурсивная функция позволяет найти лучшее решение, сводя задачу к случаю с n-1 вещей
//i - глубина дерева, то есть по факту номер вещи (после сортировки по удельной цене)
//для которой рассматриваются варианты брать или нет (они в программе идут с нуля)
Solution find_best(Backpack backpack, Solution& possible_solution, int i, std::vector<Item>& items, T capacity) {

	if (i<items.size()) {
		//тут будет проверка и отсекание лишних вариантов
		//для оценки качества можно вести счётчик сколько раз функция была полезна
		T upper_bound = greedy_bound(backpack,capacity,i);

		if (upper_bound < possible_solution.total_price) {
			return Solution{ {}, 0 };//вообще без разницы что возвращать
		}

		Backpack bp_copy = backpack;

		//берем вещь
		Solution result_take;
		if (backpack.get_weight() + items[i].weight <=capacity) {
			bp_copy.add_item(items[i], i);
			result_take = find_best(bp_copy, possible_solution, i + 1, items, capacity);
			bp_copy = backpack;//возвращаем копию в исходное состояние
		}

		//не берем вещь
		bp_copy.leave_item();
		Solution result_leave = find_best(bp_copy, possible_solution, i + 1, items,capacity);

		if (result_take.total_price > result_leave.total_price) {
			return result_take;
		}
		else return result_leave;
		
	}
	else {

		//находим сумму
		T total_price = 0;
		for (auto i : backpack.taken_items) {
			total_price += items[i].price;
		}
		if (total_price > possible_solution.total_price) {
			possible_solution = { backpack.taken_items, total_price};
		}
		return Solution { backpack.taken_items, total_price };
	}
	
}

//реализация метода ветвей и границ
std::list<int> branch_and_bound(int N, T capacity, std::vector<Item>& items) {
	
	Solution possible_solution = { { }, 0 };
	Backpack backpack(0, {}, items, &items);

	Solution best_solution;
	best_solution = find_best(backpack, possible_solution, 0, items, capacity);
	
	std::list<int> taken_items;
	for (auto i : best_solution.item_numbers) {
		taken_items.push_back(items[i].num);
	}
	//вопрос  надо ли +1 ответ да да

	return taken_items;
}