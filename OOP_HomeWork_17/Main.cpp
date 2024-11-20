#include<iostream>
#include<exception>
#include<cstdlib>
#include<ctime>
#include<string>
#include<sstream>	// для ф-ии std::istringsteam

// ф-ия, кот. принимает числа М и N, являющиеся началом и концом некоего диапазона, после чего
// возвращает случайное число, входящее в этот диапазон. Ф-ия должна бросать исключение, если вдруг
// число N оказалось больше или равно числу М.
int make_rand_number(const int begin, const int end) {
	if (begin > end)
		throw std::invalid_argument("Некорректно введен диапазон чисел - начало больше конца!\n");
	if (begin == end)
		throw std::invalid_argument("Некорректно введен диапазон чисел - начало равно концу!");
	int tmp = rand() % (end - begin + 1) + begin;
	return tmp;
}
// ф-ия, кот. преобразует из string в double:
bool num_from_str(const std::string& str, double& num) {
	std::istringstream i_str(str);
	return (i_str >> num) ? true : false;
}
// ф-ия, кот. просит пользователя ввести строку в следующем виде: "слово длина_слова". 
// Ф-ия возвращает true, если длина слова равна длине строки от пользователя. 
// Иначе возвращает false. Ф-ия должна бросать исключение, если пользователь вводит строку
// в отличном от требуемого виде.
void StringRequest() {
	std::cout << "Введите строку в следующем виде \"слово длина_слова\" - ";
	std::string str;
	std::cin.ignore(10, '\n');
	std::getline(std::cin, str);
	std::cout << str << " - ";
	std::string tmp_str, tmp_num;
	double num;
	tmp_str.reserve(str.length());
	int count = 0;	// счетчик пробелов
	try {
		for (auto it = str.cbegin(); it != str.cend(); ++it) {
			if (*it == ' ') {	// считаем кол-во пробелов
				++count;
			}
			if (count > 1)		// если пробелов больше одного, то кидаем исключение
				throw std::exception("исключение");
			if (count == 0) {	// до первого пробела записываем в tmp_str строку
				tmp_str += *it;
			}
			else {				// после первого пробела записываем в tmp_num второе слово(цифру)
				tmp_num += *it;
			}
		}
		if (!num_from_str(tmp_num, num))			// вызываем ф-ию по переводу строки в double,
			throw std::exception("исключение");		// при неудачном переводе, бросаем исключение.
		
		if (num == tmp_str.length())			// сравниваем значение num с длиной первого слова.
			std::cout << "true" << std::endl;
		else
			std::cout << "false" << std::endl;		
	}
	catch (std::exception& log) {
		std::cout << log.what() << '\n';
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	std::cout << "Task 17\n";
	srand(time(NULL));
	try {
		std::cout << "Задание 1.\nВведите диапазон чисел для подбора случайного числа: ";
		int begin_num, end_num, rand_num;
		std::cin >> begin_num >> end_num;
		rand_num = make_rand_number(begin_num, end_num);
		std::cout << "Случайное число - ";
		std::cout << rand_num;
		std::cout << std::endl;
	}
	catch (std::invalid_argument& log) {
		std::cout << "Error: " << log.what() << '\n';
	}
	try {
		std::cout << "\nЗадание 2.\n";
		StringRequest();
	}
	catch (std::exception& log) {
		std::cout << log.what() << '\n';
	}

	return 0;
}