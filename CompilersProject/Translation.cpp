#include <iostream>
#include <fstream>
#include <string>

class TranslateToCode
{
public:
	void Translate()
	{
		std::ifstream myfile;
		myfile.open("test.txt");
		// Checking if file is open
		if (myfile.is_open())
		{
			std::string lineHolder;
			while (!myfile.eof())
			{
				std::getline(std::cin, lineHolder);
				std::string wordHolder = "";
				while (!lineHolder.end)
				{

				}
			}
			myfile.close();
		}
		else
		{
			std::cout << "File could not be opened" << std::endl;
		}
	}
};
class Tester
{
public:
	void Test(std::string str)
	{
		char *pnt = &str[0];
		int test1 = 556;
		int* pnt1 = &test1;
		std::cout << &pnt;
	}
};