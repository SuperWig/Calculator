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
	char repeat{ 'a' };
	while (repeat != 'n')
	{
		std::cout << "Please enter your task:" << std::endl;
		std::getline(std::cin, inputString);
		calculateInput(inputString);
		sum = std::stod(inputString);
		std::cout << "Total is: " << sum << std::endl;
		std::cout << "Calculator another?" << std::endl;
		std::cin >> repeat;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
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
		std::move(str.replace(begin, pos - begin, std::to_string(tempL)));
		//find next power
		pos = str.find_first_of("^", 0);
	}
	pos = str.find_first_of("*/", 0);
	while (pos != std::string::npos)
	{
		//find the lhs begining of the expression by finding a non number
		auto begin = str.find_last_not_of("0123456789.", (pos - 1));
		if (begin == std::string::npos)
			begin++;
		//increase it by one to get the number
		if (str[begin] != '-' && begin != 0)
			begin++;
		//convert the numbers into doubles
		tempL = std::stod(str.substr(begin));
		tempR = std::stod(str.substr(++pos));
		if (str[pos - 1] == '*')
			tempL *= tempR;
		else if (str[pos - 1] == '/')
			tempL /= tempR;
		//replace the expression with the answer
		while (!isdigit(str[pos]))
			pos++;
		pos = str.find_first_not_of("1234567890.", pos);
		//str.erase(begin, pos - begin);
		//str.insert(begin, std::to_string(tempL));
		std::move(str.replace(begin, pos - begin, std::to_string(tempL)));
		//find the next factor
		pos = str.find_first_of("*/", 0);
	}
	//repeat for "+" and "-"
	pos = str.find_first_of("+-", 0);
	while (pos != std::string::npos)
	{
		//if the starting position is a minus number ingore it and find the next
		if (pos == 0 && str[0] == '-')
			pos = str.find_first_of("+-", 1);
		else
		{
			//find the starting position of the lhs of the operation
			//negative number will result in npos
			auto begin = str.find_last_not_of("1234567890.-", (pos - 1));
			begin++;
			//create doubles for lhs and rhs
			tempL = std::stod(str.substr(begin));
			tempR = std::stod(str.substr(++pos));
			//perform the calculation
			if (str[pos - 1] == '+')
				tempL += tempR;
			else if (str[pos - 1] == '-')
				tempL -= tempR;
			//find a digit after the operation
			while (!isdigit(str[pos]))
				pos++;
			//find the end of the string to delete
			pos = str.find_first_not_of("1234567890.", pos);
			std::move(str.replace(begin, pos - begin, std::to_string(tempL)));
			if (str[0] == '-')
				pos = str.find_first_of("+-", 1);
			else
				pos = str.find_first_of("+-", 0);
		}
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
		std::move(str.replace(front, back - front + 1, subString));
		front = str.find_last_of("(", back);
		back = str.find_first_of(")", front);
	}
	calculateExpression(str);
}