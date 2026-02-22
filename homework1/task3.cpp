#include <iostream>

int main()
{
	long long seconds;
	std::cin >> seconds;

	const long long sec_in_week = 604800;
	const long long sec_in_day = 86400;
	const long long sec_in_hour = 3600;
	const long long sec_in_min = 60;

	std::cout << seconds / sec_in_week << " weeks, ";
	seconds %= sec_in_week;
	std::cout << seconds / sec_in_day << " days, ";
	seconds %= sec_in_day;
	std::cout << seconds / sec_in_hour << " hours, ";
	seconds %= sec_in_hour;
	std::cout << seconds / sec_in_min << " minutes, ";
	seconds %= sec_in_min;
	std::cout << seconds << " seconds";
}
