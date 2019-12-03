#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
			bool hasBegan = false;
			bool hasEnded = false;
			bool insFront = false;
			bool isPrinting = false;
			bool openParenth = false;		// Simple boolean used in PRINT()
			bool iostream = false;
			// Creating vector to store output by line
			std::vector<std::string> ans;
			while (!myfile.eof())
			{
				// Getting one line document
				std::getline(myfile, lineHolder);
				std::string wordHolder = "";
				// Iteratating through the getline
				std::string::iterator it;
				std::string::iterator itNext;
				std::string temp1 = "";		// Used to store reserved words
				std::string temp2 = "";		// Used to store non-reserved words (variable names etc.)

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
					else if (*it == ';' && temp1 == "")
					{
						temp2 = wordHolder;
					}
					// Places next character into word string
					else if (*it != ' ' && *it != ':')
					{
						if (*it == '\'')
						{
							wordHolder += '\"';
						}
						else
						{
							wordHolder += *it;
						}
					}
					if (wordHolder == "PRINT")
					{
						isPrinting = true;
						wordHolder = "";
						temp1 = "std::cout";
					}
					if (wordHolder == "END")
					{
						hasEnded = true;
					}
					else if (isPrinting && (*it == '(' || *it == ')' || *it == ','))
					{
						if (wordHolder == "(")
						{
							temp1 += " << ";
							openParenth = true;		// Used to count currently open parentheses
							wordHolder = "";
						}
						else if (*it == ')')
						{
							wordHolder.pop_back();
							openParenth = false;
						}
						else if (*it == ',')
						{
							wordHolder.pop_back();
							wordHolder += " << ";
						}
					}
					if (*it != lineHolder[lineHolder.size() - 1])
					{
						itNext = std::next(it, 1);
					}
					if ((*itNext == ' ' && !stopOnSemi) || (*it == lineHolder[lineHolder.size() - 1] && !stopOnSemi) || *itNext == ':' || *itNext == ';')
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
							wordHolder = "";
						}
						else if (wordHolder == "BEGIN" && !hasBegan)
						{
							hasBegan = true;
							temp1 = "int main()\n{";
							insFront = true;
						}
						else if (isVAR)
						{
							if (*itNext == ':')
							{
								isDataType = true; 
								temp2 = wordHolder;
								wordHolder = "";
								isVAR = false;
							}
						}
						else if (isDataType)
						{
							if (wordHolder == "INTEGER")
							{
								temp1 = "int ";
								isDataType = false;
								wordHolder = "";
							}
							else if (wordHolder == "DOUBLE")
							{
								temp1 = "double ";
								isDataType = false;
								wordHolder = "";
							}
							else if (wordHolder == "FLOAT")
							{
								temp1 = "float ";
								isDataType = false;
								wordHolder = "";
							}
							else if (wordHolder == "BOOLEAN")
							{
								temp1 = "bool ";
								isDataType = false;
								wordHolder = "";
							}
						}
						else if (isPrinting && *itNext == ';')
						{
							temp2 = wordHolder;
							isPrinting = false;
							if (!iostream)
							{
								ans.insert(ans.begin(), "#include <iostream>");
								iostream = true;
							}
						}
					}
				}
				if (temp1 != "" || temp2 != "")
				{
					if (insFront)
					{
						ans.insert(ans.begin(), temp1);
						insFront = false;
					}
					else if (temp2 != "")
					{
						temp2 += ";";
						ans.push_back(temp1 + temp2);
					}
					else
					{
						ans.push_back(temp1 + temp2);
					}
				}
			}
			myfile.close();
			std::vector<std::string>::iterator it;
			for (it = ans.begin(); it != ans.end(); it++)
			{
				//std::cout << *it << std::endl;
				newFile << *it << std::endl;
			}
			// Always end this way if int main() has been initiated
			if (hasBegan && hasEnded)
			{
				//std::cout << "return 0;" << std::endl;
				//std::cout << "}" << std::endl;
				newFile << "return 0;" << std::endl;
				newFile << "}" << std::endl;
			}
			newFile.close();
		}
		else
		{
			std::cout << "File could not be opened" << std::endl;
			return;
		}
	}
};