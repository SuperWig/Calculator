#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

double addTotal(const double& lhs, const double& rhs);
double subtractTotal(const double& lhs, const double& rhs);
double productTotal(const double& lhs, const double& rhs);
double divideTotal(const double& lhs, const double& rhs);

int main()
{
	std::string tempString{};
	std::string input{};
	std::vector<std::string> calculation{};
	char x{'*'};

	std::cout << "Welcome to the basic calculator!" << std::endl;
	std::cout << "I can only perform basic calculations and only 2 inputs at a time" << std::endl;
	std::cout << R"(For example "2+2" or "10*2")" << std::endl;
	std::cout << "\nPlease enter the calculation you wish to calculate: ";
	std::getline(std::cin, input);
	double x1 = std::stof(input);
	
	auto op = std::find_if(input.begin(), input.end(), [x](char n) {return n == x; });
	if (op == input.end())
	{
		x = '/';
		op = std::find_if(input.begin(), input.end(), [x](char n) {return n == x; });
		if (op == input.end())
		{
			x = '+';
			op = std::find_if(input.begin(), input.end(), [x](char n) {return n == x; });
			if (op == input.end())
			{
				x = '-';
				op = std::find_if(input.begin(), input.end(), [x](char n) {return n == x; });
			}
		}
	}
	std::copy(++op, input.end(), std::back_inserter(tempString));
	double x2 = std::stof(tempString);

	double sum{};
	switch (x)
	{
	case '+':
		sum = addTotal(x1, x2);
		break;
	case '-':
		sum = subtractTotal(x1, x2);
		break;
	case '/':
		sum = divideTotal(x1, x2);
		break;
	case '*':
		sum = productTotal(x1, x2);
		break;
	default:std::cout << "error" << std::endl;
		break;
	}
	
	std::cout << "\nYour total is:" << sum << std::endl;
	return 0;
}

double addTotal(const double& lhs, const double& rhs)
{
	double sum{ lhs + rhs };
	return sum;
}

double subtractTotal(const double& lhs, const double& rhs)
{
	double sum{ lhs - rhs };
	return sum;
}

double divideTotal(const double& lhs, const double& rhs)
{
	double sum{ lhs / rhs };
	return sum;
}

double productTotal(const double& lhs, const double& rhs)
{
	double sum{ lhs*rhs };
	return sum;
}