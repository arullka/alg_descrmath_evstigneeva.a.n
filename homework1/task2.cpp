#include <iostream>
#include <string>
#include <cmath>

int main()
{
	int N, q1, q2;
	std::cin >> N; //вводим число отличное от 0
	std::cin >> q1 >> q2; //вводим изначальную систему счисления и конечную от 2 до 10
	if (q1 == 10) //если изначальная система счисления = 10
	{
		std::string s;
		while (N != 0)
		{
			s += std::to_string(N % q2);
			N /= q2;
		}
		reverse(s.begin(), s.end()); //разворачиваем строку в обратном порядке
		std::cout << s;
	}
	else if (q2 == 10) //если конечная система счисления = 10
	{
		int otvet = 0;
		std::string k = std::to_string(N); //промежуточная переменная k для того, чтобы пройтись по числу как по массиву
		for (int index = 0; index < k.length(); index++)
		{
			otvet += pow(q1, index) * (N % 10);
			N /= 10;
		}
		std::cout << otvet;
	}
	else //вариант перевода из одной системы счисления != 10 в другую != 10, используя промежуточный перевод в 10-ую сс
	{
		int otvet = 0;
		std::string k = std::to_string(N); 
		for (int index = 0; index < k.length(); index++)
		{
			otvet += pow(q1, index) * (N % 10);
			N /= 10;
		}
		std::string s;
		while (otvet != 0)
		{
			s += std::to_string(otvet % q2);
			otvet /= q2;
		}
		reverse(s.begin(), s.end()); 
		std::cout << s;
	}
}
