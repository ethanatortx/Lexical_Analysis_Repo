#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

int countSubstring(const std::string& str, const std::string& sub)
{
	if(sub.length()== 0) 
		return 0;
	int count = 0;
	for(int offset = str.find(sub); offset != std::string::npos; offset = str.find(sub,offset + sub.length())) 
	{
		++count;
	}
	return count;
}

int uniqueWords(const std::string& str) 
{	
	std::string Total = "";
	std::string concat = "";
	int z = 1;
	for(int i = 0; i < str.length(); i++)
	{
		if(str[i] == ' ' || i == str.length()-1) {
			if((Total.find(concat + " ")) > str.length() && (Total.find(concat + ".")) > str.length()) {
				Total += concat + " ";
				concat = "";
				z += 1;
				
			}
			else {
				concat = " ";
			}
		}
		else {
			concat += str[i];
		}
	}
	return z;
}

std::string readIn(std::string source)
{
	std::ifstream infile;
	std::string sentence, final;
	int count = 0;
	infile.open(source);
	if(infile.is_open())
	{
		while(std::getline(infile, sentence, '\n'))
		{
			final.append(sentence);
		}
		infile.close();
	}
	else{
		std::cout << "Error Opening File" << std::endl;
	}

	return final;
}

void lexicalAnalyis(std::string source, std::string open)
{
	int totWords = countSubstring(source, " ") + 1;
	int sentances = countSubstring(source, ".");
	std::cout << "substring count: " << countSubstring(source, "is") << '\n';
	std::cout << "number of words: " << countSubstring(source, " ")  + 1 << '\n';
	std::cout << "number of sentances: " << countSubstring(source, ".") << '\n';
	std::cout << "words per sentance is: " << (double)totWords/sentances << '\n';
	double uniWord = uniqueWords(source);
	double fin = uniWord / (countSubstring(source, " ")  + 1);
	double finfin = fin * 100;
	if(finfin < 100)
	{
		std::cout << "Lexical Analysis is: " << finfin;
		std::cout << " for article " << std::endl << open << std::endl << std::endl;
	}
	else
	{
		std:: cout << "This article does not contain proper words" << std::endl << std::endl;
	}
	
}

int main()
{
	std::ifstream infile;
	std::string settings = "settings.txt";
	std::string open;
	infile.open(settings);
	if(infile.is_open())
	{
		while(std::getline(infile, open, '\n' ))
		{

			std::string source = readIn(open+".txt");
			lexicalAnalyis(source, open);
		}
		infile.close();
	}
	else
		std::cout << "Error Opening Settings File";

	
	return 0;
}