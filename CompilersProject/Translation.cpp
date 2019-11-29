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
			std::ofstream newFile;
			std::string lineHolder;
			bool stopOnSemi = false;
			bool isFileName = false;
			bool isVAR = false;
			bool isDataType = false;
			std::string temp1 = "";
			std::string temp2 = "";
			while (!myfile.eof())
			{
				// Getting one line document
				std::getline(myfile, lineHolder);
				std::string wordHolder = "";
				// Iteratating through the getline
				std::string::iterator it;

				for (it = lineHolder.begin(); it != lineHolder.end(); it++)
				{
					if (*it == ';' && stopOnSemi)
					{
						if (isFileName)
						{
							// Creating file with given name
							wordHolder += ".cpp";
							newFile.open(wordHolder);
							isFileName = false;
							stopOnSemi = false;
						}
					}
					// Places next character into word string
					else if (*it != ' ')
					{
						wordHolder += *it;
					}
					else if (*it == ' ' && !stopOnSemi)
					{
						// Check if word is reserved
						if (wordHolder == "PROGRAM")
						{
							stopOnSemi = true;
							isFileName = true;
							wordHolder = "";
						}
						else if (wordHolder == "VAR")
						{
							isVAR = true;
						}
						else if (isVAR)
						{
							if (wordHolder != ":")
							{
								temp2 += wordHolder;
							}
							else
							{
								isDataType = true;
							}
						}
						else if (isDataType)
						{
							if (wordHolder == "INTEGER")
							{
								temp1 = "int";
							}
							else if (wordHolder == "DOUBLE")
							{
								temp1 = "double";
							}
							else if (wordHolder == "FLOAT")
							{
								temp1 = "float";
							}
							else if (wordHolder == "BOOLEAN")
							{
								temp1 = "bool";
							}
						}

					}
				}
				newFile << temp1 + " " + temp2;
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