// CIS 142 Assignment 3 - Guerrero.cpp : To create a table showing the square of integer "n," n = 1-10
// Francesca Guerrero, 9/20/2024. Homework Assignment 3

#include <iostream>
#include <iomanip>

int main() 
{
	int n;

	std::cout << std::setw(5) << "n" << std::setw(15) << "n^2" << std::endl;
	std::cout << "------------------------" << std::endl;

	for (n = 1; n <= 10; n++)
	{
		std::cout << std::setw(5) << n << std::setw(15) << n * n << std::endl;
	}
	return 0;

}

		// Eliminated "using namespace std;" since already told compiler cout, setw(), and endl belong 
		// to the standard namespace by using scope resolution operator (::) in std::x.
		
// <iomanip> library functions for formatting.
// setw() function to visually format table for readability with spacing.
// For-loop for finite range calculations and readability.
// I spent so long on this.
