#include <string>
#include <iostream>
#include <algorithm>

void calculateExpression(std::string& str);
void calculateInput(std::string& str);

int main()
{
	std::string inputString{ "" };
	double sum{ 0 };

	std::cout << "\tWelcome to the basic calculator!\n" << std::endl;
	std::cout << "You can perform a basic operation(/ * - + ^)" << std::endl;
	std::cout << "Please enter your task:" << std::endl;
	std::getline(std::cin, inputString);

	calculateInput(inputString);
	sum = std::stod(inputString);

	std::cout << "Total is: " << sum << std::endl;

	return 0;
}

void calculateExpression(std::string& str)
{

	double tempL{ 0 };
	double tempR{ 0 };

	str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
	auto pos = str.find_first_of("^", 0);
	while (pos != std::string::npos)
	{
		//find the lhs begining of the expression by finding a non number
		auto begin = str.find_last_not_of("0123456789.", (pos - 1));
		//increase it by one to get the number
		begin++;
		//convert the numbers into doubles
		tempL = std::stod(str.substr(begin));
		tempR = std::stod(str.substr(++pos));
		//calculate
		tempL = std::pow(tempL, tempR);
		//replace the expression with the answer
		pos = str.find_first_not_of("1234567890.-", pos);
		str.erase(begin, pos - begin);
		str.insert(begin, std::to_string(tempL));
		//find next power
		pos = str.find_first_of("^", 0);
	}
	pos = str.find_first_of("*/", 0);
	while (pos != std::string::npos)
	{
		//find the lhs begining of the expression by finding a non number
		auto begin = str.find_last_not_of("0123456789.", (pos - 1));
		//increase it by one to get the number
		begin++;
		//convert the numbers into doubles
		tempL = std::stod(str.substr(begin));
		tempR = std::stod(str.substr(++pos));
		if (str[pos - 1] == '*')
			tempL *= tempR;
		else if (str[pos - 1] == '/')
			tempL /= tempR;
		//replace the expression with the answer
		pos = str.find_first_not_of("1234567890.-", pos);
		str.erase(begin, pos - begin);
		str.insert(begin, std::to_string(tempL));
		//find the next factor
		pos = str.find_first_of("*/", 0);
	}
	//repeat for "+" and "-"
	pos = str.find_first_of("+-", 0);
	while (pos != std::string::npos && str[0] != '-')
	{
		auto begin = str.find_last_not_of("1234567890.", (pos - 1));
		begin++;
		tempL = std::stod(str.substr(begin));
		tempR = std::stod(str.substr(++pos));
		if (str[pos - 1] == '+')
			tempL += tempR;
		else if (str[pos - 1] == '-')
			tempL -= tempR;
		pos = str.find_first_not_of("1234567890.", pos);
		str.erase(begin, pos - begin);
		str.insert(begin, std::to_string(tempL));
		pos = str.find_first_of("+-", 0);
	}
}

void calculateInput(std::string& str)
{
	str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
	auto front = str.find_last_of("(");
	auto back = str.find_first_of(")", front);
	while (front != std::string::npos && back != std::string::npos)
	{
		auto subString = str.substr(front + 1, back - front - 1);
		calculateExpression(subString);
		str.erase(front, back - front + 1);
		str.insert(front, subString);
		front = str.find_last_of("(", back);
		back = str.find_first_of(")", front);
	}
	calculateExpression(str);
}