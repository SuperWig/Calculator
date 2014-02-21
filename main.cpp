#include <string>
#include <algorithm>    
#include <iostream>
#include <vector>

void splitString(std::vector<std::string>& vec, std::string& str);
void calculateElements(std::vector<std::string>& vec, double& sum);

int main()
{
	std::string inputString{"2+2"};
	std::vector<std::string> cutString{};

	std::cout << "\tWelcome to the basic calculator!\n" << std::endl;
	std::cout << "You can perform a basic operation(/ * - +)" << std::endl;
	std::cout << "Please enter your task:" << std::endl;
	std::getline(std::cin, inputString);
	

	double sum{0};
	splitString(cutString, inputString);
	calculateElements(cutString, sum);


	std::cout << "Total is: " << sum << std::endl;

	return 0;
}

void splitString(std::vector<std::string>& vec, std::string& str)
{
	unsigned int pos{ 0 };
	unsigned int newpos{};
	while (pos != std::string::npos)
	{
		newpos = str.find_first_of("+*/-xX", pos);
		if (newpos != std::string::npos)
			vec.push_back(std::move(str.substr(pos, newpos - pos)));
		else
			vec.push_back(std::move(str.substr(pos)));
		if (newpos != std::string::npos)
			vec.push_back(std::move(str.substr(newpos++, 1)));
		pos = newpos;
	}
}

void calculateElements(std::vector<std::string>& vec, double& sum)
{
	auto result = std::find_if(vec.begin(), vec.end(), [](std::string c) {return c == "*" || c == "x" || c == "X" || c == "/"; });
	while (result != vec.end())
	{
		if (*result == "*" || *result == "X" || *result == "x")
		{
			--result;
			sum = std::stod(*result);
			result += 2;
			sum *= std::stod(*result);
		}
		else if (*result == "/")
		{
			--result;
			sum= std::stod(*result);
			result += 2;
			sum /= std::stod(*result);
		}
		result->swap(std::move(std::to_string(sum)));
		auto temp = result - 2;
		vec.erase(temp, result--);
		result = std::find_if(vec.begin(), vec.end(), [](std::string c) {return c == "*" || c == "/"; });
		sum = 0;
	}
	result = std::find_if(vec.begin(), vec.end(), [](std::string c) {return c == "+" || c == "/"; });
	while (result != vec.end())
	{
		if (*result == "+")
		{
			--result;
			sum =  std::stod(*result);
			result += 2;
			sum += std::stod(*result);
		}
		else if (*result == "-")
		{
			--result;
			if (*result == "(")
				std::stod(*(result + 1));
			else
			{
				sum = std::stod(*result);
				result += 2;
				sum -= std::stod(*result);
			}
		}
		result->swap(std::to_string(sum));
		auto temp = result - 2;
		vec.erase(temp, result--);
		result = std::find_if(vec.begin(), vec.end(), [](std::string c) {return c == "+" || c == "-"; });
		sum = 0;
	}

	sum = std::stod(vec[0]);

}